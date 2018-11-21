void determinant(int n, float *o, float *ms)
{
  for(int i = 0; i < n; ++i) {
    int j = i * 4;
    o[i] = ms[j]*ms[j+3] - ms[j+1]*ms[j+2];
  }
}
