#include <props/props.h>

#include <catch2/catch.hpp>

using namespace Catch::Matchers;
using namespace props;

TEST_CASE("can print data types") {
  auto it = data_type::integer;
  REQUIRE_THAT(
    fmt::format("{}", it),
    Equals("int"));

  auto flt = data_type::floating;
  REQUIRE_THAT(
    fmt::format("{}", flt),
    Equals("float"));
}

TEST_CASE("can print params") {
  auto p1 = param{"x", data_type::integer, 2};
  REQUIRE_THAT(
    fmt::format("{}", p1),
    Equals("int **x"));

  auto p2 = param{"wefhui", data_type::floating, 0};
  REQUIRE_THAT(
    fmt::format("{}", p2),
    Equals("float wefhui"));
}

TEST_CASE("can print signatures") {
  auto str1 = "int x(float y, int *z)";
  auto sig1 = signature::parse(str1);
  REQUIRE_THAT(fmt::format("{}", sig1), Equals(str1));

  auto str2 = "void func()";
  auto sig2 = signature::parse(str2);
  REQUIRE_THAT(fmt::format("{}", sig2), Equals(str2));

  auto str3 = "float woo(float *******x, int yooo)";
  auto sig3 = signature::parse(str3);
  REQUIRE_THAT(fmt::format("{}", sig3), Equals(str3));
}
