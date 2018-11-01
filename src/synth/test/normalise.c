void norm(int n, float *in, float *out)
{
  float sum = 0;
  for(int i = 0; i < n; ++i) {
    sum += in[i];
  }

  for(int i = 0; i < n; ++i) {
    out[i] = in[i] / sum;
  }
}
