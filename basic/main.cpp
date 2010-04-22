#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#undef STRICT
#define WIN32_LEAN_AND_MEAN     1
#include <windows.h>

#include <cmath>
using namespace std;

#include "wavesound.h"
#include "compressing/compress_data.h"
#include "matrix/matrix_processing.h"

int main(int argc, char** argv) {
	//******************** Default values *********************//
	int Rp = 10;	//Количество частотных диапазонов для паузы
	int Np = 60;	//Размер фрейма (окна анализа) для паузы
	int P = 100;	//Количество фреймов которые считаются паузой
	int p = 0;		//Количество отсчетов от начала файла до начала паузы
	int BPS = 3;	//Количество разрядов квантования


	char* action;

	char* wav_name;
	char* compressed_name;
	char* matrix_a_path;
	
	if (argc == 2 && strcmp(argv[1], "-help") == 0) {
		printf("Using: ");
		printf("basic.exe command \n\t\t-s path_to_source_file \n\t\t-d path_to_destination_file \n\t\t-a path_to_matrix_AA_file\n");
		printf("\t\t[-Rp number] \n\t\t[-Np number] \n\t\t[-P number]\n\n");
		printf("\t> command - Now supported only -c (compress)\n");
		printf("\t> -Rp number - Count of pause frequency bands\n");
		printf("\t> -Np number - The size of the pause frame\n");
		printf("\t> -P number - The number of samples from the beginning of the file, which are considered a pause\n");
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
			else if (strcmp(argv[i], "-Np") == 0)
				Np = atoi(argv[i+1]);
			else if (strcmp(argv[i], "-Rp") == 0)
				Rp = atoi(argv[i+1]);
			else if (strcmp(argv[i], "-P") == 0)
				P = atoi(argv[i+1]);
			else if (strcmp(argv[i], "-p") == 0)
				p = atoi(argv[i+1]);
		}
	}

	int Jp = 2*(Np/(2*Rp)) + 2;		//Количество ненулевых собственных чисел собственных векторов матрицы для паузы
	int Ns = Np;					//Размер фрейма (окна анализа) для сигнала
	int Rs = Rp;					//Количество частотных диапазонов для сигнала
	int Js = 2*(Ns/(2*Rs)) + 2;		//Количество ненулевых собственных чисел собственных векторов матрицы для сигнала

	//wav_name = "files/wav/lec02_8000.wav";
	//wav_name = "files/wav/news_studio_8000.wav";
	//compressed_name = "files/wav/news_studio_8000_compressed.wav";
	//matrix_a_path = "files/matrix/AA_10_60_8.txt";

	unsigned long start_tick_count = GetTickCount();

	WaveSound* ws = new WaveSound();
	ws->Load(wav_name);

	float** AA = new float*[Rp*Jp];
	for (int i = 0; i < Rp*Jp; i++) 
		AA[i] = new float[Np];

	matrix_read(matrix_a_path, Rp*Jp, Np, AA);

	int wav_data_length = ws->getAvialible();				//Длина исходного сигнала

	float* wav_data = new float[wav_data_length];			//Исходный сигнал
	ws->ReadFlt(wav_data, wav_data_length);

	float wav_mean = matrix_mean(&wav_data, 1, wav_data_length);
	
	int area_count = (int)ceil(wav_data_length / (float)Np);	//Количество анализируемых отрезков
	int area_counter = 0;									//Количество обработанных отрезков
	int sample_counter = 0;
	int pause_boundary = 20;								//Порог для решающей функции

	//===================== Вычисление энергии паузы ======================= //
	float* pause_power = new float[Rp];
	memset(pause_power, 0, sizeof(float) * Rp);

	for (int curr_pause_area = 0; curr_pause_area < P; curr_pause_area++) {
		float* pause_data = new float[Np];
		memcpy(pause_data, wav_data + p + curr_pause_area*Np, sizeof(float)*Np);

		float pause_mean = matrix_mean(&pause_data, 1, 60);

		for (int i = 0; i < Np; i++) 
				pause_data[i] = pause_data[i] - pause_mean;

		float* pause_yy = new float[Rp*Jp];
		matrix_mult_trans(&pause_data, AA, 1, 60, 80, &pause_yy);
		
		for (int i = 0; i < Rp; i++) {
			for (int j = 0; j < Jp; j++) {
				pause_power[i] += pow(pause_yy[i*Jp + j], 2);
			}
		}

		delete pause_data;
		delete pause_yy;
	}

	for (int i = 0; i < Rp; i++) 
		pause_power[i] /= (float)P;
	
	//===================== Окончание вычисления энергии паузы ======================= //

	int signal_area_count = 0;
	int signal_length = 0;
	int pause_area_count = 0;
	
	float* result_data = new float[wav_data_length];			//Полученный сигнал

	for (int curr_area = 0; curr_area < area_count; curr_area++) {
		int area_length = (curr_area + 1)*Np > wav_data_length ? wav_data_length - (curr_area)*Np : Np;

		float* area_data = new float[area_length];			//Семпл	
		memcpy(area_data, wav_data+(curr_area*Np), sizeof(float)*area_length);		
		
		float area_mean = matrix_mean(&area_data, 1, area_length);

		//Сигнал минус среднее
		for (int i = 0; i < area_length; i++) 
			area_data[i] = area_data[i] - area_mean;
		
		//Вычисление энергии сигнала
		float* area_power = new float[Rp];
		memset(area_power, 0, sizeof(float) * Rp);
		
		float* area_yy = new float[Rp*Jp];
		matrix_mult_trans(&area_data, AA, 1, 60, 80, &area_yy);

		for (int i = 0; i < Rp; i++) {
			for (int j = 0; j < Jp; j++) {
				area_power[i] += pow(area_yy[i*Jp + j], 2);
			}
		}

		float decision_function;		//Решающая функция
		for (int i = 0; i < Rp; i++) {
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

	WaveSound* result_file = new WaveSound();
	result_file->Create(compressed_name, 
						result_data, 
						signal_length, 
						ws->getChannels(), 
						ws->getRate(), 
						ws->getBPS());

	ws->Destroy();
	result_file->Destroy();
	
	delete wav_data;
	delete pause_power;
	delete AA;

	delete ws;
	delete result_file;

	printf("Compression time: %.3f sec.\n", (GetTickCount() - start_tick_count)/1000.f);

	/*float a[] = {
		 0.014372,	 0.002936,	 0.002729,	-0.006935,	 0.034345,	-0.009182,	-0.000265,	 0.000757, 
		 0.009679,	-0.022560,	-0.006974,	-0.012712,	 0.000026,	 0.003752,	 0.005623,	 0.005034, 
		 0.000397,	 0.003751,	-0.000987,	-0.001325,	-0.000874,	-0.001920,	 0.000225,	-0.000162, 
		-0.002897,	-0.001030,	-0.001740,	 0.000463,	-0.000701,	-0.000519,	 0.000740,	 0.000911, 
		 0.002087,	 0.004634,	 0.000796,	 0.002857,	 0.001232,	-0.001783,	 0.000358,	-0.000218,
		 0.001667,	 0.001282,	-0.003026,	 0.003267,	 0.001486,	-0.001802,	-0.000697,	 0.000335,
		 0.001107,	 0.000746,	-0.000313,	-0.000863,	-0.000390,	-0.000165,	-0.000664,	-0.000490,
		 0.001158,	 0.001042,	-0.001261,	-0.000883,	 0.000543,	 0.000995,	-0.000469,	-0.000186, 
		 0.000039,	 0.000960,	 0.000257,	 0.000264,	-0.000481,	-0.000600,	 0.000288,	-0.000577, 
		 0.000742,	 0.000066,	 0.000284,	 0.000123,	 0.001163,	-0.001045,	-0.000007,	 0.000158};

	int quant_lvl_cnt = pow(2.0, BPS);

	int* quant_res = new int[Rs*Js];
	float* Rs_max = new float[Rs];
	bool* s_sign = new bool[Rs*Js];

	memset(quant_res, 0, sizeof(int)*Rs*Js);
	memset(Rs_max, 0, sizeof(float)*Rs);
	memset(s_sign, 0, sizeof(bool)*Rs*Js);

	for (int i = 0; i < Rs; i++) {
		float max = abs(a[i*Js]); 
		for (int j = 0; j < Js; j++) {
			int m_index = i*Js + j;
			if (a[m_index] < 0) s_sign[m_index] = true;

			a[m_index] = abs(a[m_index]);
			if (a[m_index] > max) {
				max = a[m_index];
			}
		}

		for (int j = 0; j < Js; j++) {
			int m_index = i*Js + j;
			float delta = max / (quant_lvl_cnt - 1);
			quant_res[m_index] = floor((a[m_index] / delta) + 0.5); 
			if (s_sign[m_index] = quant_res[m_index] > 0 ? s_sign[m_index] : false) printf("-");
			printf("%d\t", quant_res[m_index]);
		}
		printf("\n");
		Rs_max[i] = max;
	}*/

	return 0;
}