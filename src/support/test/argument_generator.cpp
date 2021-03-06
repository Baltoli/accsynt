#include <catch2/catch.hpp>

#include <support/argument_generator.h>

#include <props/props.h>

#include <iostream>

using namespace props;
using namespace props::literals;
using namespace support;

TEST_CASE("uniform generator works")
{
  SECTION("it is a generator")
  {
    static_assert(
        detail::is_generator_v<uniform_generator>,
        "Uniform generator must be a generator");
  }

  SECTION("it can be used with argument_generator")
  {
    auto ug = uniform_generator();
    auto ag = argument_generator(ug);
  }
}

TEST_CASE("override generator works")
{
  SECTION("it is a generator")
  {
    static_assert(
        detail::is_generator_v<override_generator<int64_t>>,
        "Override generator must be a generator");

    static_assert(
        detail::is_generator_v<override_generator<float>>,
        "Override generator must be a generator");

    static_assert(
        detail::is_generator_v<override_generator<char>>,
        "Override generator must be a generator");
  }

  SECTION("it will generate fixed values")
  {
    auto ag = argument_generator(override_generator("x", 67ll));
    auto build = call_builder("int f(int x, int y)"_sig);

    ag.gen_args(build);

    auto x = build.get<int64_t>("x");
    auto y = build.get<int64_t>("y");

    REQUIRE(x == 67);
    REQUIRE(y != 67);
  }
}

TEST_CASE("CSR SPMV generator works")
{
  SECTION("it is a generator")
  {
    static_assert(
        detail::is_generator_v<csr_generator>,
        "CSR generator must be a generator");
  }

  SECTION("it can be used with argument_generator")
  {
    auto ag = argument_generator(csr_generator());
    auto c1 = call_builder("void spmv(float *ov, float *a, float *iv, int "
                           "*rowstr, int *colidx, int rows)"_sig);

    ag.gen_args(c1);

    auto ov = c1.get<std::vector<float>>("ov");
    auto a = c1.get<std::vector<float>>("a");
    auto iv = c1.get<std::vector<float>>("iv");
    auto rowstr = c1.get<std::vector<int64_t>>("rowstr");
    auto colidx = c1.get<std::vector<int64_t>>("colidx");
    auto rows = c1.get<int64_t>("rows");

    REQUIRE(rowstr.at(0) == 0);
    REQUIRE(std::is_sorted(rowstr.begin(), rowstr.end()));

    for (auto i = 0u; i < rowstr.size() - 1; ++i) {
      REQUIRE(std::is_sorted(
          colidx.begin() + rowstr[i], colidx.begin() + rowstr[i + 1]));
    }

    auto nnz = rowstr.back();
    REQUIRE(static_cast<int64_t>(a.size()) == nnz);

    REQUIRE(static_cast<int64_t>(rowstr.size()) == rows + 1);

    REQUIRE(*std::max_element(colidx.begin(), colidx.end()) < 128);
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
