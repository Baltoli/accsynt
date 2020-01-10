#include "fragment_parse.h"

#include "fragment.h"

#include <catch2/catch.hpp>

#include <array>

using namespace presyn;
using namespace presyn::literals;
using namespace std::string_literals;

TEST_CASE("Parse building using composition does not break on empty")
{
  auto cases = std::array{"seq(empty, linear<2>)"s,
                          "if_else(empty, seq(empty, loop(empty)))"s};

  for (auto str : cases) {
    auto parsed = fragment::parse(str);

    REQUIRE(str == parsed->to_string());
  }
}
