void vec2sum(int n, float *o, float *vs)
{
  for(int i = 0; i < n; ++i) {
    int base = 2*i;
    o[i] = vs[base] + vs[base+1];
  }
}
