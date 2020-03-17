#include <coverage/coverage.h>

#include <props/props.h>

#include <support/load_module.h>

#include <catch2/catch.hpp>

#include <random>

using namespace props::literals;

auto count_negs = R"(
define i32 @count_negs(i32, float*) {
  br label %3

3:                                                ; preds = %13, %2
  %.01 = phi i32 [ 0, %2 ], [ %.1, %13 ]
  %.0 = phi i32 [ 0, %2 ], [ %14, %13 ]
  %4 = icmp slt i32 %.0, %0
  br i1 %4, label %5, label %15

5:                                                ; preds = %3
  %6 = sext i32 %.0 to i64
  %7 = getelementptr inbounds float, float* %1, i64 %6
  %8 = load float, float* %7, align 4
  %9 = fcmp olt float %8, 0.000000e+00
  br i1 %9, label %10, label %12

10:                                               ; preds = %5
  %11 = add nsw i32 %.01, 1
  br label %12

12:                                               ; preds = %10, %5
  %.1 = phi i32 [ %11, %10 ], [ %.01, %5 ]
  br label %13

13:                                               ; preds = %12
  %14 = add nsw i32 %.0, 1
  br label %3

15:                                               ; preds = %3
  ret i32 %.01
}
)";

TEST_CASE("Can construct coverage wrappers")
{
  PARSE_TEST_MODULE(mod, count_negs);

  auto wrap = coverage::wrapper(
      "int count_negs(int n, float *xs)"_sig, *mod, "count_negs");
}

TEST_CASE("Can get builders and make calls to wrappers")
{
  PARSE_TEST_MODULE(mod, count_negs);

  auto wrap = coverage::wrapper(
      "int count_negs(int n, float *xs)"_sig, *mod, "count_negs");

  auto b = wrap.get_builder();
  b.add(4, std::vector<float> {1, -1, 2, -2});

  REQUIRE(wrap.call(b) == 2);
}

TEST_CASE("Can correctly record coverage stats")
{
  PARSE_TEST_MODULE(mod, count_negs);

  auto wrap = coverage::wrapper(
      "int count_negs(int n, float *xs)"_sig, *mod, "count_negs");

  auto b = wrap.get_builder();

  SECTION("Total number of branches")
  {
    b.add(4, std::vector<float> {1, -1, 2, -2});

    REQUIRE(wrap.call(b) == 2);
    REQUIRE(wrap.total_conditions() == 4);
  }

  SECTION("Number of covered branches")
  {
    b.add(4, std::vector<float> {1, -1, 2, -2});

    REQUIRE(wrap.call(b) == 2);
    REQUIRE(wrap.covered_conditions() == 4);
  }

  SECTION("Coverage")
  {
    b.add(4, std::vector<float> {1, -1, 2, -2});

    REQUIRE(wrap.call(b) == 2);
    REQUIRE(wrap.coverage() == 1.0);
  }

  SECTION("Incremental")
  {
    b.add(0, std::vector<float> {});
    REQUIRE(wrap.call(b) == 0);
    REQUIRE(wrap.coverage() < 1.0);
    b.reset();

    b.add(2, std::vector<float> {1, 2});
    REQUIRE(wrap.call(b) == 0);
    REQUIRE(wrap.coverage() < 1.0);
    b.reset();

    b.add(3, std::vector<float> {-11, -2, -6});
    REQUIRE(wrap.call(b) == 3);
    REQUIRE(wrap.coverage() == 1.0);
    b.reset();
  }
}

std::vector<float> random_input()
{
  auto rd = std::random_device {};
  auto gen = std::mt19937(rd());
  auto len = std::uniform_int_distribution(0, 32)(gen);
  auto dist = std::uniform_real_distribution<float>(-1, 1);

  auto ret = std::vector<float> {};
  for (auto i = 0; i < len; ++i) {
    ret.push_back(dist(gen));
  }

  return ret;
}

TEST_CASE("Coverage is monotonic")
{
  PARSE_TEST_MODULE(mod, count_negs);

  auto wrap = coverage::wrapper(
      "int count_negs(int n, float *xs)"_sig, *mod, "count_negs");

  auto b = wrap.get_builder();

  for (auto i = 0; i < 64; ++i) {
    auto cov = wrap.coverage();

    auto in = random_input();
    b.add(static_cast<int>(in.size()), in);
    wrap.call(b);
    b.reset();

    REQUIRE(cov <= wrap.coverage());
  }
}
