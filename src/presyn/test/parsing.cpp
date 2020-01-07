#include "fragment_parse.h"

#include <catch2/catch.hpp>

using namespace presyn::grammar;

#define MATCH_EXACT(str)                                                       \
  do {                                                                         \
    REQUIRE(parse<seq<test_grammar, eof>>(string_input(str, __func__)));       \
  } while (false)

#define NOT_MATCH_EXACT(str)                                                   \
  do {                                                                         \
    REQUIRE(!parse<seq<test_grammar, eof>>(string_input(str, __func__)));      \
  } while (false)

TEST_CASE("Can recognise fragment names")
{
  using test_grammar = fragment_name;

  SECTION("Can correctly recognise valid names")
  {
    MATCH_EXACT("linear");
    MATCH_EXACT("empty");
    MATCH_EXACT("seq");
  }

  SECTION("Does not match incorrect names")
  {
    NOT_MATCH_EXACT("fweo");
    NOT_MATCH_EXACT("sequence");
    NOT_MATCH_EXACT("empty_fragment");
    NOT_MATCH_EXACT("");
  }
}

TEST_CASE("Can recognise constant integers")
{
  using test_grammar = constant_int;

  SECTION("Can correctly recognise valid integers")
  {
    MATCH_EXACT("12345");
    MATCH_EXACT("0");
    MATCH_EXACT("+0");
    MATCH_EXACT("-0");
    MATCH_EXACT("+10");
    MATCH_EXACT("-12493248290");
  }

  SECTION("Doesn't match incorrect integers")
  {
    NOT_MATCH_EXACT("12.3");
    NOT_MATCH_EXACT("1f");
    NOT_MATCH_EXACT("");
    NOT_MATCH_EXACT("abd23");
    NOT_MATCH_EXACT("--1223");
  }
}

TEST_CASE("Can recognise parameter names")
{
  using test_grammar = parameter_name;

  SECTION("Can correctly recognise parameter names")
  {
    MATCH_EXACT("@wefi");
    MATCH_EXACT("@abc_123_");
    MATCH_EXACT("@w12_23______AJIJI_");
    MATCH_EXACT("@a");
    MATCH_EXACT("@_bcusd");
  }

  SECTION("Doesn't match incorrect parameter names")
  {
    NOT_MATCH_EXACT("wefi");
    NOT_MATCH_EXACT("abc_123_");
    NOT_MATCH_EXACT("@12awd");
    NOT_MATCH_EXACT("@fewji-fe");
    NOT_MATCH_EXACT("@");
    NOT_MATCH_EXACT("");
    NOT_MATCH_EXACT("@(wef)");
    NOT_MATCH_EXACT("@@f");
  }
}
