#include <catch2/catch.hpp>

#include <support/instr_count.h>
#include <support/load_module.h>

using namespace support;
using namespace llvm;

TEST_CASE("Can count the instructions in functions")
{
  auto str = R"*(
define i32 @sum(i32* readonly) {
  %2 = icmp eq i32* %0, null
  br i1 %2, label %14, label %3

  %4 = load i32, i32* %0, align 4
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %14, label %6

  %7 = phi i32 [ %12, %6 ], [ %4, %3 ]
  %8 = phi i32 [ %11, %6 ], [ 0, %3 ]
  %9 = phi i32* [ %10, %6 ], [ %0, %3 ]
  %10 = getelementptr inbounds i32, i32* %9, i64 1
  %11 = add nsw i32 %7, %8
  %12 = load i32, i32* %10, align 4
  %13 = icmp eq i32 %12, 0
  br i1 %13, label %14, label %6

  %15 = phi i32 [ 0, %1 ], [ 0, %3 ], [ %11, %6 ]
  ret i32 %15
}
)*";

  auto mod = parse_module(str);
  auto fn = mod->getFunction("sum");

  REQUIRE(fn);
  REQUIRE(instr_count(*fn) == 15);
}
