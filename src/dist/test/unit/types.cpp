#include "catch.h"

#include <dist/types.h>

using namespace accsynt;

TEST_CASE( "sized pointers respect their size", "[types]" ) {
  auto size = Size{32};
  auto i64 = Integer{};
  auto sp = SizedPointer{i64, size};

  SECTION( "generated values are 0 < gv <= ub" ) {
    for(auto i = 0; i < 128; ++i) {
      auto g = size.generate();
      REQUIRE(g <= size.upper_bound);
      REQUIRE(g > 0);
    }
  }

  SECTION( "sps generate appropriately sized vectors" ) {
    auto gv = sp.generate();
    REQUIRE(gv.size() <= size.upper_bound);
  }
}
