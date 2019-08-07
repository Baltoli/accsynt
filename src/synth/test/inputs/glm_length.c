#include <math.h>

float length(float* x, int n)
{
  float sum = 0.0f;
  for (int i = 0; i < n; ++i) {
    sum += x[i] * x[i];
  }
  return sqrt(sum);
}
