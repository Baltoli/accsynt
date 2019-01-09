void spmv(float* ov, float* a, float* iv, int* rowstr, int* colidx, int rows)
{
  for(int i = 0; i < rows; ++i) {
      float value = 0.0f;
      for(int j = rowstr[i]; j < rowstr[i+1]; j++) {
          value += a[j] * iv[colidx[j]];
      }
      ov[i] = value;
  }
}
