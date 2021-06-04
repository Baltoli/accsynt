#include <replacer/replace.h>

#include <catch2/catch.hpp>

#include <nlohmann/json.hpp>

using json = ::nlohmann::json;

using namespace idlr;

TEST_CASE("Can construct call objects")
{
  using namespace std::string_literals;

  auto j = R"(
    {
      "callee": "func",
      "args": [
        "v1", "v2", "v3"
      ]
    }
  )"_json;

  auto c = call(j);

  REQUIRE(c.target() == "func");
  REQUIRE(c.args() == std::vector {"v1"s, "v2"s, "v3"s});
}

TEST_CASE("Can construct spec objects")
{
  using namespace std::string_literals;

  auto j = R"(
    {
      "function": "add",
      "replacements": {
        "v1": {
          "callee": "func",
          "args": ["v2", "v3"]
        },

        "v2": {
          "callee": "f2",
          "args": []
        }
      }
    }
  )"_json;

  auto s = spec(j);

  REQUIRE(s.function() == "add");

  REQUIRE(s.replacements().at("v1").target() == "func");
  REQUIRE(s.replacements().at("v1").args() == std::vector {"v2"s, "v3"s});

  REQUIRE(s.replacements().at("v2").target() == "f2");
  REQUIRE(s.replacements().at("v2").args() == std::vector<std::string> {});
}
