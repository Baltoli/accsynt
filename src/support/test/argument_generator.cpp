#include <catch2/catch.hpp>

#include <support/argument_generator.h>

#include <iostream>

using namespace support;

struct gen {
  int gen_int(int min, int max) { return 2; }
  float gen_float(float min, float max) { return 3; }
};

struct gen2 {
  int base;
  gen2(int i) : base(i) {}

  int gen_int(int min, int max) { return base * base; }
  float gen_float(float min, float max) { return float(base) / 10.0; }
};

struct not_gen {
};

struct not_gen2 {
  void gen_int(int, int) {}
};

struct not_gen3 {
  int gen_int(int, int) { return 0; }
  float gen_float(int) { return 0.0f; }
};

TEST_CASE("argument concepts work") {
  static_assert(is_generator_v<gen>, "gen is not a generator");
  static_assert(is_generator_v<gen2>, "gen2 is not a generator");
  static_assert(!is_generator_v<not_gen>, "not_gen is a generator");
  static_assert(!is_generator_v<not_gen2>, "not_gen2 is a generator");
  static_assert(!is_generator_v<not_gen3>, "not_gen3 is a generator");
}

TEST_CASE("type erasure works") {
  using namespace Catch::literals;

  SECTION("on a simple constant generator") {
    auto ag = argument_generator(gen());

    REQUIRE(ag.gen_int() == 2);
    REQUIRE(ag.gen_int() == 2);

    REQUIRE(ag.gen_float() == 3.0_a);
    REQUIRE(ag.gen_float() == 3.0_a);
  }

  SECTION("on a different type") {
    auto g1 = gen2(2);
    auto ag1 = argument_generator(g1);
    REQUIRE(ag1.gen_int() == 4);
    REQUIRE(ag1.gen_float() == 0.2_a);

    auto ag2 = argument_generator(gen2(45));
    REQUIRE(ag2.gen_int() == 2025);
    REQUIRE(ag2.gen_float() == 4.5_a);
  }
}
