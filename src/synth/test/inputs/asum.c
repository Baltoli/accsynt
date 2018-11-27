#include <math.h>

float asum(int n, float *x)
{
  float sum = 0.0f;
  for(int i = 0; i < n; ++i) {
    sum += fabs(x[i]);
  }
  return sum;
}
