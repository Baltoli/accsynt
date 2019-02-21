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
  static_assert(detail::is_generator_v<gen>, "gen is not a generator");
  static_assert(detail::is_generator_v<gen2>, "gen2 is not a generator");
  static_assert(!detail::is_generator_v<not_gen>, "not_gen is a generator");
  static_assert(!detail::is_generator_v<not_gen2>, "not_gen2 is a generator");
  static_assert(!detail::is_generator_v<not_gen3>, "not_gen3 is a generator");
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

TEST_CASE("rule of 5 works") {
  SECTION("on simple stateless generators") {
    auto ag = argument_generator(gen());
    auto ag2{ag};
    auto ag3 = ag;

    REQUIRE(ag.gen_int() == ag2.gen_int());
    REQUIRE(ag.gen_int() == ag3.gen_int());
    REQUIRE(ag.gen_float() == ag2.gen_float());
    REQUIRE(ag.gen_float() == ag3.gen_float());

    auto ag4{std::move(ag2)};
    auto ag5 = std::move(ag3);

    REQUIRE(ag.gen_int() == ag4.gen_int());
    REQUIRE(ag.gen_int() == ag5.gen_int());
    REQUIRE(ag.gen_float() == ag4.gen_float());
    REQUIRE(ag.gen_float() == ag5.gen_float());
  }

  SECTION("when generators have state") {
    auto ag = argument_generator(gen2(11));
    auto ag2{ag};
    auto ag3 = ag;

    REQUIRE(ag.gen_int() == ag2.gen_int());
    REQUIRE(ag.gen_int() == ag3.gen_int());
    REQUIRE(ag.gen_float() == ag2.gen_float());
    REQUIRE(ag.gen_float() == ag3.gen_float());

    auto ag4{std::move(ag2)};
    auto ag5 = std::move(ag3);

    REQUIRE(ag.gen_int() == ag4.gen_int());
    REQUIRE(ag.gen_int() == ag5.gen_int());
    REQUIRE(ag.gen_float() == ag4.gen_float());
    REQUIRE(ag.gen_float() == ag5.gen_float());
  }
}

TEST_CASE("uniform generator works") {
  SECTION("it is a valid generator") {
    static_assert(detail::is_generator_v<uniform_generator>, 
                  "Uniform generator needs to be a valid generator");
  }

  SECTION("it can generate values") {
    auto ug = uniform_generator();

    for(int i = 0; i < 100; ++i) {
      auto v1 = ug.gen_int(-10, 10);
      REQUIRE(v1 >= -10);
      REQUIRE(v1 <= 10);

      auto v2 = ug.gen_float(20.1, 33.7);
      REQUIRE(v2 >= 20.1);
      REQUIRE(v2 < 33.7);
    }
  }

  SECTION("it can be seeded") {
    auto ug1 = uniform_generator(10);
    auto ug2 = uniform_generator(10);

    for(int i = 0; i < 100; ++i) {
      REQUIRE(ug1.gen_int(-100, 100) == ug2.gen_int(-100, 100));
      REQUIRE(ug1.gen_float(2.22, 3.33) == Approx(ug2.gen_float(2.22, 3.33)));
    }
  }

  SECTION("it can be wrapped properly") {
    auto ug = uniform_generator();
    auto g = argument_generator(ug);

    for(int i = 0; i < 100; ++i) {
      REQUIRE(g.gen_int(0) >= 0);

      auto v = g.gen_int(-10, -6);
      REQUIRE(v >= -10);
      REQUIRE(v <= -6);

      REQUIRE(g.gen_float(-10) >= -10);

      auto v2 = g.gen_float(3, 4);
      REQUIRE(v2 >= 3);
      REQUIRE(v2 < 4);
    }
  }
}