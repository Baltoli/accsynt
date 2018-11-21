float v_sum(int n, float *x)
{
  float sum = 0.0f;
  for(int i = 0; i < n; ++i) {
    sum += x[i];
  }
  return sum;
}
