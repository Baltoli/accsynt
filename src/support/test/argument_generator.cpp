#include <catch2/catch.hpp>

#include <support/argument_generator.h>

#include <iostream>

using namespace support;

TEST_CASE("uniform generator works")
{
  SECTION("it is a generator")
  {
    static_assert(detail::is_generator_v<uniform_generator>,
        "Uniform generator must be a generator");
  }

  SECTION("it can be used with argument_generator")
  {
    auto ug = uniform_generator();
    auto ag = argument_generator(ug);
  }
}

TEST_CASE("CSR SPMV generator works")
{
  SECTION("it is a generator")
  {
    static_assert(detail::is_generator_v<csr_generator>,
        "CSR generator must be a generator");
  }

  SECTION("it can be used with argument_generator")
  {
    auto ag = argument_generator(csr_generator());
  }
}

struct not_gen {
};

struct not_gen_2 {
  int gen_args(call_builder&);
};

struct not_gen_3 {
  void gen_args();
};

struct gen {
  void gen_args(call_builder&);
};

TEST_CASE("Other generators are detected correctly")
{
  static_assert(
      !detail::is_generator_v<not_gen>, "not_gen shouldn't be a generator");

  static_assert(
      !detail::is_generator_v<not_gen_2>, "not_gen2 shouldn't be a generator");

  static_assert(
      !detail::is_generator_v<not_gen_3>, "not_gen3 shouldn't be a generator");

  static_assert(detail::is_generator_v<gen>, "gen should be a generator");
}
