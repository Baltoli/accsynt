#include "catch.h"

#include <dist/loop_shapes.h>
#include <dist/utils.h>

#include <iostream>

using namespace accsynt;

TEST_CASE("testing loop shapes", "[shapes]") {
  auto id = Indexer(3);
  auto shapes = id.all_loops();

  for(auto shape : shapes) {
    std::cout << shape << '\n';
  }
}
