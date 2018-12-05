#include "regular_loop_fragment.h"

#include <catch2/catch.hpp>

using namespace props;
using namespace synth;

TEST_CASE("Fragment constructor validates arguments")
{
  SECTION("With valid arguments") {
    auto args = std::vector<value>{value::with_param("x"), value::with_param("y")};
    REQUIRE_NOTHROW(regular_loop_fragment{args});
  }

  SECTION("With too many arguments") {
    auto args = std::vector<value>{
      value::with_param("x"), value::with_param("y"), value::with_param("z")};
    REQUIRE_THROWS_AS(regular_loop_fragment{args}, std::invalid_argument);

    auto args1 = std::vector<value>{
      value::with_param("x"), value::with_param("y"), value::with_param("z"),
      value::with_param("x"), value::with_param("y"), value::with_param("z"),
      value::with_param("x"), value::with_param("y"), value::with_param("z")};
    REQUIRE_THROWS_AS(regular_loop_fragment{args1}, std::invalid_argument);
  }

  SECTION("With too few arguments") {
    auto args = std::vector<value>{};
    REQUIRE_THROWS_AS(regular_loop_fragment{args}, std::invalid_argument);

    auto args1 = std::vector<value>{value::with_param("x")};
    REQUIRE_THROWS_AS(regular_loop_fragment{args1}, std::invalid_argument);
  }

  SECTION("With the wrong argument types") {
    auto args = std::vector<value>{value::with_string("x"), value::with_param("y")};
    REQUIRE_THROWS_AS(regular_loop_fragment{args}, std::invalid_argument);

    auto args1 = std::vector<value>{value::with_param("x"), value::with_int(0)};
    REQUIRE_THROWS_AS(regular_loop_fragment{args1}, std::invalid_argument);

    auto args2 = std::vector<value>{value::with_param("x"), value::with_float(0.1)};
    REQUIRE_THROWS_AS(regular_loop_fragment{args2}, std::invalid_argument);

    auto args3 = std::vector<value>{value::with_string("x"), value::with_float(0.1)};
    REQUIRE_THROWS_AS(regular_loop_fragment{args3}, std::invalid_argument);
  }
}
