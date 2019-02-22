#include <props/props.h>

#include <catch2/catch.hpp>
#include <iostream>

using namespace props;

TEST_CASE("can validate property sets")
{
  SECTION("with valid signature")
  {
    auto str =
        R"(
int main(int x)
)";

    REQUIRE_NOTHROW(property_set::parse(str));
  }

  SECTION("with invalid signature")
  {
    auto str =
        R"(
int main(int x, float *x)
)";

    REQUIRE_THROWS(property_set::parse(str));
  }

  SECTION("with valid signature, valid properties")
  {
    auto str =
        R"(
int main(int x, float *y)
size :str, 0.2, 23, x, y
)";

    REQUIRE_NOTHROW(property_set::parse(str));
  }

  SECTION("with valid signature, invalid properties")
  {
    auto str =
        R"(
int main(int x, float *y)
size 3452.231, 3, x, nope
)";

    REQUIRE_THROWS(property_set::parse(str));
  }
}

TEST_CASE("can iterate over properties")
{
  SECTION("with no named properties")
  {
    auto str =
        R"(
void main(int x)
prop
other_prop
third
)";

    auto pset = property_set::parse(str);

    int i = 0;
    pset.for_each_named("name", [&i](auto const&) { ++i; });

    REQUIRE(i == 0);
  }

  SECTION("with named properties")
  {
    auto str =
        R"(
void main(int x)
size 34
size 22
other_name
and_another :sty, x
size -8
)";

    auto pset = property_set::parse(str);

    int i = 0;
    pset.for_each_named(
        "size", [&i](auto const& prop) { i += prop.values.at(0).int_val; });

    REQUIRE(i == (34 + 22 + -8));
  }
}

TEST_CASE("can find signature indices")
{
  SECTION("when the name exists")
  {
    auto str = "int main(int x, int y, float *z)";
    auto sig = signature::parse(str);

    REQUIRE(sig.param_index("x") == 0);
    REQUIRE(sig.param_index("y") == 1);
    REQUIRE(sig.param_index("z") == 2);
  }

  SECTION("when the name does not exist")
  {
    auto str = "int main(int x, int y)";
    auto sig = signature::parse(str);

    REQUIRE_THROWS(sig.param_index("z"));
  }
}
