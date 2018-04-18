#include "catch.h"

#include <dist/loop_shapes.h>

#include <iostream>

using namespace accsynt;

TEST_CASE("testing loop shapes", "[shapes]") {
  auto a = Hole{};
  std::cout << a.str() << '\n';

  auto b = Seq(Hole{}, Hole{});
}
