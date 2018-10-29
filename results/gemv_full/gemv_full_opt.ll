; ModuleID = 'results/gemv_full/gemv_full.ll'
source_filename = "results/gemv_full/gemv_full.ll"

; Function Attrs: norecurse nounwind
define void @gemv_full(i32 %M, i32 %N, float %alpha, float* nocapture readonly %A, float* nocapture readonly %x, float %beta, float* nocapture %y) local_unnamed_addr #0 {
entry:
  %0 = icmp sgt i32 %M, 0
  br i1 %0, label %body_pre.lr.ph, label %loop_exit

body_pre.lr.ph:                                   ; preds = %entry
  %1 = icmp sgt i32 %N, 0
  br i1 %1, label %body_pre.us.preheader, label %body_pre.preheader

body_pre.preheader:                               ; preds = %body_pre.lr.ph
  br label %body_pre

body_pre.us.preheader:                            ; preds = %body_pre.lr.ph
  br label %body_pre.us

body_pre.us:                                      ; preds = %body_pre.us.preheader, %loop_check5.loop_exit4_crit_edge.us
  %next_iter3.us = phi i32 [ %next_iter.us, %loop_check5.loop_exit4_crit_edge.us ], [ 1, %body_pre.us.preheader ]
  %iter2.us = phi i32 [ %next_iter3.us, %loop_check5.loop_exit4_crit_edge.us ], [ 0, %body_pre.us.preheader ]
  %2 = sext i32 %iter2.us to i64
  %3 = getelementptr float, float* %y, i64 %2
  %4 = load float, float* %3, align 4
  %5 = fmul float %4, %beta
  %6 = mul i32 %iter2.us, %N
  br label %body_pre2.us

body_pre2.us:                                     ; preds = %body_pre.us, %body_pre2.us
  %iter61.us = phi i32 [ 0, %body_pre.us ], [ %next_iter7.us, %body_pre2.us ]
  %7 = phi float [ %5, %body_pre.us ], [ %17, %body_pre2.us ]
  %next_iter7.us = add nuw nsw i32 %iter61.us, 1
  %8 = zext i32 %iter61.us to i64
  %9 = getelementptr float, float* %x, i64 %8
  %10 = load float, float* %9, align 4
  %11 = add i32 %iter61.us, %6
  %12 = sext i32 %11 to i64
  %13 = getelementptr float, float* %A, i64 %12
  %14 = load float, float* %13, align 4
  %15 = fmul float %10, %alpha
  %16 = fmul float %15, %14
  %17 = fadd float %7, %16
  %18 = icmp slt i32 %next_iter7.us, %N
  br i1 %18, label %body_pre2.us, label %loop_check5.loop_exit4_crit_edge.us

loop_check5.loop_exit4_crit_edge.us:              ; preds = %body_pre2.us
  store float %17, float* %3, align 4
  %next_iter.us = add nuw i32 %next_iter3.us, 1
  %19 = icmp slt i32 %next_iter3.us, %M
  br i1 %19, label %body_pre.us, label %loop_exit

body_pre:                                         ; preds = %body_pre.preheader, %body_pre
  %next_iter3 = phi i32 [ %next_iter, %body_pre ], [ 1, %body_pre.preheader ]
  %iter2 = phi i32 [ %next_iter3, %body_pre ], [ 0, %body_pre.preheader ]
  %20 = sext i32 %iter2 to i64
  %21 = getelementptr float, float* %y, i64 %20
  %22 = load float, float* %21, align 4
  %23 = fmul float %22, %beta
  store float %23, float* %21, align 4
  %next_iter = add nuw i32 %next_iter3, 1
  %24 = icmp slt i32 %next_iter3, %M
  br i1 %24, label %body_pre, label %loop_exit

loop_exit:                                        ; preds = %body_pre, %loop_check5.loop_exit4_crit_edge.us, %entry
  ret void
}

attributes #0 = { norecurse nounwind }
