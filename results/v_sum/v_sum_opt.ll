; ModuleID = 'results/v_sum/v_sum.ll'
source_filename = "results/v_sum/v_sum.ll"

; Function Attrs: norecurse nounwind readonly
define float @v_sum(i32 %n, float* nocapture readonly %x) local_unnamed_addr #0 {
entry:
  %0 = icmp sgt i32 %n, 0
  br i1 %0, label %body_pre.preheader, label %loop_exit

body_pre.preheader:                               ; preds = %entry
  br label %body_pre

body_pre:                                         ; preds = %body_pre.preheader, %body_pre
  %iter1 = phi i32 [ %next_iter, %body_pre ], [ 0, %body_pre.preheader ]
  %1 = phi float [ %5, %body_pre ], [ 0.000000e+00, %body_pre.preheader ]
  %next_iter = add nuw nsw i32 %iter1, 1
  %2 = zext i32 %iter1 to i64
  %3 = getelementptr float, float* %x, i64 %2
  %4 = load float, float* %3, align 4
  %5 = fadd float %1, %4
  %6 = icmp slt i32 %next_iter, %n
  br i1 %6, label %body_pre, label %loop_exit

loop_exit:                                        ; preds = %body_pre, %entry
  %.lcssa = phi float [ 0.000000e+00, %entry ], [ %5, %body_pre ]
  ret float %.lcssa
}

attributes #0 = { norecurse nounwind readonly }
