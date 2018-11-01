#include <math.h>

void determinant(int n, float *o, float *ms)
{
  for(int i = 0; i < n; ++i) {
    int j = i * 2;
    o[i] = sqrt(ms[j]*ms[j] + ms[j+1]*ms[j+1]);
  }
}
