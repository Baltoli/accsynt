#include <catch2/catch.hpp>

#include <dist/utils.h>

using namespace accsynt;

TEST_CASE("can uniformly sample", "[sampling]") {
  SECTION("without a predicate") {
    SECTION("when elements exist") {
      auto vec = std::vector<int>{0, 1, 2, 3};
      auto sample = uniform_sample(vec);

      REQUIRE(sample != end(vec));

      auto value = *sample;
      REQUIRE((value >= 0 && value <= 3));
    }

    SECTION("when no element exists") {
      auto vec = std::vector<int>{};
      auto sample = uniform_sample(vec);

      REQUIRE(sample == end(vec));
    }
  }

  SECTION("with a predicate") {
    auto vec = std::vector<int>{0, 1, 2, 3, 4, 5};

    SECTION("when valid cases exist") {
      auto sample = uniform_sample_if(vec, [](auto i) { return i % 2 == 0; });

      REQUIRE(sample != end(vec));
      
      auto val = *sample;
      REQUIRE((val == 0 || val == 2 || val == 4));
    }

    SECTION("when no valid case exists") {
      auto sample = uniform_sample_if(vec, [](auto i) { return i == 8; });
      REQUIRE(sample == end(vec));
    }
  }
}
