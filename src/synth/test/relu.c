void relu(int n, float *in, float *o)
{
  for(int i = 0; i < n; ++i) {
    o[i] = in[i] < 0 ? 0 : in[i];
  }
}
