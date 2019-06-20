#include <catch2/catch.hpp>

#include <support/random.h>

#include <sstream>
#include <string>
#include <tuple>

using namespace support;
using namespace std::literals::string_literals;

TEST_CASE("Can sample from tuples using auto lambdas")
{
  auto t = std::tuple{ 1, 3.45, "ir"s };

  auto ss = std::stringstream{};
  uniform_tuple_sample(t, [&ss](auto elt) { ss << elt; });

  auto str = ss.str();
  REQUIRE(((str == "1") || (str == "3.45") || (str == "ir")));
}

TEST_CASE("Sampling from empty works")
{
  auto t = std::tuple{};
  REQUIRE_NOTHROW(uniform_tuple_sample(t, [](auto) { throw 0; }));
}
