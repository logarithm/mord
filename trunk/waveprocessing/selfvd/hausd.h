//#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include "nrutil.h"
using namespace std;
 
 
/* максимальное число итераций */
#define MAXITER 30
 
/* Здесь определяются некоторые утилиты типа выделения памяти */
 
 
/* Редукция Хаусхолдера действительной симметричной матрицы a[1...n][1...n]. 
   На выходе a заменяется ортогональной матрицей трансформации q. 
   d[1...n] возвращает диагональ трехдиагональной матрицы. 
   e[1...n] возвращает внедиагональные элементы, причем e[1]=0.   */
 
void tred2(float **a, int n, float *d, float *e) 
{
	int l,k,j,i; 
	float scale,hh,h,g,f; 
	/* Проход по стадиям процесса редукции */ 
	for(i=n-1;i>=1;i--) 
	{ 
		l=i-1; h=scale=0.;
		if(l>1) 
		{ 
			/* вычислить шкалу */
			for(k=0;k<l;k++) scale += fabs(a[i][k]); 
			/* малая величина шкалы -> пропустить преобразование */ 
			if(scale==0.) e[i]=a[i][l]; 
			else 
			{ 
				/* отмасштабировать строку и вычислить s2 в h */ 
				for(k=0;k<l;k++) 
				{ 
					a[i][k]/=scale; h += a[i][k]*a[i][k]; 
				} 
				/* вычислить вектор u */ 
				f=a[i][l];
				g=(f>=0.?-sqrt(h):sqrt(h)); 
				e[i]=scale*g; h -= f*g; 
				/* записать u на место i-го ряда a */ 
				a[i][l]=f-g; 
				/* вычисление u/h, Au, p, K */ 
				f=0.; 
				for(j=0;j<l;j++) 
				{
					a[j][i]=a[i][j]/h; 
					/* сформировать элемент Au (в g) */ 
					g=0.; 
					for(k=0;k<j;k++) g += a[j][k]*a[i][k]; 
					for(k=j+1;k<l;k++) g += a[k][j]*a[i][k]; 
					/* загрузить элемент p во временно неиспользуемую область e */ 
					e[j]=g/h; 
					/* подготовка к формированию K */ 
					f += e[j]*a[i][j]; 
				} 
				/* Сформировать K */ 
				hh=f/(h+h); 
				for(j=0;j<l;j++) 
				{
					/* Сформировать q и поместить на место p (в e) */ 
					f=a[i][j]; e[j]=g=e[j]-hh*f; 
					/* Трансформировать матрицу a */ 
					for(k=0;k<j;k++) a[j][k] -= (f*e[k]+g*a[i][k]); 
				} 
			} 
		} 
		else e[i]=a[i][l]; 
		
		d[i]=h; 
	} 
	d[1]=0.; 
	e[1]=0.; 
	for(i=0;i<n;i++) 
	{
		l=i-1; 
		/* этот блок будет пропущен при i=1 */ 
		if(d[i]!=0.) 
		{
			for(j=0;j<l;j++) 
			{ 
				g=0.; 
				/* формируем PQ, используя u и u/H */ 
				for(k=0;k<l;k++) g += a[i][k]*a[k][j]; 
				for(k=0;k<l;k++) a[k][j] -= g*a[k][i]; 
			} 
		} 
		d[i]=a[i][i]; 
		/* ряд и колонка матрицы a преобразуются к единичной, для след. итерации */ 
		a[i][i]=0.; 
		for(j=0;j<l;j++) a[j][i]=a[i][j]=0.; 
	} 
}

/* QL-алгоритм с неявными сдвигами для определения собственных значений (и собственных
   векторов) действительной, симметричной, трехдиагональной матрицы. Эта матрица может
   быть предварительно получена с помощью программы tred2. На входе d[1...n] содержит
   диагональ исходной матрицы, на выходе - собственные значения. На входе e[1...n]
   содержит поддиагональные элементы, начиная с e[2]. На выходе массив e разрушается.
   При необходимости поиска только собственных значений в программе следует
   закомментировать или удалить инструкции, необходимые только для поиска собственных
   векторов. Если требуются собственные вектора трехдиагональной матрицы, массив
   z[1...n][1...n] необходимо инициализировать на входе единичной матрицей. Если
   требуются собственные вектора матрицы, сведенной к трехдиагональному виду с помощью
   программы tred2, в массив z требуется загрузить соответствующий выход tred2. В
   обоих случаях на выходе массив z возвращает матрицу собственных векторов, расположенных
   по столбцам.
*/
 
/* максимальное число итераций */
#define MAXITER 30
 
