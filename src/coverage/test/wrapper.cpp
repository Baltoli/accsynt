#include <coverage/coverage.h>

#include <props/props.h>

#include <support/load_module.h>

#include <catch2/catch.hpp>

#include <random>

using namespace props::literals;

auto count_negs = R"#(
define i64 @count_negs(i64 %arg0, float* %arg1) {
  br label %1

1:                                                ; preds = %5, %0
  %v0 = phi i64 [ 0, %0 ], [ %v8, %5 ]
  %v1 = phi i64 [ 0, %0 ], [ %v9, %5 ]
  %v2 = icmp slt i64 %v1, %arg0
  br i1 %v2, label %2, label %6

2:                                                ; preds = %1
  %v4 = getelementptr inbounds float, float* %arg1, i64 %v1
  %v5 = load float, float* %v4, align 4
  %v6 = fcmp olt float %v5, 0.000000e+00
  br i1 %v6, label %3, label %4

3:                                                ; preds = %2
  %v7 = add nsw i64 %v0, 1
  br label %4

4:                                                ; preds = %3, %2
  %v8 = phi i64 [ %v7, %3 ], [ %v0, %2 ]
  br label %5

5:                                                ; preds = %4
  %v9 = add nsw i64 %v1, 1
  br label %1

6:                                                ; preds = %1
  ret i64 %v0
}
)#";

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
  b.add(4ll, std::vector<float> {1, -1, 2, -2});

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
    b.add(4ll, std::vector<float> {1, -1, 2, -2});

    REQUIRE(wrap.call(b) == 2);
    REQUIRE(wrap.total_conditions() == 4);
  }

  SECTION("Number of covered branches")
  {
    b.add(4ll, std::vector<float> {1, -1, 2, -2});

    REQUIRE(wrap.call(b) == 2);
    REQUIRE(wrap.covered_conditions() == 4);
  }

  SECTION("Coverage")
  {
    b.add(4ll, std::vector<float> {1, -1, 2, -2});

    REQUIRE(wrap.call(b) == 2);
    REQUIRE(wrap.coverage() == 1.0);
  }

  SECTION("Incremental")
  {
    b.add(0ll, std::vector<float> {});
    REQUIRE(wrap.call(b) == 0);
    REQUIRE(wrap.coverage() < 1.0);
    b.reset();

    b.add(2ll, std::vector<float> {1, 2});
    REQUIRE(wrap.call(b) == 0);
    REQUIRE(wrap.coverage() < 1.0);
    b.reset();

    b.add(3ll, std::vector<float> {-11, -2, -6});
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
    b.add(static_cast<int64_t>(in.size()), in);
    wrap.call(b);
    b.reset();

    REQUIRE(cov <= wrap.coverage());
  }
}
