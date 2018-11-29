#include <support/cartesian_product.h>

#include <catch2/catch.hpp>

#include <iostream>

using namespace support;

TEST_CASE("basic construction") {
  auto vec = std::vector<std::vector<int>>{{0,1}, {2}};
  auto prod = cartesian_product(vec.begin(), vec.end());

  for(auto v : prod) {
    for(auto i : v) {
      std::cout << i << " ";
    }
    std::cout << '\n';
  }
}
