void saxpy(int n, float a, float *x, float *y)
{
  for(int i = 0; i < n; ++i) {
    y[i] = a*x[i] + y[i];
  }
}
