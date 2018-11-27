float dot(int n, float *a, float *b)
{
  float sum = 0.f;
  for(int i = 0; i < n; ++i) {
    sum += a[i] * b[i];
  }
  return sum;
}
