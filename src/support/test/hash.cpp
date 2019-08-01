#include <catch2/catch.hpp>

#include <support/hash.h>

#include <iostream>

using namespace support;

TEST_CASE("Can hash things down to a nice string")
{
  std::string s = "fweiu";
  REQUIRE(nice_hash(s) == "Xg2k083chIE");
}
