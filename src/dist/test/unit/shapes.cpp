#include "catch.h"

#include <dist/loop_shapes.h>
#include <dist/utils.h>

#include <iostream>

using namespace accsynt;

TEST_CASE("testing loop shapes", "[shapes]") {
  auto s = Shape{4};

  s.set_loop_id(0, {0});
  s.set_loop_id(1, {1});
  s.set_loop_id(2, {2});
  s.set_loop_id(3, {3});

  std::cout << s << '\n';
}
