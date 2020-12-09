#include <catch2/catch.hpp>

#include <props/props.h>

using namespace props;

TEST_CASE("Can check if params are compatible")
{
  SECTION("Successful")
  {
    auto p1 = param {"x", base_type::integer, 0};
    auto p2 = param {"t", base_type::integer, 0};
    REQUIRE(p1.compatible(p2));

    p1 = param {"x", base_type::floating, 4};
    p2 = param {"t", base_type::floating, 4};
    REQUIRE(p1.compatible(p2));
  }

  SECTION("Unsuccessful")
  {
    auto p1 = param {"x", base_type::integer, 1};
    auto p2 = param {"t", base_type::integer, 0};
    REQUIRE(!p1.compatible(p2));

    p1 = param {"x", base_type::character, 1};
    p2 = param {"x", base_type::integer, 1};
    REQUIRE(!p1.compatible(p2));
  }
}
