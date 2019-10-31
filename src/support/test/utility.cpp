#include <catch2/catch.hpp>

#include <support/utility.h>

#include <vector>

using namespace support;

TEST_CASE("Can enumerate")
{
  SECTION("With iterables")
  {
    auto v = std::vector<int>{ 3, 4, 5 };

    auto dot = 0;
    for (auto [i, e] : enumerate(v)) {
      dot += i * e;
    }
    REQUIRE(dot == 14);
  }

  SECTION("With iterators")
  {
    auto v = std::vector<int>{ -2, -1, 0, 3, 7 };

    auto b = adl_begin(v);
    auto e = adl_end(v);

    auto dot = 0;
    for (auto [i, elt] : enumerate(b, e)) {
      dot += i * elt;
    }
    REQUIRE(dot == 36);
  }
}
