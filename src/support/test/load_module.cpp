#include <support/load_module.h>

#include <catch2/catch.hpp>

TEST_CASE("can parse modules from strings")
{
  auto str = R"(
; ModuleID = 'test.c'
source_filename = "test.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define dso_local i64 @add(i64, i64) #0 {
  %3 = alloca i64, align 4
  %4 = alloca i64, align 4
  store i64 %0, i64* %3, align 4, !tbaa !2
  store i64 %1, i64* %4, align 4, !tbaa !2
  %5 = load i64, i64* %3, align 4, !tbaa !2
  %6 = load i64, i64* %4, align 4, !tbaa !2
  %7 = add nsw i64 %5, %6
  ret i64 %7
}

attributes #0 = { nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i64 1, !"wchar_size", i64 4}
!1 = !{!"clang version 7.0.0 (tags/RELEASE_700/final 343108)\"}
!2 = !{!3, !3, i64 0}
!3 = !{!"int", !4, i64 0}
!4 = !{!"omnipotent char", !5, i64 0}
!5 = !{!"Simple C/C++ TBAA"}
)";

  PARSE_TEST_MODULE(mod, str);
}
