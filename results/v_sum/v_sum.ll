define float @v_sum(i32 %n, float* %x) {
entry:
  br label %header

exit:                                             ; preds = %loop_exit
  ret float %5

header:                                           ; preds = %entry
  br label %loop_check

body_pre:                                         ; preds = %loop_check
  %0 = getelementptr float, float* %x, i32 %iter
  %1 = load float, float* %0
  %2 = fmul float %1, %5
  %3 = fadd float %1, %1
  %4 = fadd float %5, %1
  br label %body_post

body_post:                                        ; preds = %body_pre
  br label %loop_check

loop_exit:                                        ; preds = %loop_check
  br label %exit

loop_check:                                       ; preds = %header, %body_post
  %5 = phi float [ 0.000000e+00, %header ], [ %4, %body_post ]
  %iter = phi i32 [ 0, %header ], [ %next_iter, %body_post ]
  %next_iter = add i32 %iter, 1
  %6 = icmp slt i32 %iter, %n
  br i1 %6, label %body_pre, label %loop_exit
}
