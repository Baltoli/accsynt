#include "load_module.h"

#include <catch2/catch.hpp>

#include <dist/function_callable.h>

#include <llvm/IR/Module.h>

using namespace accsynt;

TEST_CASE( "using v2 function callable", "[function]" ) {
  SECTION( "return types" ) {
    using ret1 = FunctionCallable<Void, Output<Integer>>::return_type;
    REQUIRE(std::is_same_v<ret1, std::tuple<Integer::example_t>>);
  }

  SECTION( "running with return values" ) {
    LOAD_MODULE(mod, R"(
define i64 @func(i64) {
  ret i64 %0
}
    )");

    auto ret_t = Integer{64};
    auto fc = FunctionCallable(no_error_code, mod.get(), "func", ret_t, ret_t);

    auto ret = fc(23);

    REQUIRE(fc.get_error() == std::nullopt);
    REQUIRE(std::get<0>(ret) == 23);
  }

  SECTION( "running with output params" ) {
    LOAD_MODULE(mod, R"(
define void @func([4 x i64]*) {
  %2 = getelementptr inbounds [4 x i64], [4 x i64]* %0, i64 0, i64 0
  store i64 1, i64* %2
  ret void
}
    )");

    auto ret_t = Void{};
    auto arg_t = Output{Array{Integer{64}, 4}};

    auto fc = FunctionCallable(no_error_code, mod.get(), "func", ret_t, arg_t);

    auto args = std::vector<long>{0, 1, 2, 3};
    auto ret = fc(args);

    REQUIRE(fc.get_error() == std::nullopt);
    REQUIRE(std::get<0>(ret).at(0) == 1);
  }

  SECTION( "running with both" ) {
    LOAD_MODULE(mod, R"(
define i64 @func([4 x i64]*, i64) {
  %3 = getelementptr inbounds [4 x i64], [4 x i64]* %0, i64 0, i64 %1
  %4 = load i64, i64* %3
  %5 = add i64 %4, 1
  store i64 %5, i64* %3
  ret i64 %4
}
    )");

    auto ret_t = Integer{64};
    auto arg_t = Output{Array{Integer{64}, 4}};
    
    auto fc = FunctionCallable(no_error_code, mod.get(), "func", ret_t, arg_t, ret_t);

    auto arr = std::vector<long>{0, 1, 2, 23};

    auto ret1 = fc(arr, 0);
    REQUIRE(fc.get_error() == std::nullopt);
    REQUIRE(arr.at(0) == 0);
    REQUIRE(std::get<0>(ret1) == 0);
    REQUIRE(std::get<1>(ret1).at(0) == 1);

    auto ret2 = fc(arr, 3);
    REQUIRE(fc.get_error() == std::nullopt);
    REQUIRE(arr.at(3) == 23);
    REQUIRE(std::get<0>(ret2) == 23);
    REQUIRE(std::get<1>(ret2).at(3) == 24);
  }

  SECTION( "running with an error code") {
    LOAD_MODULE(mod, R"(
define void @func(i64*) {
  store i64 1, i64* %0
  ret void
}
    )");

    auto fc = FunctionCallable(with_error_code, mod.get(), "func", Void{});

    fc();
    REQUIRE(fc.get_error() != std::nullopt);
    REQUIRE(*fc.get_error() == 1);
  }
}
