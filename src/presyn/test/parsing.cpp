#include "fragment_parse.h"

#include "fragment.h"

#include <tao/pegtl/analyze.hpp>

#include <catch2/catch.hpp>

#include <array>

using namespace presyn::grammar;
using namespace presyn::literals;

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
    MATCH_EXACT("loop");
    MATCH_EXACT("delim");
    MATCH_EXACT("fixed");
    MATCH_EXACT("if");
    MATCH_EXACT("if_else");
    MATCH_EXACT("affine");
    MATCH_EXACT("index");
  }

  SECTION("Does not match incorrect names")
  {
    NOT_MATCH_EXACT("fweo");
    NOT_MATCH_EXACT("sequence");
    NOT_MATCH_EXACT("empty_fragment");
    NOT_MATCH_EXACT("");
    NOT_MATCH_EXACT("for");
    NOT_MATCH_EXACT("while");
    NOT_MATCH_EXACT("until");
    NOT_MATCH_EXACT("if-else");
    NOT_MATCH_EXACT("else");
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

TEST_CASE("Can recognise fragments")
{
  using test_grammar = fragment;

  SECTION("Recognise correct fragments")
  {
    MATCH_EXACT("empty");
    MATCH_EXACT("empty()");
    MATCH_EXACT("empty<>()");

    MATCH_EXACT("linear<2>");
    MATCH_EXACT("seq(seq(empty, empty), empty<@w, -12>)");
    MATCH_EXACT("seq(seq, seq)");
    MATCH_EXACT("seq(seq, seq, linear, empty<>, empty(empty))");

    MATCH_EXACT("linear<1,\n2,\t\t3, 4, 5, 6, 7>(   linear\n)");

    MATCH_EXACT("loop<@x,23>(loop, loop)");
    MATCH_EXACT("delim(loop, fixed(delim))");
    MATCH_EXACT("if(if(if(if(if(if<>())))))");
    MATCH_EXACT("if(if(if(if_else, if_else, if_else<>(), if(if(if<>())))))");
    MATCH_EXACT("affine<1, 1, 2, +3, -1>(affine)");
    MATCH_EXACT("affine<1, 1, 2, +3, -1>(index, index(index<>))");
  }

  SECTION("Don't recognise wrong fragments")
  {
    NOT_MATCH_EXACT("wwoq");
    NOT_MATCH_EXACT("woo()");
    NOT_MATCH_EXACT("woefwjk<>()");

    NOT_MATCH_EXACT("empty<)");
    NOT_MATCH_EXACT("empty<>)");
    NOT_MATCH_EXACT("empty<");
    NOT_MATCH_EXACT("linear(");
    NOT_MATCH_EXACT("seq(1)");
    NOT_MATCH_EXACT("seq(empty)<2>");
    NOT_MATCH_EXACT("seq(empty)<linear>");
    NOT_MATCH_EXACT("seq(empty)<linear(2)>");
    NOT_MATCH_EXACT("loop<loop>()");
    NOT_MATCH_EXACT("if-else()");
    NOT_MATCH_EXACT("if<--22>()");
    NOT_MATCH_EXACT("indexed()");
    NOT_MATCH_EXACT("affine_index<>");
  }
}

TEST_CASE("The grammar doesn't have any issues")
{
  REQUIRE(analyze<fragment>() == 0);
}

TEST_CASE("Printing and parsing are inverses")
{
  auto frags = std::array {"empty"_frag,
                           "linear<7>()"_frag,
                           "seq<>()"_frag,
                           "seq(seq(), seq<>(empty))"_frag,
                           "seq(linear<2>, seq(empty()))"_frag,
                           "loop(seq(linear<7>, empty))"_frag,
                           "delim<@x>(loop)"_frag,
                           "fixed<@x, @N>(fixed<@y, 32>(empty))"_frag,
                           "if(if(linear<2>))"_frag,
                           "if_else(if, loop(fixed<@wef_w, 45>))"_frag,
                           "affine<@ptr>(delim<@ptr>(if))"_frag,
                           "index<@x>(affine<@y>(fixed<@p, @q>(loop)))"_frag};

  for (auto const& frag : frags) {
    auto str = frag->to_string();
    auto parsed = presyn::fragment::parse(str);

    REQUIRE(str == parsed->to_string());
  }
}
