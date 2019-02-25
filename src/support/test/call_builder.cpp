#include <support/call_builder.h>

#include <catch2/catch.hpp>

using namespace props;
using namespace support;

TEST_CASE("Can extract the nth byte of values")
{
  SECTION("for easy int vals")
  {
    auto val = 0xDEADBEEF;
    REQUIRE(detail::nth_byte(val, 0) == 239);
    REQUIRE(detail::nth_byte(val, 1) == 190);
    REQUIRE(detail::nth_byte(val, 2) == 173);
    REQUIRE(detail::nth_byte(val, 3) == 222);
  }

  SECTION("for floating values")
  {
    auto val = float{ 12.345 };
    REQUIRE(detail::nth_byte(val, 0) == 31);
    REQUIRE(detail::nth_byte(val, 1) == 133);
    REQUIRE(detail::nth_byte(val, 2) == 69);
    REQUIRE(detail::nth_byte(val, 3) == 65);
  }

  SECTION("for pointers")
  {
    auto long_val = 0xDEADBEEF01020304;
    int* val;

    REQUIRE(sizeof(long_val) == sizeof(val));
    memcpy(&val, &long_val, sizeof(long_val));

    REQUIRE(detail::nth_byte(val, 0) == 4);
    REQUIRE(detail::nth_byte(val, 1) == 3);
    REQUIRE(detail::nth_byte(val, 2) == 2);
    REQUIRE(detail::nth_byte(val, 3) == 1);
    REQUIRE(detail::nth_byte(val, 4) == 239);
    REQUIRE(detail::nth_byte(val, 5) == 190);
    REQUIRE(detail::nth_byte(val, 6) == 173);
    REQUIRE(detail::nth_byte(val, 7) == 222);
  }
}

TEST_CASE("Can construct call builders from signatures")
{
  auto s1 = signature::parse("void f()");
  auto c1 = call_builder(s1);
}

TEST_CASE("Can extract arguments from a call_builder")
{
  SECTION("Fails if not enough arguments are present")
  {
    auto c1 = call_builder(signature::parse("void f()"));
    REQUIRE_THROWS_AS(c1.get<int>(0), call_builder_error);

    auto c2 = call_builder(signature::parse("void f(int x)"));
    c2.add(0);
    REQUIRE_THROWS_AS(c2.get<int>(1), call_builder_error);

    auto c3 = call_builder(signature::parse("void f(int x, int y, int z)"));
    c3.add(0);
    c3.add(0);
    REQUIRE_THROWS_AS(c3.get<int>(2), call_builder_error);
  }
}
