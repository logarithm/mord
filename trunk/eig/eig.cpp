// eig.cpp : Defines the entry point for the console application.

#include "stdafx.h"
//#include "eig.h"
#include "selfVD.h"

//#define M_PI 3.14159

//__inline float GetA(int i,int j, int r, int R)
//{
//  float sigma = M_PI/R;    
//  return (i==j) ? (sigma/M_PI) : (sin(r*sigma*(i-j))-sin((r-1)*sigma*(i-j)))/(i-j)/M_PI;
//} 

int _tmain(int argc, _TCHAR* argv[])
{
	int N = 128;
	int R = 16;

	float** Q = new float* [N+1];
	for (int i = 0; i < N+1; i++) Q[i] = new float[N+1];

	float* L = new float[N+1];

	selfVD(N, R, 5, Q, L);

	printf("\n\n\n---------------\n");
	printf("D[]=");
	for(int i = 1; i < N + 1; i++) printf("%e ",L[i]);
	printf("\n");
	delete L;
	 
	printf("A[][]=\n");
	for(int i=1;i<N+1;i++)
	{
		for(int j=1;j<N+1;j++) printf("%e ", Q[i][j]);printf("\n");
	} 	 
	for(int i=0; i<N+1; i++) 
		delete Q[i];
	delete Q;
	scanf("sdsd");
	//int N = 128;
	//int R = 16; 
	//float** A; 

	//for(int r=0; r<R; r++)
	//{        
	//	A = new float*[N];
	//	for(int i=0; i<N; i++)
	//	{
	//		A[i] = new float[N];
	//		for(int j=0; j<N; j++)
	//		{
	//			A[i][j] = GetA(i,j,r,R);
	//		}
	//	}
	//}
 // 
	//// ну вот имеется A
	//const int n = N; 
	//int i, j;
	//float z;
	//float **a;
	//a=new float*[n+1];
	//for(i = 0; i < n + 1; i++) a[i]=new float[n+1];
	//for(int p = 0; p < n; p++) 
	//	for(int t = 0; t < n; t++) 
	//		a[p][t] = A[p][t];
	//// эта я не убрал всвязи с тем что впадл было переименовывать в коде a на A
	//// и еще потом она обнулится и в нее же запишется результат, так что копировать массив нада

	// 
	////float d[n+1],e[n+1];
	//float *d,*e;
	//d = new float[n + 1];
	//e = new float[n + 1];
	//for(i=0; i<n+1; i++) d[i]=e[i]=0;
	//tred2(a, n, d, e); // это приведение матрицы к трехдиагональному виду
	//	
	//// обнуление
	//for(i=0;i<n+1;i++)
	//	for(j=0;j<n+1;j++)
	//		a[i][j]=0;
	// 
	////заполнение диагональных
	//for(i=1;i<n+1;i++) a[i][i]=d[i];
	// 
	////заполнение поддиагональных
	//for(i=1;i<n;i++) a[i+1][i]=e[i+1];
	// 
	//tqli(d, e, n, a); // это непосредственно получение сч и св
	//// после трансформации d - сч, a - св
	// 
	//printf("\n\n\n---------------\n");
	//printf("D[]=");
	//for(i = 1; i < n + 1; i++) printf("%e ",d[i]);
	//printf("\n");
	// 
	//printf("A[][]=\n");
	//for(i=1;i<n+1;i++)
	//{
	//	for(j=1;j<n+1;j++) printf("%e ", a[i][j]);printf("\n");
	//} 	 
	//for(i=0; i<n+1; i++) 
	//	delete a[i];
	//delete a;
	//scanf("sdsd");  

	////float** Q; float* L;int cou;
	////jacobi(A,N,L,Q,cou);

	//return 0;
}