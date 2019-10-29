#include <catch2/catch.hpp>

#include "prepare_data.h"

#include <props/props.h>

using namespace predict;
using namespace props;
using namespace props::literals;

TEST_CASE("Can summarise a single property set")
{
  auto file = R"(;hello

;qwd


;werjio


int main(int s, float *d, char **argv, bool on)
name 2.111, 0.000, 4, :string, s, d
fjio
name 3.1, 0.1, 5, :fef, d, s
wefjop
)";
  auto ps = property_set::parse(file);

  auto [params, names, props, arity] = summary(ps).get();

  REQUIRE(params == 4);
  REQUIRE(names == 3);
  REQUIRE(props == 4);
  REQUIRE(arity == 6);
}

TEST_CASE("Can summarise a collection of property sets")
{
auto p1 = R"(
int f(int s, int y)
size s, y
output y
)"_ps;

auto p2 = R"(
float g(int d)
prop d, d, 1.0
output d
size 1, 2
)"_ps;

auto p3 = R"(
void func()
size 2, 3
)"_ps;

auto p4 = R"(
int woop(int **x, int *y, int z)
output x
)"_ps;

  SECTION("From iters") {
    auto vec = std::vector{ p1, p2, p4 };
    auto [params, names, props, arity] = summary(vec).get();

    REQUIRE(params == 3);
    REQUIRE(names == 3);
    REQUIRE(props == 3);
    REQUIRE(arity == 3);
  }

  SECTION("From containers") {
    auto vec = std::vector{ p1, p3, p4 };
    auto [params, names, props, arity] = summary(vec.begin(), vec.end()).get();

    REQUIRE(params == 3);
    REQUIRE(names == 2);
    REQUIRE(props == 2);
    REQUIRE(arity == 2);
  }
}
