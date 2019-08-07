void negate(float* x, int n)
{
  for (int i = 0; i < n; ++i) {
    x[i] = 0.0f - x[i];
  }
}
