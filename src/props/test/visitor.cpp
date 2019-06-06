#include <catch2/catch.hpp>

#include <props/props.h>

using namespace props;
using namespace props::literals;

// clang-format off
TEST_CASE("can visit type signatures")
{
  auto sig = "int f(int x, float y, int *z, float *a)"_sig;

  int ptd = 0;

  auto v = sig_visitor{ 
    [&ptd] { ptd += 11; }, 
    [&ptd] { ptd += 1000; }, 
    [&ptd](int p) { ptd += p; },
    [&ptd](int p) { ptd += p; } 
  };

  v.visit(sig);

  REQUIRE(ptd == 1013);

  auto v2 = sig_visitor{ 
    [](auto const& p) { return 1; },
    [](auto const& p) { return 2; }, 
    [](auto const& p) { return 3; },
    [](auto const& p) { return 4; }
  };

  auto vec = v2.visit(sig);
  REQUIRE(vec == std::vector{ 1, 2, 3, 4 });
}
// clang-format on
