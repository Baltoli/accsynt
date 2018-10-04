; ModuleID = 'dot.ll'
source_filename = "dot.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define dso_local double @dot(i32, double*, double*) #0 {
  br label %4

; <label>:4:                                      ; preds = %16, %3
  %.01 = phi double [ 0.000000e+00, %3 ], [ %15, %16 ]
  %.0 = phi i32 [ 0, %3 ], [ %17, %16 ]
  %5 = icmp slt i32 %.0, %0
  br i1 %5, label %7, label %6

; <label>:6:                                      ; preds = %4
  br label %18

; <label>:7:                                      ; preds = %4
  %8 = sext i32 %.0 to i64
  %9 = getelementptr inbounds double, double* %1, i64 %8
  %10 = load double, double* %9, align 8, !tbaa !2
  %11 = sext i32 %.0 to i64
  %12 = getelementptr inbounds double, double* %2, i64 %11
  %13 = load double, double* %12, align 8, !tbaa !2
  %14 = fmul double %10, %13
  %15 = fadd double %.01, %14
  br label %16

; <label>:16:                                     ; preds = %7
  %17 = add nsw i32 %.0, 1
  br label %4

; <label>:18:                                     ; preds = %6
  ret double %.01
}

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.start.p0i8(i64, i8* nocapture) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.end.p0i8(i64, i8* nocapture) #1

attributes #0 = { nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nounwind }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 7.0.0 (tags/RELEASE_700/final 343108)"}
!2 = !{!3, !3, i64 0}
!3 = !{!"double", !4, i64 0}
!4 = !{!"omnipotent char", !5, i64 0}
!5 = !{!"Simple C/C++ TBAA"}
