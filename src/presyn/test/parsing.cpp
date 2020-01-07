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

TEST_CASE("Can recognise individual template arguments")
{
  using test_grammar = template_arg;

  SECTION("Recognise correct arguments")
  {
    MATCH_EXACT("2445");
    MATCH_EXACT("@cdfew_wefji");
    MATCH_EXACT("-32");
    MATCH_EXACT("@__fkj");
    MATCH_EXACT("@_ewjf_");
  }

  SECTION("Don't recognise wrong arguments")
  {
    NOT_MATCH_EXACT("");
    NOT_MATCH_EXACT("seq()");
    NOT_MATCH_EXACT("empty");
    NOT_MATCH_EXACT("+32.2");
    NOT_MATCH_EXACT("<21>");
  }
}

TEST_CASE("Can recognise template argument lists")
{
  using test_grammar = template_arg_list;

  SECTION("Recognise correct lists")
  {
    MATCH_EXACT("<>");
    MATCH_EXACT("<                  >");
    MATCH_EXACT("<12>");
    MATCH_EXACT("<@x, -123>");
    MATCH_EXACT("< -5,       \n@x\n\n,+9148,\n\n\t@d__334_1_x>");
  }

  SECTION("Don't recognise wrong lists")
  {
    NOT_MATCH_EXACT("<,>");
    NOT_MATCH_EXACT("<1,>");
    NOT_MATCH_EXACT("<,@x>");
    NOT_MATCH_EXACT("");
    NOT_MATCH_EXACT("<1,12,@x");
    NOT_MATCH_EXACT("1,12,@x>");
    NOT_MATCH_EXACT("xyx>");
    NOT_MATCH_EXACT("xyx, 123");
  }
}
