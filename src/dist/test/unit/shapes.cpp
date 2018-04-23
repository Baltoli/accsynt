#include "catch.h"

#include <dist/loop_shapes.h>
#include <dist/utils.h>

#include <iostream>
#include <unordered_set>

using namespace accsynt;

TEST_CASE("testing loop shapes", "[shapes]") {
  auto all = Loop::loops(3);
  for(auto var : all) {
    std::cout << var << '\n';
  }
}
