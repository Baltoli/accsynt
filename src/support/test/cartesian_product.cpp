#include <support/cartesian_product.h>

#include <catch2/catch.hpp>

#include <iostream>

using namespace support;

TEST_CASE("basic construction") {
  auto vec = std::vector<std::vector<int>>{{1, 2}, {3,4}, {5,6}};
  auto prod = cartesian_product(vec.begin(), vec.end());
}
