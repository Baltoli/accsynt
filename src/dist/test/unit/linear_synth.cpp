#include "catch.h"

#include <dist/linear_synth.h>
#include <dist/types.h>

TEST_CASE( "arithmetic programs can be synthesized", "[linear]" ) {
  auto i64 = types::Integer{};
  auto linear = synth::Linear{i64, i64, i64};

  SECTION( "examples are respected" ) {
    linear.add_example(3, {1, 2});
    linear.add_example(3, {2, 1});
    linear.add_example(-10, {-4, -6});

    auto candidate = linear();
    auto c_func = FunctionCallable<long>{candidate.get(), "cand", true};

    REQUIRE(c_func(1, 2) == 3);
    REQUIRE(c_func(2, 1) == 3);
    REQUIRE(c_func(-4, -6) == -10);
  }

  SECTION( "conflicting examples use the most recent value" ) {
    linear.add_example(4, {1, 3});
    linear.add_example(3, {1, 3});

    auto candidate = linear();
    auto c_func = FunctionCallable<long>{candidate.get(), "cand", true};

    REQUIRE(c_func(1, 3) == 3);
  }
}
