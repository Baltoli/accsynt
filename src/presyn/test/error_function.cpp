#include <catch2/catch.hpp>

#include "error_function.h"

#include <props/props.h>

#include <support/bit_cast.h>
#include <support/call_builder.h>

using namespace support;
using namespace presyn;
using namespace props;
using namespace props::literals;

TEST_CASE("Can get errors from built packs")
{
  auto b1 = call_builder("int f(int x, int y)"_sig, 1, 2);
  auto b2 = call_builder("int g(int abc, int def)"_sig, 1, 2);

  [[maybe_unused]] auto err = presyn::scalar_distance_error({0, b1}, {0, b2});
}

TEST_CASE("Can properly compute errors on construction")
{
  auto sig = "int f(int x)"_sig;

  auto b1 = call_builder(sig, 4);
  auto b2 = call_builder(sig, 4);

  auto e1 = presyn::scalar_distance_error(
      {6, b1}, {bit_cast<uint64_t>(int64_t(-8)), b2});
  REQUIRE(e1 == 14);

  auto e2 = presyn::scalar_distance_error({8, b1}, {8, b2});
  REQUIRE(e2 == 0);
}
