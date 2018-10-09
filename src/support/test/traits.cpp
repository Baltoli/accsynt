#include <support/traits.h>

#include <catch2/catch.hpp>

using namespace support;

struct s {};
struct t {};

TEST_CASE("pointer depth calculations work") {
  SECTION("basic types") {
    REQUIRE(pointer_depth_v<int> == 0);
    REQUIRE(pointer_depth_v<float> == 0);
    REQUIRE(pointer_depth_v<void> == 0);
    REQUIRE(pointer_depth_v<s> == 0);
    REQUIRE(pointer_depth_v<t> == 0);
  }

  SECTION("pointers") {
    REQUIRE(pointer_depth_v<int*> == 1);
    REQUIRE(pointer_depth_v<float**> == 2);
    REQUIRE(pointer_depth_v<void***> == 3);
    REQUIRE(pointer_depth_v<s****> == 4);
    REQUIRE(pointer_depth_v<t*****> == 5);
  }
}
