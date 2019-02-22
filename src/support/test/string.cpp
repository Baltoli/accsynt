#include <support/string.h>

#include <catch2/catch.hpp>

using namespace support;
using namespace std::literals::string_literals;

TEST_CASE("can left trim strings")
{
  REQUIRE(left_trim("  abc") == "abc");
  REQUIRE(left_trim("\t") == "");
  REQUIRE(left_trim("\nwoo\n") == "woo\n");
  REQUIRE(left_trim("ww  ") == "ww  ");

  auto s = "  fweo";
  REQUIRE(left_trim(s) == "fweo");
  REQUIRE(s == "  fweo"s);
}
