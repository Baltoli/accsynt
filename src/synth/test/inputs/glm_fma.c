void fma_(int n, float* a, float* b, float* c)
{
  for (int i = 0; i < n; ++i) {
    a[i] = (a[i] * b[i]) + c[i];
  }
}
