void ger(int m, int n, float *x, float *y, float *a)
{
  for(int i = 0; i < m; ++i) {
    for(int j = 0; j < n; ++j) {
      a[j + i*n] += x[i] * y[j];
    }
  }
}
