void gemv_full(int M, int N, float alpha, float *A, float *x, float beta, float *y)
{
  for(int i = 0; i < M; ++i) {
    float sum = beta * y[i];
    for(int j = 0; j < N; ++j) {
      sum += alpha * A[j + i*N] * x[j];
    }
    y[i] = sum;
  }
}
