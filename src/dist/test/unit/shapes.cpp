#include "catch.h"

#include <dist/loop_shapes.h>

#include <iostream>

using namespace accsynt;

TEST_CASE("testing loop shapes", "[shapes]") {
  auto h = Hole{};
  auto n = Nest{h};
  auto nnn = Nest{n};
}
