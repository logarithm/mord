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
	//======================= Default values =======================//
	int Rp = 10;	//Количество частотных диапазонов для паузы
	int Np = 60;	//Размер фрейма (окна анализа) для паузы
	int P = 100;	//Количество фреймов которые считаются паузой
	int p = 0;		//Количество отсчетов от начала файла до начала паузы
	unsigned short BPS = 7;	//Количество разрядов квантования


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

	float** AAp = new float*[Rp*Jp];
	for (int i = 0; i < Rp*Jp; i++) 
		AAp[i] = new float[Np];	
	matrix_read(matrix_a_path, Rp*Jp, Np, AAp);

	float** AAs = new float*[Rs*Js];
	for (int i = 0; i < Rs*Js; i++) 
		AAs[i] = new float[Ns];
	matrix_read(matrix_a_path, Rs*Js, Ns, AAs);

	int wav_data_length = ws->getAvialible();				//Длина исходного сигнала

	float* wav_data = new float[wav_data_length];			//Исходный сигнал
	ws->ReadFlt(wav_data, wav_data_length);

	float wav_mean = matrix_mean(&wav_data, 1, wav_data_length);
	
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
		matrix_mult_trans(&pause_data, AAp, 1, 60, 80, &pause_yy);
		
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

	int area_count = (int)ceil(wav_data_length / (float)Np);	//Количество анализируемых отрезков
	int area_counter = 0;									//Количество обработанных отрезков
	int pause_boundary = 20;								//Порог для решающей функции

	int signal_area_count = 0;
	int signal_length = 0;
	int pause_area_count = 0;
	int pause_segment_count = 0;
	
	float* result_data = new float[wav_data_length];			//Полученный сигнал	

	unsigned short* pause_map = new unsigned short[ceil(area_count/2.0) * 2];
	bool last_pause = false;
	int pause_section_length = 0;
	int last_pause_segment_area_index = 0;
	int prev_last_pause_segment_area_index = 0;

	//===================== Определение участков пауз ======================= //
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
		matrix_mult_trans(&area_data, AAp, 1, area_length, Rp*Jp, &area_yy);

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

			if (last_pause) {
				if (last_pause_segment_area_index > 0) {
					pause_map[(pause_segment_count - 1)*2] = ((last_pause_segment_area_index + 1)- pause_section_length) - prev_last_pause_segment_area_index;
					pause_map[(pause_segment_count - 1)*2 + 1] = pause_section_length;

					prev_last_pause_segment_area_index = last_pause_segment_area_index;
				}
			}

			last_pause = false;
		}
		else {											//Пауза
			pause_area_count++;

			if (!last_pause) {
				pause_section_length = 0;
				pause_segment_count++;
			}

			
			pause_section_length++;
			last_pause_segment_area_index = curr_area;
			last_pause = true;
		}
		
		delete area_yy;
		delete area_data;
		delete area_power;
		area_counter++;
	}

	if (last_pause) {
		pause_map[(pause_segment_count - 1)*2] = ((last_pause_segment_area_index + 1)- pause_section_length) - prev_last_pause_segment_area_index;
		pause_map[(pause_segment_count - 1)*2 + 1] = pause_section_length;
	}

	// ===================== Субполосное кодирование и квантование ======================= //
	area_count = (int)ceil(signal_length / (float)Ns);
	area_counter = 0;	

	unsigned short* quant_res = new unsigned short[Rs*Js];
	float* Rs_max = new float[Rs];
	bool* s_sign = new bool[Rs*Js];

	Frame* frames = new Frame[area_count];

	for (int curr_area = 0; curr_area < area_count; curr_area++) {
		int area_length = (curr_area + 1)*Ns > signal_length ? signal_length - (curr_area)*Ns : Ns;

		float* area_data = new float[area_length];			//Семпл	
		memcpy(area_data, result_data+(curr_area*Ns), sizeof(float)*area_length);		
		
		float area_mean = matrix_mean(&area_data, 1, area_length);

		//Сигнал минус среднее
		for (int i = 0; i < area_length; i++) 
			area_data[i] = area_data[i] - area_mean;
		
		float* area_yy = new float[Rs*Js]; //Субполосный вектор
		matrix_mult_trans(&area_data, AAs, 1, area_length, Rs*Js, &area_yy);

		//Квантование
		memset(quant_res, 0, sizeof(short)*Rs*Js);
		memset(Rs_max, 0, sizeof(float)*Rs);
		memset(s_sign, 0, sizeof(bool)*Rs*Js);

		int quant_lvl_cnt = pow(2.0, BPS);

		for (int i = 0; i < Rs; i++) {
			float max = abs(area_yy[i*Js]);
			//Вычисление максимума для частотного интервала и знаков числа
			for (int j = 0; j < Js; j++) {
				int m_index = i*Js + j;
				if (area_yy[m_index] < 0) s_sign[m_index] = true;

				area_yy[m_index] = abs(area_yy[m_index]);
				if (area_yy[m_index] > max) {
					max = area_yy[m_index];
				}
			}

			for (int j = 0; j < Js; j++) {
				int m_index = i*Js + j;
				float delta = max / (quant_lvl_cnt - 1);
				quant_res[m_index] = floor((area_yy[m_index] / delta) + 0.5); 
			}
			Rs_max[i] = max;
		}

		frames[curr_area] = Frame(Rs, Ns, BPS, Rs_max, quant_res, s_sign);
		
		delete area_yy;
		delete area_data;
		area_counter++;
	}

	FrameContainer frameContainer(frames, area_count);

	saveCompressFile("files/wav/destination.cwf", wav_data_length, ws->getBPS(), Rp, Np, Rs, Ns, BPS, pause_segment_count, pause_map, frameContainer);
	

	/*WaveSound* result_file = new WaveSound();
	result_file->Create(compressed_name, 
						result_data, 
						signal_length, 
						ws->getChannels(), 
						ws->getRate(), 
						ws->getBPS());

	result_file->Destroy();
	delete result_file;*/

	ws->Destroy();	

	delete quant_res;
	delete Rs_max;
	delete s_sign;
	delete wav_data;
	delete pause_power;
	delete AAp;
	delete AAs;

	delete ws;

	//int a;
	//scanf("%d", &a);
	printf("Compression time: %.3f sec.\n", (GetTickCount() - start_tick_count)/1000.f);

	readCompressFile("files/wav/destination.cwf");
	return 0;
}