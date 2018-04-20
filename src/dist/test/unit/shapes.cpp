#include "catch.h"

#include <dist/loop_shapes.h>
#include <dist/utils.h>

#include <iostream>

using namespace accsynt;

TEST_CASE("testing loop shapes", "[shapes]") {
  auto s = Shape{4};
  s.set_loop_id(0, {3, 3, 1, 0});
  s.set_loop_id(1, {2, 1, 0, 3});
  s.set_loop_id(2, {2, 0, 1, 1});
  s.set_loop_id(3, {0, 1, 1, 3});

  auto t = Shape{4};
  t.set_loop_id(3, {0});
  t.set_loop_id(1, {1});
  t.set_loop_id(2, {1, 0});
  t.set_loop_id(0, {2});

  std::cout << s << '\n';
  std::cout << t << '\n';
  std::cout << (s == t) << '\n';
}
