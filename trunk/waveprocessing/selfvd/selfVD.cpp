#define _USE_MATH_DEFINES

#include <cmath>
#include "stdafx.h"
#include "hausd.h"

__inline float GetA(int i,int j, int r, int R)
{
	float sigma = M_PI/R;    
	return (i==j) ? (sigma/M_PI) : (sin(r*sigma*(i-j))-sin((r-1)*sigma*(i-j)))/(i-j)/M_PI;
} 

//Q и L ДОЛЖНЫ быть размерностью N+1. По словам одного из разработчиков - "метод такой"
//вычитываются они потом от 1 до N+1 элемента, т.е. 0-ой столбец и строка отбрасываются
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
	// эта я не убрал всвязи с тем что впадл было переименовывать в коде a на A
	// и еще потом она обнулится и в нее же запишется результат, так что копировать массив нада

	float *d,*e;
	//d = new float[N + 1];
	e = new float[N];
	for(i = 0; i < N; i++) L[i] = e[i] = 0;
	tred2(Q, N, L, e); // это приведение матрицы к трехдиагональному виду
		
	// обнуление
	for(i = 0; i < N; i++)
		for(j = 0; j < N; j++)
			Q[i][j] = 0;
	 
	//заполнение диагональных
	for(i = 0; i < N; i++) Q[i][i] = L[i];
	 
	//заполнение поддиагональных
	for(i = 0; i < N - 1; i++) Q[i+1][i]=e[i+1];
	 
	tqli(L, e, N, Q); // это непосредственно получение сч и св
	// после трансформации d - сч, a - св

	return;
}