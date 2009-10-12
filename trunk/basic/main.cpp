#include <stdio.h>
#include <stdlib.h>

#undef STRICT
#define WIN32_LEAN_AND_MEAN     1
#include <windows.h>

#include <cmath>
using namespace std;

#include "wavesound.h"

#include "matrix/matrix_processing.h"

int main(int argc, char** argv) {
	/********************* Default values **********************/
	int R = 10;		//Количество частотных диапазонов
	int N = 60;		//Размер фрейма (окна анализа)
	int J = 8;		//количество ненулевых собственных чисел собственных векторов матрицы А
	int P = 1000;	//Количество отсчетов от начала файла, которые считаются паузой

	char* action;

	char* wav_name;
	char* compressed_name;
	char* matrix_a_path;
	
	if (argc == 2 && strcmp(argv[1], "-help") == 0) {
		return 0;
	}
	if (argc < 6) {
		printf("Command line arguments error. Use '-help'\n");
		return 0;
	}
	else {
		action = argv[1];
		for (int i = 2; i < argc; i+=2) {
			if (strcmp(argv[i], "-s") == 0)
				wav_name = argv[i+1];
			else if (strcmp(argv[i], "-d") == 0)
				compressed_name = argv[i+1];
			else if (strcmp(argv[i], "-a") == 0)
				matrix_a_path = argv[i+1];
			else if (strcmp(argv[i], "-N") == 0)
				N = atoi(argv[i+1]);
			else if (strcmp(argv[i], "-R") == 0)
				R = atoi(argv[i+1]);
			else if (strcmp(argv[i], "-J") == 0)
				J = atoi(argv[i+1]);
			else if (strcmp(argv[i], "-P") == 0)
				P = atoi(argv[i+1]);
		}
	}

	wav_name = "files/wav/lec02_8000.wav";
	//wav_name = "files/wav/news_studio_8000.wav";
	//compressed_name = "files/wav/news_studio_8000_compressed.wav";
	//matrix_a_path = "files/matrix/AA_10_60_8.txt";

	unsigned long start_tick_count = GetTickCount();

	WaveSound* ws = new WaveSound();
	ws->Load(wav_name);

	float** AA = new float*[R*J];
	for (int i = 0; i < R*J; i++) 
		AA[i] = new float[N];

	matrix_read(matrix_a_path, R*J, N, AA);

	int wav_data_length = ws->getAvialible();				//Длина исходного сигнала

	float* wav_data = new float[wav_data_length];			//Исходный сигнал
	ws->ReadFlt(wav_data, wav_data_length);

	float wav_mean = matrix_mean(&wav_data, 1, wav_data_length);
	
	int area_count = (int)ceil(wav_data_length / (float)N);	//Количество анализируемых отрезков
	int area_counter = 0;									//Количество обработанных отрезков
	int sample_counter = 0;
	int pause_boundary = 20;								//Порог для решающей функции

	/*===================== Вычисление энергии паузы ======================= */
	float* pause_power = new float[R];
	memset(pause_power, 0, sizeof(float) * R);

	for (int curr_pause_area = 0; curr_pause_area < P; curr_pause_area++) {
		float* pause_data = new float[N];
		memcpy(pause_data, wav_data + curr_pause_area*N, sizeof(float)*N);

		float pause_mean = matrix_mean(&pause_data, 1, 60);

		for (int i = 0; i < N; i++) 
				pause_data[i] = pause_data[i] - pause_mean;

		float* pause_yy = new float[R*J];
		matrix_mult_trans(&pause_data, AA, 1, 60, 80, &pause_yy);
		
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < J; j++) {
				pause_power[i] += pow(pause_yy[i*J + j], 2);
			}
		}

		delete pause_data;
		delete pause_yy;
	}

	for (int i = 0; i < R; i++) 
		pause_power[i] /= (float)P;
	
	/*===================== Окончание вычисления энергии паузы ======================= */

	int signal_area_count = 0;
	int signal_length = 0;
	int pause_area_count = 0;
	
	float* result_data = new float[wav_data_length];			//Полученный сигнал

	for (int curr_area = 0; curr_area < area_count; curr_area++) {
		int area_length = (curr_area + 1)*N > wav_data_length ? wav_data_length - (curr_area)*N : N;

		float* area_data = new float[area_length];			//Семпл	
		memcpy(area_data, wav_data+(curr_area*N), sizeof(float)*area_length);		
		
		float area_mean = matrix_mean(&area_data, 1, area_length);

		//Сигнал минус среднее
		for (int i = 0; i < area_length; i++) 
			area_data[i] = area_data[i] - area_mean;
		
		//Вычисление энергии сигнала
		float* area_power = new float[R];
		memset(area_power, 0, sizeof(float) * R);
		
		float* area_yy = new float[R*J];
		matrix_mult_trans(&area_data, AA, 1, 60, 80, &area_yy);

		for (int i = 0; i < R; i++) {
			for (int j = 0; j < J; j++) {
				area_power[i] += pow(area_yy[i*J + j], 2);
			}
		}

		float decision_function;		//Решающая функция
		for (int i = 0; i < R; i++) {
			area_power[i] /= (float) pause_power[i];
			decision_function = (i == 0 || area_power[i] > decision_function) ? area_power[i] : decision_function;
		}

		if (decision_function > pause_boundary) {		//Сигнал
			signal_area_count++;

			memcpy(result_data + signal_length, area_data, sizeof(float)*area_length); //Копирование данных в выходной файл
			signal_length += area_length;
		}
		else {											//Пауза
			pause_area_count++;
		}
		
		delete area_yy;
		delete area_data;
		delete area_power;
		area_counter++;
	}

	ws->Destroy();

	WaveSound* result_file = new WaveSound();
	result_file->Create(compressed_name, 
						result_data, 
						signal_length, 
						ws->getChannels(), 
						ws->getRate(), 
						ws->getBPS());

	result_file->Destroy();
	
	delete wav_data;
	delete pause_power;
	delete AA;

	delete ws;
	delete result_file;

	printf("Compression time: %.3f sec.\n", (GetTickCount() - start_tick_count)/1000.f);

	return 0;
}