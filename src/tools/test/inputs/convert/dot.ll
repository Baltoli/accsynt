; ModuleID = 'dot.c'
source_filename = "dot.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define dso_local double @dot(i32, double*, double*) #0 {
  %4 = alloca i32, align 4
  %5 = alloca double*, align 8
  %6 = alloca double*, align 8
  %7 = alloca double, align 8
  %8 = alloca i32, align 4
  store i32 %0, i32* %4, align 4, !tbaa !2
  store double* %1, double** %5, align 8, !tbaa !6
  store double* %2, double** %6, align 8, !tbaa !6
  %9 = bitcast double* %7 to i8*
  call void @llvm.lifetime.start.p0i8(i64 8, i8* %9) #2
  store double 0.000000e+00, double* %7, align 8, !tbaa !8
  %10 = bitcast i32* %8 to i8*
  call void @llvm.lifetime.start.p0i8(i64 4, i8* %10) #2
  store i32 0, i32* %8, align 4, !tbaa !2
  br label %11

; <label>:11:                                     ; preds = %31, %3
  %12 = load i32, i32* %8, align 4, !tbaa !2
  %13 = load i32, i32* %4, align 4, !tbaa !2
  %14 = icmp slt i32 %12, %13
  br i1 %14, label %17, label %15

; <label>:15:                                     ; preds = %11
  %16 = bitcast i32* %8 to i8*
  call void @llvm.lifetime.end.p0i8(i64 4, i8* %16) #2
  br label %34

; <label>:17:                                     ; preds = %11
  %18 = load double*, double** %5, align 8, !tbaa !6
  %19 = load i32, i32* %8, align 4, !tbaa !2
  %20 = sext i32 %19 to i64
  %21 = getelementptr inbounds double, double* %18, i64 %20
  %22 = load double, double* %21, align 8, !tbaa !8
  %23 = load double*, double** %6, align 8, !tbaa !6
  %24 = load i32, i32* %8, align 4, !tbaa !2
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds double, double* %23, i64 %25
  %27 = load double, double* %26, align 8, !tbaa !8
  %28 = fmul double %22, %27
  %29 = load double, double* %7, align 8, !tbaa !8
  %30 = fadd double %29, %28
  store double %30, double* %7, align 8, !tbaa !8
  br label %31

; <label>:31:                                     ; preds = %17
  %32 = load i32, i32* %8, align 4, !tbaa !2
  %33 = add nsw i32 %32, 1
  store i32 %33, i32* %8, align 4, !tbaa !2
  br label %11

; <label>:34:                                     ; preds = %15
  %35 = load double, double* %7, align 8, !tbaa !8
  %36 = bitcast double* %7 to i8*
  call void @llvm.lifetime.end.p0i8(i64 8, i8* %36) #2
  ret double %35
}

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.start.p0i8(i64, i8* nocapture) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.end.p0i8(i64, i8* nocapture) #1

attributes #0 = { nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nounwind }
attributes #2 = { nounwind }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 7.0.0 (tags/RELEASE_700/final 343108)"}
!2 = !{!3, !3, i64 0}
!3 = !{!"int", !4, i64 0}
!4 = !{!"omnipotent char", !5, i64 0}
!5 = !{!"Simple C/C++ TBAA"}
!6 = !{!7, !7, i64 0}
!7 = !{!"any pointer", !4, i64 0}
!8 = !{!9, !9, i64 0}
!9 = !{!"double", !4, i64 0}