void tqli(float *d, float *e, int n, float **z) 
{
	int m,l,iter,i,k;
	float s,r,p,g,f,dd,c,b;
	/* удобнее будет перенумеровать элементы e */
	for(i=1;i<n;i++) e[i-1]=e[i];
	
	e[n]=0.;
	/* главный цикл идет по строкам матрицы */
	for(l=0;l<n;l++) 
	{
		/* обнуляем счетчик итераций для этой строки */
		iter=0;
		/* цикл проводится, пока минор 2х2 в левом верхнем углу начиная со строки l
		не станет диагональным */
		do 
		{
			/* найти малый поддиагональный элемент, дабы расщепить матрицу */
			for(m=l;m<n-1;m++) 
			{
				dd=fabs(d[m])+fabs(d[m+1]);
				if((float)(fabs(e[m]+dd)==dd)) break;
			}
			/* операции проводятся, если верхний левый угол 2х2 минора еще не диагональный */
			if(m!=l) 
			{
				/* увеличить счетчик итераций и посмотреть, не слишком ли много. Функция
					nerror завершает программу с диагностикой ошибки. */
				if(++iter>=MAXITER) {cout<<"Error!!!"; return;};
				/* сформировать сдвиг */
				g=(d[l+1]-d[l])/(2.*e[l]); r=hypot(1.,g);
				/* здесь d_m - k_s */
				if(g>=0.) g+=fabs(r);
				else g-=fabs(r);
        
				g=d[m]-d[l]+e[l]/g;
				/* инициализация s,c,p */
				s=c=1.; p=0.;
				/* плоская ротация оригинального QL алгоритма, сопровождаемая ротациями
					Гивенса для восстановления трехдиагональной формы */
				for(i=m-1;i>=l;i--) 
				{
					f=s*e[i]; b=c*e[i];
					e[i+1]=r=hypot(f,g);
					/* что делать при малом или нулевом знаменателе */
					if(r==0.) {d[i+1]-=p; e[m]=0.; break;}
					/* основные действия на ротации */
					s=f/r; c=g/r; g=d[i+1]-p; r=(d[i]-g)*s+2.*c*b; d[i+1]=g+(p=s*r); g=c*r-b;
				}
				/* безусловный переход к новой итерации при нулевом знаменателе и недоведенной
					до конца последовательности ротаций */
				if(r==0. && i>=l) continue;
				/* новые значения на диагонали и "под ней" */
				d[l]-=p; e[l]=g; e[m]=0.;
			}
		} 
		while(m!=l);
	}
}
 
#ifndef _NR_UTILS_H_
#define _NR_UTILS_H_
   
static float sqrarg;
#define SQR(a) ((sqrarg=(a)) == 0.0 ? 0.0 : sqrarg*sqrarg)
   
static double dsqrarg;
#define DSQR(a) ((dsqrarg=(a)) == 0.0 ? 0.0 : dsqrarg*dsqrarg)
   
static double dmaxarg1,dmaxarg2;
#define DMAX(a,b) (dmaxarg1=(a),dmaxarg2=(b),(dmaxarg1) > (dmaxarg2) ?\
        (dmaxarg1) : (dmaxarg2))
   
static double dminarg1,dminarg2;
#define DMIN(a,b) (dminarg1=(a),dminarg2=(b),(dminarg1) < (dminarg2) ?\
        (dminarg1) : (dminarg2))
   
 
static float maxarg1,maxarg2;
#define FMAX(a,b) (maxarg1=(a),maxarg2=(b),(maxarg1) > (maxarg2) ?\
        (maxarg1) : (maxarg2))
   
static float minarg1,minarg2;
#define FMIN(a,b) (minarg1=(a),minarg2=(b),(minarg1) < (minarg2) ?\
        (minarg1) : (minarg2))
   
static long lmaxarg1,lmaxarg2;
#define LMAX(a,b) (lmaxarg1=(a),lmaxarg2=(b),(lmaxarg1) > (lmaxarg2) ?\
        (lmaxarg1) : (lmaxarg2))
   
   
static int iminarg1,iminarg2;
#define IMIN(a,b) (iminarg1=(a),iminarg2=(b),(iminarg1) < (iminarg2) ?\
        (iminarg1) : (iminarg2))
   
#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))
   
void nrerror(char error_text[]);
float *vector(long nl, long nh);
int *ivector(long nl, long nh);
unsigned char *cvector(long nl, long nh);
unsigned long *lvector(long nl, long nh);
double *dvector(long nl, long nh);
 
float **matrix(long nrl, long nrh, long ncl, long nch);
double **dmatrix(long nrl, long nrh, long ncl, long nch);
int **imatrix(long nrl, long nrh, long ncl, long nch);
float **submatrix(float **a, long oldrl, long oldrh, long oldcl, long oldch,
        long newrl, long newcl);
float **convert_matrix(float *a, long nrl, long nrh, long ncl, long nch);
float ***f3tensor(long nrl, long nrh, long ncl, long nch, long ndl, long ndh);
void free_vector(float *v, long nl, long nh);
void free_ivector(int *v, long nl, long nh);
 
void free_cvector(unsigned char *v, long nl, long nh);
void free_lvector(unsigned long *v, long nl, long nh);
void free_dvector(double *v, long nl, long nh);
void free_matrix(float **m, long nrl, long nrh, long ncl, long nch);
void free_dmatrix(double **m, long nrl, long nrh, long ncl, long nch);
void free_imatrix(int **m, long nrl, long nrh, long ncl, long nch);
void free_submatrix(float **b, long nrl, long nrh, long ncl, long nch);
void free_convert_matrix(float **b, long nrl, long nrh, long ncl, long nch);
void free_f3tensor(float ***t, long nrl, long nrh, long ncl, long nch,
        long ndl, long ndh);
   
#endif /* _NR_UTILS_H_ */