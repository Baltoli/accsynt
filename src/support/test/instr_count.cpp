#include <catch2/catch.hpp>

#include <support/instr_count.h>
#include <support/load_module.h>

using namespace support;
using namespace llvm;

TEST_CASE("Can count the instructions in functions")
{
  auto str = R"*(
define i64 @sum(i64* readonly) {
  %2 = icmp eq i64* %0, null
  br i1 %2, label %14, label %3

  %4 = load i64, i64* %0, align 4
  %5 = icmp eq i64 %4, 0
  br i1 %5, label %14, label %6

  %7 = phi i64 [ %12, %6 ], [ %4, %3 ]
  %8 = phi i64 [ %11, %6 ], [ 0, %3 ]
  %9 = phi i64* [ %10, %6 ], [ %0, %3 ]
  %10 = getelementptr inbounds i64, i64* %9, i64 1
  %11 = add nsw i64 %7, %8
  %12 = load i64, i64* %10, align 4
  %13 = icmp eq i64 %12, 0
  br i1 %13, label %14, label %6

  %15 = phi i64 [ 0, %1 ], [ 0, %3 ], [ %11, %6 ]
  ret i64 %15
}
)*";

  auto mod = parse_module(str);
  auto fn = mod->getFunction("sum");

  REQUIRE(fn);
  REQUIRE(instr_count(*fn) == 15);
}
