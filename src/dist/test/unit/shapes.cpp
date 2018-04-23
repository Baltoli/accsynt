#include "catch.h"

#include <dist/loop_shapes.h>
#include <dist/utils.h>

#include <iostream>
#include <unordered_set>

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

  auto m = std::unordered_set<Loop>{};
  m.insert(l);
  m.insert(l2);

  for(const auto& lp : m) {
    std::cout << '\n' << lp;
  }
  std::cout << '\n';
}
