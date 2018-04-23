#include "catch.h"

#include <dist/loop_shapes.h>
#include <dist/utils.h>

#include <iostream>
#include <unordered_set>

using namespace accsynt;

TEST_CASE("testing loop shapes", "[shapes]") {
  Loop l{};
  l.add_child(Loop{});
  l.add_child(Loop{});

  auto& l2 = l.add_child(Loop{});
  l2.add_child(Loop{});

  std::cout << l << '\n';

  for(auto i = 0u; i < l.size(); ++i) {
    auto lc = l;
    auto& ch = lc.nth_child(i);
    ch = ch.nested();
    std::cout << lc << '\n';
  }
}
