//#include "stdafx.h"
#include <math.h>
#include <iostream>
#include <fstream>
#include "nrutil.h"
using namespace std;
 
 
/* ������������ ����� �������� */
#define MAXITER 30
 
/* ����� ������������ ��������� ������� ���� ��������� ������ */
 
 
/* �������� ����������� �������������� ������������ ������� a[1...n][1...n]. 
   �� ������ a ���������� ������������� �������� ������������� q. 
   d[1...n] ���������� ��������� ���������������� �������. 
   e[1...n] ���������� ��������������� ��������, ������ e[1]=0.   */
 
void tred2(float **a, int n, float *d, float *e) 
{
	int l,k,j,i; 
	float scale,hh,h,g,f; 
	/* ������ �� ������� �������� �������� */ 
	for(i=n-1;i>=1;i--) 
	{ 
		l=i-1; h=scale=0.;
		if(l>1) 
		{ 
			/* ��������� ����� */
			for(k=0;k<l;k++) scale += fabs(a[i][k]); 
			/* ����� �������� ����� -> ���������� �������������� */ 
			if(scale==0.) e[i]=a[i][l]; 
			else 
			{ 
				/* ���������������� ������ � ��������� s2 � h */ 
				for(k=0;k<l;k++) 
				{ 
					a[i][k]/=scale; h += a[i][k]*a[i][k]; 
				} 
				/* ��������� ������ u */ 
				f=a[i][l];
				g=(f>=0.?-sqrt(h):sqrt(h)); 
				e[i]=scale*g; h -= f*g; 
				/* �������� u �� ����� i-�� ���� a */ 
				a[i][l]=f-g; 
				/* ���������� u/h, Au, p, K */ 
				f=0.; 
				for(j=0;j<l;j++) 
				{
					a[j][i]=a[i][j]/h; 
					/* ������������ ������� Au (� g) */ 
					g=0.; 
					for(k=0;k<j;k++) g += a[j][k]*a[i][k]; 
					for(k=j+1;k<l;k++) g += a[k][j]*a[i][k]; 
					/* ��������� ������� p �� �������� �������������� ������� e */ 
					e[j]=g/h; 
					/* ���������� � ������������ K */ 
					f += e[j]*a[i][j]; 
				} 
				/* ������������ K */ 
				hh=f/(h+h); 
				for(j=0;j<l;j++) 
				{
					/* ������������ q � ��������� �� ����� p (� e) */ 
					f=a[i][j]; e[j]=g=e[j]-hh*f; 
					/* ���������������� ������� a */ 
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
		/* ���� ���� ����� �������� ��� i=1 */ 
		if(d[i]!=0.) 
		{
			for(j=0;j<l;j++) 
			{ 
				g=0.; 
				/* ��������� PQ, ��������� u � u/H */ 
				for(k=0;k<l;k++) g += a[i][k]*a[k][j]; 
				for(k=0;k<l;k++) a[k][j] -= g*a[k][i]; 
			} 
		} 
		d[i]=a[i][i]; 
		/* ��� � ������� ������� a ������������� � ���������, ��� ����. �������� */ 
		a[i][i]=0.; 
		for(j=0;j<l;j++) a[j][i]=a[i][j]=0.; 
	} 
}

/* QL-�������� � �������� �������� ��� ����������� ����������� �������� (� �����������
   ��������) ��������������, ������������, ���������������� �������. ��� ������� �����
   ���� �������������� �������� � ������� ��������� tred2. �� ����� d[1...n] ��������
   ��������� �������� �������, �� ������ - ����������� ��������. �� ����� e[1...n]
   �������� ��������������� ��������, ������� � e[2]. �� ������ ������ e �����������.
   ��� ������������� ������ ������ ����������� �������� � ��������� �������
   ���������������� ��� ������� ����������, ����������� ������ ��� ������ �����������
   ��������. ���� ��������� ����������� ������� ���������������� �������, ������
   z[1...n][1...n] ���������� ���������������� �� ����� ��������� ��������. ����
   ��������� ����������� ������� �������, ��������� � ����������������� ���� � �������
   ��������� tred2, � ������ z ��������� ��������� ��������������� ����� tred2. �
   ����� ������� �� ������ ������ z ���������� ������� ����������� ��������, �������������
   �� ��������.
*/
 
/* ������������ ����� �������� */
#define MAXITER 30
 
void tqli(float *d, float *e, int n, float **z) 
{
	int m,l,iter,i,k;
	float s,r,p,g,f,dd,c,b;
	/* ������� ����� �������������� �������� e */
	for(i=1;i<n;i++) e[i-1]=e[i];
	
	e[n]=0.;
	/* ������� ���� ���� �� ������� ������� */
	for(l=0;l<n;l++) 
	{
		/* �������� ������� �������� ��� ���� ������ */
		iter=0;
		/* ���� ����������, ���� ����� 2�2 � ����� ������� ���� ������� �� ������ l
		�� ������ ������������ */
		do 
		{
			/* ����� ����� ��������������� �������, ���� ��������� ������� */
			for(m=l;m<n-1;m++) 
			{
				dd=fabs(d[m])+fabs(d[m+1]);
				if((float)(fabs(e[m]+dd)==dd)) break;
			}
			/* �������� ����������, ���� ������� ����� ���� 2�2 ������ ��� �� ������������ */
			if(m!=l) 
			{
				/* ��������� ������� �������� � ����������, �� ������� �� �����. �������
					nerror ��������� ��������� � ������������ ������. */
				if(++iter>=MAXITER) {cout<<"Error!!!"; return;};
				/* ������������ ����� */
				g=(d[l+1]-d[l])/(2.*e[l]); r=hypot(1.,g);
				/* ����� d_m - k_s */
				if(g>=0.) g+=fabs(r);
				else g-=fabs(r);
        
				g=d[m]-d[l]+e[l]/g;
				/* ������������� s,c,p */
				s=c=1.; p=0.;
				/* ������� ������� ������������� QL ���������, �������������� ���������
					������� ��� �������������� ���������������� ����� */
				for(i=m-1;i>=l;i--) 
				{
					f=s*e[i]; b=c*e[i];
					e[i+1]=r=hypot(f,g);
					/* ��� ������ ��� ����� ��� ������� ����������� */
					if(r==0.) {d[i+1]-=p; e[m]=0.; break;}
					/* �������� �������� �� ������� */
					s=f/r; c=g/r; g=d[i+1]-p; r=(d[i]-g)*s+2.*c*b; d[i+1]=g+(p=s*r); g=c*r-b;
				}
				/* ����������� ������� � ����� �������� ��� ������� ����������� � ������������
					�� ����� ������������������ ������� */
				if(r==0. && i>=l) continue;
				/* ����� �������� �� ��������� � "��� ���" */
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