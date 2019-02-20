#include <catch2/catch.hpp>

#include <support/argument_generator.h>

using namespace support;

struct gen {
  int gen_int(int min, int max) { return 2; }
  float gen_float(float min, float max) { return 3; }
};

TEST_CASE("type erasure works") {
  auto g = argument_generator(gen());
}
