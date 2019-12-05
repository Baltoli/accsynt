define float @func(float %arg0, float %arg1, float %arg2) {
  %v0 = fadd float %arg0, %arg1
  %v1 = fadd float %v0, %arg2
  %v2 = fmul float %v1, %arg1
  %v3 = fadd float %v2, %arg2
  %v4 = fadd float %arg0, %arg1
  %v5 = fmul float %v3, %v4
  ret float %v5
}
