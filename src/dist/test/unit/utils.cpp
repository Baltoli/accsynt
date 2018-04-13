#include "catch.h"

#include <dist/utils.h>

using namespace accsynt;

TEST_CASE("can uniformly sample with a predicate", "[sampling]") {
  auto vec = std::vector<int>{0, 1, 2, 3, 4, 5};

  SECTION("when valid cases exist") {
    auto sample = uniform_sample_if(vec, [](auto i) { return i % 2 == 0; });

    REQUIRE(sample != end(vec));
    
    auto val = *sample;
    REQUIRE((val == 0 || val == 2 || val == 4));
  }
}
