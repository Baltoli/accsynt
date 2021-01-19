#include <catch2/catch.hpp>

#include <support/containers.h>

#include <set>
#include <unordered_set>

namespace {

bool is_even(int i) { return (i % 2 == 0); }
bool is_big(int i) { return i > 100; }

} // namespace

TEST_CASE("Can erase from unordered sets")
{
  auto s1 = std::unordered_set {1, 2, 3, 4, 5};
  auto e1 = support::erase_if(s1, is_even);
  REQUIRE(e1 == 2);
  REQUIRE(s1 == std::unordered_set {1, 3, 5});

  auto s2 = std::unordered_set {12, 53, 2, -1};
  auto e2 = support::erase_if(s2, is_big);
  REQUIRE(e2 == 0);
  REQUIRE(s2 == std::unordered_set {12, 53, 2, -1});
}

TEST_CASE("Can erase from sets")
{
  auto s1 = std::set {3, 4, 5, 6, 7, 8, 9, 10};
  auto e1 = support::erase_if(s1, is_even);
  REQUIRE(e1 == 4);
  REQUIRE(s1 == std::set {3, 5, 7, 9});
}
