#include <stdio.h>

#include <cmath>
using namespace std;

#include "wavesound.h"

#include "matrix/matrix_processing.h"

const int R = 10;	//���������� ��������� ����������
const int N = 60;	//������ ������ (���� �������)
const int J = 8;	//

int main(int argc, char** argv) {
	WaveSound* ws = new WaveSound();
	//char* wav_name = "files/wav/lec02_03_8000.wav";
	char* wav_name = "files/wav/news_studio_8000.wav";;
	ws->Load(wav_name);

	float** AA = new float*[R*J];
	for (int i = 0; i < R*J; i++) 
		AA[i] = new float[N];

	matrix_read("files/matrix/AA_10_60_8.txt", 80, 60, AA);

	int wav_data_length = ws->getAvialible();				//����� ��������� �������

	float* wav_data = new float[wav_data_length];			//�������� ������
	ws->ReadFlt(wav_data, wav_data_length);

	float wav_mean = matrix_mean(&wav_data, 1, wav_data_length);
	
	int area_count = (int)ceil(wav_data_length / (float)N);	//���������� ������������� ��������
	int area_counter = 0;									//���������� ������������ ��������
	int sample_counter = 0;
	int pause_boundary = 20;								//����� ��� �������� �������

	/*===================== ���������� ������� ����� ======================= */
	float* pause_power = new float[R];
	memset(pause_power, 0, sizeof(float) * R);

	float* pause_data = new float[N];
	memcpy(pause_data, wav_data, sizeof(float)*N);
	float pause_mean = matrix_mean(&pause_data, 1, 60);

	for (int i = 0; i < N; i++) 
			pause_data[i] = pause_data[i] - pause_mean;

	float* pause_yy = new float[R*J];
	matrix_mult_trans(&pause_data, AA, 1, 60, 80, &pause_yy);
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < J; j++) {
			pause_power[i] += pow(pause_yy[i*R + j], 2);
		}
	}

	delete pause_data;
	delete pause_yy;
	/*===================== ��������� ���������� ������� ����� ======================= */

	int signal_area_count = 0;
	int signal_length = 0;
	int pause_area_count = 0;
	
	float* result_data = new float[wav_data_length];			//���������� ������

	for (int curr_area = 0; curr_area < area_count; curr_area++) {
		int area_length = (curr_area + 1)*N > wav_data_length ? wav_data_length - (curr_area)*N : N;

		float* area_data = new float[area_length];			//�����	
		memcpy(area_data, wav_data+(curr_area*N), sizeof(float)*area_length);		
		
		float area_mean = matrix_mean(&area_data, 1, area_length);

		//������ ����� �������
		for (int i = 0; i < area_length; i++) 
			area_data[i] = area_data[i] - area_mean;
		
		//���������� ������� �������
		float* area_power = new float[R];
		memset(area_power, 0, sizeof(float) * R);
		
		float* area_yy = new float[R*J];
		matrix_mult_trans(&pause_data, AA, 1, 60, 80, &area_yy);

		for (int i = 0; i < R; i++) {
			for (int j = 0; j < J; j++) {
				area_power[i] += pow(area_yy[i*R + j], 2);
			}
		}

		float decision_function;		//�������� �������
		for (int i = 0; i < R; i++) {
			area_power[i] /= (float) pause_power[i];
			decision_function = (i == 0 || area_power[i] > decision_function) ? area_power[i] : decision_function;
		}

		
		if (decision_function > pause_boundary) {		//������
			signal_area_count++;

			memcpy(result_data + signal_length, area_data, sizeof(float)*area_length); //����������� ������ � �������� ����
			signal_length += area_length;
		}
		else {											//�����
			pause_area_count++;
		}
		
		delete area_yy;
		delete area_data;
		delete area_power;
		area_counter++;
	}
	
	ws->Destroy();

	WaveSound* result_file = new WaveSound();
	result_file->Create("files/wav/news_studio_8000_compressed.wav", result_data, signal_length, 1, 8000, 16);
	//result_file->Create("files/wav/news_studio_8000_compressed.wav", wav_data, wav_data_length, 1, 8000, 16);
	
	delete wav_data;
	delete pause_power;
	delete AA;

	delete ws;
	delete result_file;

	return 0;
}