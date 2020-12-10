#include <catch2/catch.hpp>

#include "error_function.h"

#include <props/props.h>

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
