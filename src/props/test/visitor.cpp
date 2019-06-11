#include <catch2/catch.hpp>

#include <props/props.h>

#include <sstream>

using namespace props;
using namespace props::literals;

// clang-format off
TEST_CASE("Can use the v2 visitor")
{
  SECTION("in a very basic case") {
    auto s = "void f(float a, int *b, int c)"_sig;

    auto c = 0;
    auto vis = sig_visitor{
      on(data_type::integer, [&] (auto const&) { ++c; })
    };

    vis.visit(s);
    REQUIRE(c == 1);
  }
}
// clang-format on
