#include "catch.h"

#include <dist/linear_synth.h>
#include <dist/types.h>

using namespace accsynt;

TEST_CASE( "arithmetic programs can be synthesized", "[linear]" ) {
  auto i64 = Integer{};
  auto linear = Linear{i64, i64, i64};

  SECTION( "examples are respected" ) {
    linear.add_example(3, {1, 2});
    linear.add_example(3, {2, 1});
    linear.add_example(-10, {-4, -6});

    auto candidate = linear();
    auto c_func = FunctionCallable{with_error_code, candidate.get(), "cand", i64, i64, i64};

    REQUIRE(std::get<0>(c_func(1, 2)) == 3);
    REQUIRE(std::get<0>(c_func(2, 1)) == 3);
    REQUIRE(std::get<0>(c_func(-4, -6)) == -10);
  }

  SECTION( "conflicting examples use the most recent value" ) {
    linear.add_example(4, {1, 3});
    linear.add_example(3, {1, 3});

    auto candidate = linear();
    auto c_func = FunctionCallable{with_error_code, candidate.get(), "cand", i64, i64, i64};

    REQUIRE(std::get<0>(c_func(1, 3)) == 3);
  }
}

TEST_CASE( "array access programs can be synthesized", "[linear]" ) {
  auto i64 = Integer{};
  auto arr = Array(i64, 4);
  auto idx = Index{arr};
  auto linear = Linear{i64, arr, idx};

  auto vec = std::vector<long>{2, -1, 3, -4};
  auto vec2 = std::vector<long>{4, 52, -13, 0};

  SECTION( "examples are respected" ) {
    linear.add_example(2, {vec, 0});
    linear.add_example(-13, {vec2, 2});

    auto candidate = linear();
    auto c_func = FunctionCallable{with_error_code, candidate.get(), "cand", i64, arr, idx};

    REQUIRE(std::get<0>(c_func(vec, 0)) == 2);
    REQUIRE(std::get<0>(c_func(vec2, 2)) == -13);
  }
}
