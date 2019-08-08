#include <math.h>

void invsqrt(float* x, int n)
{
  for (int i = 0; i < n; ++i) {
    x[i] = 1.0f / sqrt(x[i]);
  }
}
