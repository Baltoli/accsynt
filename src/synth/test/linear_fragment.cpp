#include "linear_fragment.h"

#include <props/props.h>

#include <catch2/catch.hpp>

using namespace props;
using namespace synth;

TEST_CASE("Can construct linear fragments")
{
  SECTION("valid with no arguments")
  {
    auto args = std::vector<props::value>{};

    REQUIRE_NOTHROW(linear_fragment(args));
    REQUIRE_NOTHROW(empty_fragment(args));
  }

  SECTION("invalid with any arguments")
  {
    auto a1 = std::vector{ value::with_int(0) };
    auto a2 = std::vector{ value::with_float(0.1) };
    auto a3 = std::vector{ value::with_string("s") };
    auto a4 = std::vector{ value::with_param("q") };
    auto a5 = std::vector(10, value::with_param("q"));

    REQUIRE_THROWS_AS(linear_fragment(a1), std::invalid_argument);
    REQUIRE_THROWS_AS(empty_fragment(a1), std::invalid_argument);

    REQUIRE_THROWS_AS(linear_fragment(a2), std::invalid_argument);
    REQUIRE_THROWS_AS(empty_fragment(a2), std::invalid_argument);

    REQUIRE_THROWS_AS(linear_fragment(a3), std::invalid_argument);
    REQUIRE_THROWS_AS(empty_fragment(a3), std::invalid_argument);

    REQUIRE_THROWS_AS(linear_fragment(a4), std::invalid_argument);
    REQUIRE_THROWS_AS(empty_fragment(a4), std::invalid_argument);

    REQUIRE_THROWS_AS(linear_fragment(a5), std::invalid_argument);
    REQUIRE_THROWS_AS(empty_fragment(a5), std::invalid_argument);
  }
}

TEST_CASE("can copy and move")
{
  auto frag = linear_fragment{ {} };

  auto f1 = frag;
  auto f2 = std::move(f1);

  auto f3{ f2 };
  auto f4{ std::move(f3) };

  f1 = f4;
}
