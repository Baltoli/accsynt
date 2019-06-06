#include <catch2/catch.hpp>

#include <props/props.h>

using namespace props;
using namespace props::literals;

// clang-format off
TEST_CASE("can visit type signatures")
{
  SECTION("visiting empty signatures")
  {
    auto s1 = "void f()"_sig;
    auto s2 = "int g()"_sig;
    auto s3 = "float h()"_sig;
  }

  SECTION("can visit using actions, receiving depth")
  {
  }

  SECTION("can visit using values, receiving depth")
  {
  }

  SECTION("can visit using actions, receiving the param")
  {
  }

  SECTION("can visit using values, receiving the param")
  {
  }
}
// clang-format on
