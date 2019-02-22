float vsum(float* input, int n)
{
  float sum = 0.0f;
  for (int i = 0; i < n; ++i) {
    sum += input[i];
  }
  return sum;
}
