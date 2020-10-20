#include <coverage/coverage.h>

#include <props/props.h>

#include <support/load_module.h>

#include <catch2/catch.hpp>

#include <random>

using namespace props::literals;

auto count_negs = R"#(
define i64 @count_negs(i64* %0, i64 %1) {
  %3 = alloca i64*, align 8
  %4 = alloca i64, align 8
  %5 = alloca i64, align 8
  %6 = alloca i64, align 8
  store i64* %0, i64** %3, align 8
  store i64 %1, i64* %4, align 8
  store i64 0, i64* %5, align 8
  store i64 0, i64* %6, align 8
  br label %7

7:                                                ; preds = %21, %2
  %8 = load i64, i64* %6, align 8
  %9 = load i64, i64* %4, align 8
  %10 = icmp slt i64 %8, %9
  br i1 %10, label %11, label %24

11:                                               ; preds = %7
  %12 = load i64*, i64** %3, align 8
  %13 = load i64, i64* %6, align 8
  %14 = getelementptr inbounds i64, i64* %12, i64 %13
  %15 = load i64, i64* %14, align 8
  %16 = icmp slt i64 %15, 0
  br i1 %16, label %17, label %20

17:                                               ; preds = %11
  %18 = load i64, i64* %5, align 8
  %19 = add nsw i64 %18, 1
  store i64 %19, i64* %5, align 8
  br label %20

20:                                               ; preds = %17, %11
  br label %21

21:                                               ; preds = %20
  %22 = load i64, i64* %6, align 8
  %23 = add nsw i64 %22, 1
  store i64 %23, i64* %6, align 8
  br label %7

24:                                               ; preds = %7
  %25 = load i64, i64* %5, align 8
  ret i64 %25
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
