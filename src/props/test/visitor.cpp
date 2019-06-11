#include <catch2/catch.hpp>

#include <props/props.h>

#include <sstream>

using namespace props;
using namespace props::literals;

// clang-format off
TEST_CASE("Can use the v2 visitor")
{
  SECTION("in a very basic case") 
  {
    auto s = "void f(float a, int *b, int c)"_sig;

    auto c = 0;
    sig_visitor{
      on(data_type::integer, [&] (auto const&) { ++c; })
    }.visit(s);

    REQUIRE(c == 1);
  }

  SECTION("visiting different depths")
  {
    auto s = "void f(int a, int *b, int **c, int *d)"_sig;

    auto ss = std::stringstream{};
    sig_visitor{
      on(data_type::integer, [&] (auto const&) { ss << "A"; }),
      on(data_type::integer, 1, [&] (auto const&) { ss << "B"; }),
      on(data_type::integer, 2, [&] (auto const&) { ss << "C"; }),
      on(data_type::integer, 3, [&] (auto const&) { ss << "D"; })
    }.visit(s);

    REQUIRE(ss.str() == "ABCB");
  }
}
// clang-format on
