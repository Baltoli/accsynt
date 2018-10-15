#include <props/props.h>

#include <catch2/catch.hpp>

using namespace props;

TEST_CASE("can validate property sets") {
  SECTION("with valid signature") {
    auto str = 
R"(
int main(int x)
)";

    REQUIRE_NOTHROW(property_set::parse(str));
  }

  SECTION("with invalid signature") {
    auto str = 
R"(
int main(int x, float *x)
)";

    REQUIRE_THROWS(property_set::parse(str));
  }

  SECTION("with valid signature, valid properties") {
    auto str =
R"(
int main(int x, float *y)
size :str, 0.2, 23, x, y
)";

    REQUIRE_NOTHROW(property_set::parse(str));
  }

  SECTION("with valid signature, invalid properties") {
    auto str =
R"(
int main(int x, float *y)
size 3452.231, 3, x, nope
)";

    REQUIRE_THROWS(property_set::parse(str));
  }
}
