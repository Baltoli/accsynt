void relu(int n, float *o)
{
  for(int i = 0; i < n; ++i) {
    float val = o[i];
    if(o[i] < 0) {
      o[i] = 0.0f;
    }
  }
}
