#include <catch2/catch.hpp>

#include "prepare_data.h"

#include <props/props.h>

using namespace predict;
using namespace props;

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
