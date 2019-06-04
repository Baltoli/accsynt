#include <support/float_compare.h>
#include <support/type_finder.h>

#include <catch2/catch.hpp>

#include <iostream>

using namespace support;

TEST_CASE("tinkering")
{
  static_assert(std::is_same_v<int_type_finder<float>::type, void>,
      "Empty list maps to void");

  static_assert(std::is_same_v<int_type_finder<float, float>::type, float>,
      "Non-empty list doesn't map to void");

  static_assert(
      std::is_same_v<int_type_finder<float, double, char, float>::type, float>,
      "Non-empty list doesn't map to void");

  auto w = detail::equality_wrapper(2.0f);
  REQUIRE(!w.is_negative());
}
