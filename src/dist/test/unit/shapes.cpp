#include "catch.h"

#include <dist/loop_shapes.h>

#include <iostream>

using namespace accsynt;

TEST_CASE("testing loop shapes", "[shapes]") {
  auto s = Seq{
    Hole{}, Nest{
      Seq{Hole{}, Hole{}}
    }
  };

  std::cout << s << '\n';
  std::cout << s.size() << '\n';
}
