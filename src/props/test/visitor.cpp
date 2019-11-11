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
      on(data_type::integer, [&] { ++c; })
    }.visit(s);

    REQUIRE(c == 1);
  }

  SECTION("visiting different depths")
  {
    auto s = "void f(int a, int *b, int **c, int *d)"_sig;

    auto ss = std::stringstream{};
    sig_visitor{
      on(data_type::integer,    [&] { ss << "A"; }),
      on(data_type::integer, 1, [&] { ss << "B"; }),
      on(data_type::integer, 2, [&] { ss << "C"; }),
      on(data_type::integer, 3, [&] { ss << "D"; })
    }.visit(s);

    REQUIRE(ss.str() == "ABCB");
  }

  SECTION("visiting more than once")
  {
    auto s = "int g(int a, int b)"_sig;
    
    auto c = 0;
    sig_visitor{
      on(data_type::integer, [&] { ++c; })
    }.visit(s);

    REQUIRE(c == 2);
  }

  SECTION("visiting at any depth") {
    auto s = "void f(int *a, int b, int **c)"_sig;

    auto ss = std::stringstream{};
    sig_visitor {
      on(data_type::integer, 2,       [&] () { ss << "dbl"; }),
      on(data_type::integer, any_ptr, [&] (auto const& p) { ss << p.pointer_depth; }),
      on(data_type::integer, 1,       [&] () { ss << "star"; })
    }.visit(s);

    REQUIRE(ss.str() == "1stardbl2");
  }
}
// clang-format on
