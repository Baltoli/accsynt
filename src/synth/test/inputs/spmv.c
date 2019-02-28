void spmv(float* ov, float* a, float* iv, int* rowstr, int* colidx, int rows)
{
  // RegularLoop over rowstr, ov with size rows
  for (int i = 0; i < rows; ++i) {
    float value = 0.0f;

    // Paired access to rowstr
    int idx_1 = rowstr[i];
    int idx_2 = rowstr[i + 1];

    // Data loop over a, iv here
    // Plus some kind of indexing into iv
    for (int j = idx_1; j < idx_2; j++) {
      value += a[j] * iv[colidx[j]];
    }

    // Regular access to ov
    ov[i] = value;
  }
}
