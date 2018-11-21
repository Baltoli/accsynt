void bias(float b, int n, float *x)
{
  for(int i = 0; i < n; ++i) {
    x[i] += b;
  }
}
