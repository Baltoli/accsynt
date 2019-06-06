#include <catch2/catch.hpp>

#include <props/props.h>

using namespace props;
using namespace props::literals;

TEST_CASE("can visit type signatures")
{
  auto sig = "int f(int x, float y, int *z, float *a)"_sig;
}
