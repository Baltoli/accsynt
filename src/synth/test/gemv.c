void gemv(int M, int N, float *A, float *x, float *y)
{
  for(int i = 0; i < M; ++i) {
    float sum = 0;
    for(int j = 0; j < N; ++j) {
      sum += A[i + j*M] * x[j];
    }
    y[i] = sum;
  }
}
