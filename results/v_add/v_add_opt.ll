; ModuleID = 'results/v_add/v_add.ll'
source_filename = "results/v_add/v_add.ll"

; Function Attrs: norecurse nounwind
define void @v_add(i32 %n, float* nocapture readonly %x, float* nocapture readonly %y, float* nocapture %o) local_unnamed_addr #0 {
entry:
  %0 = icmp sgt i32 %n, 0
  br i1 %0, label %body_pre.preheader, label %loop_exit

body_pre.preheader:                               ; preds = %entry
  br label %body_pre

body_pre:                                         ; preds = %body_pre.preheader, %body_pre
  %iter1 = phi i32 [ %next_iter, %body_pre ], [ 0, %body_pre.preheader ]
  %next_iter = add nuw nsw i32 %iter1, 1
  %1 = zext i32 %iter1 to i64
  %2 = getelementptr float, float* %x, i64 %1
  %3 = load float, float* %2, align 4
  %4 = getelementptr float, float* %y, i64 %1
  %5 = load float, float* %4, align 4
  %6 = getelementptr float, float* %o, i64 %1
  %7 = fadd float %3, %5
  store float %7, float* %6, align 4
  %8 = icmp slt i32 %next_iter, %n
  br i1 %8, label %body_pre, label %loop_exit

loop_exit:                                        ; preds = %body_pre, %entry
  ret void
}

attributes #0 = { norecurse nounwind }
