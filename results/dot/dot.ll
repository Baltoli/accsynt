define float @dot(i32 %n, float* %a, float* %b) {
entry:
  br label %header

exit:                                             ; preds = %loop_exit
  %0 = fsub float %9, %12
  %1 = fmul float %0, %0
  ret float %10

header:                                           ; preds = %entry
  br label %loop-check

body:                                             ; preds = %loop-check
  %2 = getelementptr float, float* %a, i32 %iter
  %3 = load float, float* %2
  %4 = getelementptr float, float* %b, i32 %iter
  %5 = load float, float* %4
  %6 = fmul float %3, %5
  %7 = fadd float %10, %6
  br label %loop-check

loop_exit:                                        ; preds = %loop-check
  %8 = fsub float %12, %10
  %9 = fmul float %12, %13
  br label %exit

loop-check:                                       ; preds = %header, %body
  %10 = phi float [ 0.000000e+00, %header ], [ %7, %body ]
  %iter = phi i32 [ 0, %header ], [ %next_iter, %body ]
  %next_iter = add i32 %iter, 1
  %11 = icmp slt i32 %iter, %n
  %12 = fsub float %10, %10
  %13 = fadd float %12, %12
  br i1 %11, label %body, label %loop_exit
}
