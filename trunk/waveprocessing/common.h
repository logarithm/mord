#define _USE_MATH_DEFINES
#include "math.h"

/*__inline float GetA(int i,int k,int r, int R)
{
   float sigma = M_PI/R;    
   return (i==k) ? (sigma/M_PI) : (sin(r*sigma*(i-k))-sin((r-1)*sigma*(i-k)))/(i-k)/M_PI;
}

__inline float GetA(int tau, int r, int R)
{
   float sigma = M_PI/R;    
   return (!tau) ? (sigma/M_PI) : (sin(r*sigma*tau)-sin((r-1)*sigma*tau))/tau/M_PI;
}*/


__inline float GetA(int i,int j, int r, int R)
{
   float sigma = M_PI/R;    
   return (i==j) ? (sigma/M_PI) : (sin(r*sigma*(i-j))-sin((r-1)*sigma*(i-j)))/(i-j)/M_PI;
}