#include <cmath>
#include <vector>

#ifndef M_PI 
#define M_PI 3.14159265358979323846
#endif

void DFT(float* data, float* res, int length)
{
	float s1, s2;
	for (int i = 0; i < length; i++)
	{
		s1 = s2 = 0;
		for (int k = 0; k < length; k++)
		{
			s1 += data[k] * cos(i*M_PI*k);
			s2 += data[k] * sin(i*M_PI*k);
		}

		res[i] = ((pow(s1, 2) + pow(s2, 2))/length);
	}	
}

//V1=0; V2=pi;
//dV=(V2-V1)/nf;
//    for i=1:nf
//        s1=0; s2=0;
//        for k=1:N
//            s1=s1+X(k)*cos((i-1)*dV*(k-1));
//            s2=s2+X(k)*sin((i-1)*dV*(k-1));
//        end;
//        P_dpf(i,otr)=(s1^2+s2^2)/nf;
//    end;
//    clear i s1 s2 k S