#include <math.h>
#include <vector>
#include <iostream>
 
using namespace std;
 
#ifndef M_PI 
#define M_PI 3.14159265358979323846
#endif
 
vector<double> FFT(const vector<int>& dIn, int nn, int beginData)
{
	int i, j, n, m, mmax, istep;
	double tempr, tempi, wtemp, theta, wpr, wpi, wr, wi;
 
	int isign = -1;
	vector<double> data(nn*2 + 1);
 
	j = 0;
	for (i = beginData; i < beginData + nn; i++)
	{
		if (i < dIn.size())
		{
			data[j*2]   = 0;
			data[j*2+1] = dIn[i];
		}
		else
		{
			data[j*2]   = 0;
			data[j*2+1] = 0;
		}
		j++;
	}
 
	n = nn << 1;
	j = 1;
	i = 1;
	while (i < n)
	{
		if (j > i)
		{
			tempr = data[i];   data[i]   = data[j];   data[j]   = tempr;
			tempr = data[i+1]; data[i+1] = data[j+1]; data[j+1] = tempr;
		}
		m = n >> 1;
		while ((m >= 2) && (j > m))
		{
			j = j - m;
			m = m >> 1;
		}
		j = j + m;
		i = i + 2;
	}
	mmax = 2;
	while (n > mmax)
	{
		istep = 2 * mmax;
		theta = 2.0*M_PI / (isign * mmax);
		wtemp = sin(0.5 * theta);
		wpr   = -2.0 * wtemp * wtemp;
		wpi   = sin(theta);
		wr    = 1.0;
		wi    = 0.0;
		m    = 1;
		while (m < mmax)
		{
			i = m;
			while (i < n)
			{
				j         = i + mmax;
				tempr     = wr * data[j] - wi * data[j+1];
				tempi     = wr * data[j+1] + wi * data[j];
				data[j]   = data[i] - tempr;
				data[j+1] = data[i+1] - tempi;
				data[i]   = data[i] + tempr;
				data[i+1] = data[i+1] + tempi;
				i         = i + istep;
			}
			wtemp = wr;
			wr    = wtemp * wpr - wi * wpi + wr;
			wi    = wi * wpr + wtemp * wpi + wi;
			m     = m + 2;
		}
		mmax = istep;
	}
	vector<double> dOut(nn / 2);
 
	for (i = 0; i < (nn / 2); i++)
	{
		dOut[i] = sqrt( data[i*2] * data[i*2] + data[i*2+1] * data[i*2+1] );
	}
 
	return dOut;
}