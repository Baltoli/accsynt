#include <catch2/catch.hpp>

#include <support/bit_cast.h>
#include <support/similarity.h>

#include <iostream>

#include <limits>

using namespace support;
using namespace Catch::literals;

TEST_CASE("return metric is monotonic")
{
  SECTION("ints")
  {
    int start = GENERATE(take(100, random(0, 1000)));
    auto current = start;

    auto score = scalar_similarity<int>(start, current);
    REQUIRE(score == 1.0_a);

    for (int i = 0; i < 1000; ++i) {
      current += 1;

      auto new_score = scalar_similarity<int>(start, current);

      REQUIRE(new_score <= score);
      score = new_score;
    }
  }

  SECTION("floats")
  {
    auto start = GENERATE(take(100, random(0.0, 1.0E3)));
    auto current = start;

    auto score = scalar_similarity<float>(start, current);
    REQUIRE(score == 1.0_a);

    for (int i = 0; i < 1000; ++i) {
      current += 1.0;

      auto new_score = scalar_similarity<float>(start, current);

      REQUIRE(new_score <= score);
      score = new_score;
    }
  }
}
