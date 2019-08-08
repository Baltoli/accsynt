void abs_(float* x, int n)
{
  for (int i = 0; i < n; ++i) {
    x[i] = (x[i] > 0.0f ? x[i] : -x[i]);
  }
}
