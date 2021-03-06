#include "regular_loop_fragment.h"

#include <catch2/catch.hpp>

#include <fmt/format.h>

using namespace support;
using namespace props;
using namespace synth;

TEST_CASE("Fragment constructor validates arguments")
{
  SECTION("With valid arguments")
  {
    auto args = std::vector{ value::with_param("x"), value::with_param("y") };
    REQUIRE_NOTHROW(regular_loop_fragment{ args });

    auto args1 = std::vector(3, value::with_param("x"));
    REQUIRE_NOTHROW(regular_loop_fragment{ args1 });

    auto args2 = std::vector(34, value::with_param("x"));
    REQUIRE_NOTHROW(regular_loop_fragment{ args2 });
  }

  SECTION("With the wrong argument types")
  {
    auto args = std::vector{ value::with_string(":x"), value::with_param("y") };
    REQUIRE_THROWS_AS(regular_loop_fragment{ args }, std::invalid_argument);

    auto args1 = std::vector{ value::with_param("x"), value::with_int(0) };
    REQUIRE_THROWS_AS(regular_loop_fragment{ args1 }, std::invalid_argument);

    auto args2 = std::vector{ value::with_param("x"), value::with_float(0.1) };
    REQUIRE_THROWS_AS(regular_loop_fragment{ args2 }, std::invalid_argument);

    auto args3
        = std::vector{ value::with_string(":x"), value::with_float(0.1) };
    REQUIRE_THROWS_AS(regular_loop_fragment{ args3 }, std::invalid_argument);

    auto args4 = std::vector{ value::with_param("x"), value::with_float(0.1),
      value::with_param("x"), value::with_float(0.1), value::with_param("x"),
      value::with_float(0.1), value::with_param("x"), value::with_float(0.1) };
    REQUIRE_THROWS_AS(regular_loop_fragment{ args4 }, std::invalid_argument);
  }
}

TEST_CASE("Can copy and move fragments properly")
{
  auto args = std::vector{ value::with_param("x"), value::with_param("x") };
  auto frag = regular_loop_fragment{ args };

  auto frag1{ frag };
  auto frag2{ std::move(frag) };
  auto frag3 = frag1;
  auto frag4 = std::move(frag2);

  frag1 = frag3;

  // TODO: validate these do the right thing - needs equality of fragments to be
  // defined to work really, or some external observers of the fragment state
}

TEST_CASE("Can add children to fragments")
{
  auto args = std::vector{ value::with_param("x"), value::with_param("x") };
  auto f1 = bsc::make_val<regular_loop_fragment>(args);

  SECTION("fails when the index is too big")
  {
    REQUIRE_THROWS_AS(f1->add_child(f1, 3), std::invalid_argument);
  }

  SECTION("succeeds when the index is small enough")
  {
    f1->add_child(f1, 0);
    f1->add_child(f1, 4);
    f1->add_child(f1, 6);
  }
}

TEST_CASE("Can count remaining holes")
{
  SECTION("with an empty fragment")
  {
    auto args = std::vector{ value::with_param("x"), value::with_param("x") };
    auto frag = regular_loop_fragment{ args };

    REQUIRE(frag.count_holes() == 3);
  }

  SECTION("when children have been added")
  {
    // TODO
  }
}
