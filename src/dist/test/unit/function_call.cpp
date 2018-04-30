#include "catch.h"
#include "load_module.h"

#include <dist/function_callable.h>

#include <llvm/IR/Module.h>

using namespace accsynt;

TEST_CASE( "LLVM functions can be wrapped and called", "[function]" ) {
  LOAD_MODULE(mod, R"(
define i64 @func(i64) {
  %2 = add nsw i64 %0, 1
  ret i64 %2
}
  )");

  auto fc = FunctionCallable<long>(mod.get(), "func");

  SECTION( "error is not used by default" ) {
    REQUIRE(!fc.get_error());
    fc(0);
    REQUIRE(!fc.get_error());
  }

  SECTION( "callable behaves correctly" ) {
    REQUIRE(fc(0) == 1);
    REQUIRE(fc(-30) == -29);
    REQUIRE(fc(22) == 23);
  }
}

TEST_CASE( "LLVM functions can return an error", "[function]" ) {
  LOAD_MODULE(mod, R"(
define i64 @func(i64*) {
  store i64 3, i64* %0
  ret i64 0
}
  )");

  auto fc = FunctionCallable<long>(mod.get(), "func", true);

  SECTION( "error is not set initially" ) {
    REQUIRE(!fc.get_error());
  }

  SECTION( "error is set after calling" ) {
    fc();
    REQUIRE(fc.get_error());
    REQUIRE(*fc.get_error() == 3);
  }
}

TEST_CASE( "LLVM functions can take an array", "[function]" ) {
  LOAD_MODULE(mod, R"(
define i64 @func([4 x i64]*, i64) {
  %3 = getelementptr inbounds [4 x i64], [4 x i64]* %0, i64 0, i64 %1
  %4 = load i64, i64* %3
  ret i64 %4
}
  )");

  auto fc = FunctionCallable<long>(mod.get(), "func");
  auto vec = std::vector<long>{2, 4, -1, -6, 0};

  SECTION( "valid indices yield the correct values" ) {
    REQUIRE(fc(vec, 0) == 2);
    REQUIRE(fc(vec, 1) == 4);
    REQUIRE(fc(vec, 2) == -1);
    REQUIRE(fc(vec, 3) == -6);
    REQUIRE(fc(vec, 4) == 0);
  }
}

TEST_CASE( "using v2 function callable", "[function]" ) {
  SECTION( "return types" ) {
    using ret1 = v2::FunctionCallable<Void, Output<Integer>>::return_type;
    REQUIRE(std::is_same_v<ret1, std::tuple<Integer::example_t>>);
  }

  SECTION( "running with output params" ) {
    LOAD_MODULE(mod, R"(
define void @func([4 x i64]*) {
  %2 = getelementptr inbounds [4 x i64], [4 x i64]* %0, i64 0, i64 0
  store i64 1, i64* %2
  ret void
}
    )");

    auto fc = v2::FunctionCallable<Void, Output<Array<Integer>>>(mod.get(), "func");

    auto args = std::vector<long>{0, 1, 2, 3};
    auto ret = fc(args);

    /* REQUIRE(std::get<0>(ret).at(0) == 1); */
  }
}
