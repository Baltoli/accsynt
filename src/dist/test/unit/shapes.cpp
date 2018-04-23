#include "catch.h"

#include <dist/loop_shapes.h>
#include <dist/utils.h>

#include <iostream>

using namespace accsynt;

TEST_CASE("testing loop shapes", "[shapes]") {
  Loop l;
  std::cout << l << '\n';

  auto l2 = l;
  l.add_child(Loop{});
  l.add_child(Loop{});
  std::cout << l << '\n';
  std::cout << l2 << '\n';

  for(const auto& lp : l) {
    lp->add_child(Loop{});
  }
  std::cout << l << '\n';
}
