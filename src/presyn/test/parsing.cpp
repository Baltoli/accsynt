#include "fragment_parse.h"

#include <catch2/catch.hpp>

using namespace tao::pre_tl;
using namespace presyn::grammar;

#define MATCH_EXACT(grammar, str)                                              \
  do {                                                                         \
    REQUIRE(parse<seq<grammar, eof>>(string_input(str, __func__)));            \
  } while (false)

#define NOT_MATCH_EXACT(grammar, str)                                          \
  do {                                                                         \
    REQUIRE(!parse<seq<grammar, eof>>(string_input(str, __func__)));           \
  } while (false)

TEST_CASE("Can recognise fragment names")
{
  SECTION("Can correctly recognise valid names")
  {
    MATCH_EXACT(fragment_name, "linear");
    MATCH_EXACT(fragment_name, "empty");
    MATCH_EXACT(fragment_name, "seq");
  }

  SECTION("Does not match incorrect names")
  {
    NOT_MATCH_EXACT(fragment_name, "fweo");
    NOT_MATCH_EXACT(fragment_name, "sequence");
    NOT_MATCH_EXACT(fragment_name, "empty_fragment");
    NOT_MATCH_EXACT(fragment_name, "");
  }
}
