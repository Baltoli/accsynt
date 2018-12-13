float v_sum(int n, float *x, float *y)
{
  float sum = 0.0f;
  for(int i = 0; i < n; ++i) {
    sum += x[i] + y[i];
  }
  return sum;
}
