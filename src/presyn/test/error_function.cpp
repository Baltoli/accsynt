#include <catch2/catch.hpp>

#include "error_function.h"

#include <props/props.h>

#include <support/call_builder.h>

using namespace support;
using namespace props;
using namespace props::literals;

TEST_CASE("Can get errors from built packs")
{
  auto sig = "int f(int x, int y)"_sig;

  auto b1 = call_builder(sig);
  auto b2 = call_builder(sig);
}
