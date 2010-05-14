#ifndef _MATRIX_PROCESSING_
#define _MATRIX_PROCESSING_

#include <string.h>
#include <stdio.h>
#include <unistd.h>

void matrix_read (char* file_name, int size_x, int size_y, float** matrix, char* el_format = "%f\\t", char* str_sep = "\\n")
{
        FILE * src_file = fopen(file_name, "rb");

	if (!src_file) {
                fclose(src_file);
		return;
	}

	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			fscanf(src_file, el_format, &matrix[i][j]);
		}
		fscanf(src_file, str_sep);
	}

	fclose(src_file);

	return;
}

//size_x и size_y - размеры матрицы А
void matrix_mult(float** A, float** B, int sizeA_x, int sizeA_y, int sizeB_y, float** result) {	
	for (int i = 0; i < sizeA_x; i++) {
		for (int j = 0; j < sizeB_y; j++) {
			result[i][j] = 0;
			for (int k = 0; k < sizeA_y; k++) {
				result[i][j] += A[i][k]*B[k][j];
			}
		}
	}
}

//Используется, в случае если надо умножить на транспонированную матрицу В
void matrix_mult_trans(float** A, float** B, int sizeA_x, int sizeA_y, int sizeB_x, float** result) {
	for (int i = 0; i < sizeA_x; i++) {
		for (int j = 0; j < sizeB_x; j++) {
			result[i][j] = 0;
			for (int k = 0; k < sizeA_y; k++) {
				result[i][j] += A[i][k]*B[j][k];
			}
		}
	}
}

bool matrix_compare(float** A, float** B, int size_x, int size_y) {
	bool result = true;
	for (int i = 0; i < size_x; i++) 
		result = result && (memcmp(A[i], B[i], sizeof(float)*size_y) == 0);

	return result;
}

float matrix_mean(float** A, int size_x, int size_y) {
	float sum = 0;
	for (int i = 0; i < size_x; i++) 
		for (int j = 0; j < size_y; j++)
			sum += A[i][j];

	return sum / (float)(size_x*size_y);
}

#endif
