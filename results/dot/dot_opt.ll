; ModuleID = 'dot.ll'
source_filename = "dot.ll"

; Function Attrs: norecurse nounwind readonly
define float @dot(i32 %n, float* nocapture readonly %a, float* nocapture readonly %b) local_unnamed_addr #0 {
entry:
  %0 = icmp sgt i32 %n, 0
  br i1 %0, label %body.preheader, label %loop_exit

body.preheader:                                   ; preds = %entry
  br label %body

body:                                             ; preds = %body.preheader, %body
  %iter1 = phi i32 [ %next_iter, %body ], [ 0, %body.preheader ]
  %1 = phi float [ %8, %body ], [ 0.000000e+00, %body.preheader ]
  %next_iter = add nuw nsw i32 %iter1, 1
  %2 = zext i32 %iter1 to i64
  %3 = getelementptr float, float* %a, i64 %2
  %4 = load float, float* %3, align 4
  %5 = getelementptr float, float* %b, i64 %2
  %6 = load float, float* %5, align 4
  %7 = fmul float %4, %6
  %8 = fadd float %1, %7
  %9 = icmp slt i32 %next_iter, %n
  br i1 %9, label %body, label %loop_exit

loop_exit:                                        ; preds = %body, %entry
  %.lcssa = phi float [ 0.000000e+00, %entry ], [ %8, %body ]
  ret float %.lcssa
}

attributes #0 = { norecurse nounwind readonly }
