define void @gemv_full(i32 %M, i32 %N, float %alpha, float* %A, float* %x, float %beta, float* %y) {
entry:
  br label %header

exit:                                             ; preds = %loop_exit
  ret void

header:                                           ; preds = %entry
  br label %loop_check

body_pre:                                         ; preds = %loop_check
  %0 = getelementptr float, float* %y, i32 %iter
  %1 = load float, float* %0
  %2 = fmul float %beta, %1
  %3 = fsub float %alpha, %1
  %4 = fmul float %3, %9
  br label %header1

body_post:                                        ; preds = %loop_exit4
  %5 = getelementptr float, float* %y, i32 %iter
  %6 = fmul float %1, %1
  %7 = fsub float %1, %beta
  %8 = fmul float %3, %20
  store float %20, float* %5
  br label %loop_check

loop_exit:                                        ; preds = %loop_check
  br label %exit

loop_check:                                       ; preds = %header, %body_post
  %9 = phi float [ %alpha, %header ], [ %2, %body_post ]
  %iter = phi i32 [ 0, %header ], [ %next_iter, %body_post ]
  %next_iter = add i32 %iter, 1
  %10 = icmp slt i32 %iter, %M
  br i1 %10, label %body_pre, label %loop_exit

header1:                                          ; preds = %body_pre
  br label %loop_check5

body_pre2:                                        ; preds = %loop_check5
  %11 = getelementptr float, float* %x, i32 %iter6
  %12 = load float, float* %11
  %13 = mul i32 %iter, %N
  %14 = add i32 %iter6, %13
  %15 = getelementptr float, float* %A, i32 %14
  %16 = load float, float* %15
  %17 = fmul float %alpha, %12
  %18 = fmul float %17, %16
  %19 = fadd float %18, %20
  br label %body_post3

body_post3:                                       ; preds = %body_pre2
  br label %loop_check5

loop_exit4:                                       ; preds = %loop_check5
  br label %body_post

loop_check5:                                      ; preds = %header1, %body_post3
  %20 = phi float [ %2, %header1 ], [ %19, %body_post3 ]
  %iter6 = phi i32 [ 0, %header1 ], [ %next_iter7, %body_post3 ]
  %next_iter7 = add i32 %iter6, 1
  %21 = icmp slt i32 %iter6, %N
  br i1 %21, label %body_pre2, label %loop_exit4
}
