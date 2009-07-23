#define _USE_MATH_DEFINES

#include <cmath>
#include "stdafx.h"
#include "hausd.h"

__inline float GetA(int i,int j, int r, int R)
{
	float sigma = M_PI/R;    
	return (i==j) ? (sigma/M_PI) : (sin(r*sigma*(i-j))-sin((r-1)*sigma*(i-j)))/(i-j)/M_PI;
} 

//Q � L ������ ���� ������������ N+1. �� ������ ������ �� ������������� - "����� �����"
//������������ ��� ����� �� 1 �� N+1 ��������, �.�. 0-�� ������� � ������ �������������
void selfVD(int N, int R, int r, float** Q, float* L)
{
	float** A; 

	A = new float*[N];
	for(int i=0; i<N; i++)
	{
		A[i] = new float[N];
		for(int j=0; j<N; j++)
		{
			A[i][j] = GetA(i,j,r,R);
		}
	}
  
	int i, j;
	
	for(int p = 0; p < N; p++) 
		for(int t = 0; t < N; t++) 
			Q[p][t] = A[p][t];
	// ��� � �� ����� ������ � ��� ��� ����� ���� ��������������� � ���� a �� A
	// � ��� ����� ��� ��������� � � ��� �� ��������� ���������, ��� ��� ���������� ������ ����

	float *d,*e;
	//d = new float[N + 1];
	e = new float[N];
	for(i = 0; i < N; i++) L[i] = e[i] = 0;
	tred2(Q, N, L, e); // ��� ���������� ������� � ����������������� ����
		
	// ���������
	for(i = 0; i < N; i++)
		for(j = 0; j < N; j++)
			Q[i][j] = 0;
	 
	//���������� ������������
	for(i = 0; i < N; i++) Q[i][i] = L[i];
	 
	//���������� ���������������
	for(i = 0; i < N - 1; i++) Q[i+1][i]=e[i+1];
	 
	tqli(L, e, N, Q); // ��� ��������������� ��������� �� � ��
	// ����� ������������� d - ��, a - ��

	return;
}