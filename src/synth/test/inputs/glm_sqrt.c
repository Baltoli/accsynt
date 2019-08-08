#include <math.h>

void sqrt_(float* x, int n)
{
  for (int i = 0; i < n; ++i) {
    x[i] = sqrt(x[i]);
  }
}
