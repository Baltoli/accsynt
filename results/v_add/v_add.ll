define void @v_add(i32 %n, float* %x, float* %y, float* %o) {
entry:
  br label %header

exit:                                             ; preds = %loop_exit
  ret void

header:                                           ; preds = %entry
  br label %loop_check

body_pre:                                         ; preds = %loop_check
  %0 = getelementptr float, float* %x, i32 %iter
  %1 = load float, float* %0
  %2 = getelementptr float, float* %y, i32 %iter
  %3 = load float, float* %2
  %4 = getelementptr float, float* %o, i32 %iter
  %5 = load float, float* %4
  %6 = fmul float %10, %5
  %7 = fadd float %3, %1
  %8 = fadd float %1, %10
  br label %body_post

body_post:                                        ; preds = %body_pre
  %9 = getelementptr float, float* %o, i32 %iter
  store float %7, float* %9
  br label %loop_check

loop_exit:                                        ; preds = %loop_check
  br label %exit

loop_check:                                       ; preds = %header, %body_post
  %10 = phi float [ 0.000000e+00, %header ], [ %6, %body_post ]
  %iter = phi i32 [ 0, %header ], [ %next_iter, %body_post ]
  %next_iter = add i32 %iter, 1
  %11 = icmp slt i32 %iter, %n
  br i1 %11, label %body_pre, label %loop_exit
}
