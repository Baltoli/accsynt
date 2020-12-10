#include <catch2/catch.hpp>

#include <props/props.h>

using namespace props;
using namespace props::literals;

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

TEST_CASE("Can check if sigs are compatible")
{
  SECTION("Successful")
  {
    auto s1 = "int f()"_sig;
    auto s2 = "int g()"_sig;
    REQUIRE(s1.compatible(s2));

    auto s3 = "float hefw(float x, int **y)"_sig;
    auto s4 = "float efwfnfjnfjhj(float eiorwf, int **wojoq)"_sig;
    REQUIRE(s3.compatible(s4));
  }

  SECTION("Unsuccessful")
  {
    auto s1 = "int f()"_sig;
    auto s2 = "bool f()"_sig;
    REQUIRE(!s1.compatible(s2));

    auto s3 = "int h(int x, int *y)"_sig;
    auto s4 = "int h(int x, int y)"_sig;
    REQUIRE(!s3.compatible(s4));

    auto s5 = "float j(int x)"_sig;
    auto s6 = "float j()"_sig;
    REQUIRE(!s5.compatible(s6));
  }
}
