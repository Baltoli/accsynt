float offset_sum(int n, float *x, float *y)
{
  float sum = 0.0f;
  for(int i = 0; i < n; ++i) {
    sum += x[i];
    sum += y[i+1];
  }
  return sum;
}
