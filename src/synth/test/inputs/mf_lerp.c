void lerp(float* o, float* x, float* y, float alpha, int n)
{
  for (int i = 0; i < n; ++i) {
    o[i] = x[i] + alpha * (y[i] - x[i]);
  }
}
