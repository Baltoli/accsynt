#pragma once

// This header should only be included in the corresponding implementation file,
// and the unit test file. If included elsewhere, namespace pollution is
// possible.

#include <support/assert.h>

#include <fmt/format.h>

#define TAO_PEGTL_NAMESPACE pre_tl
#include <tao/pegtl.hpp>

#include <string>
#include <variant>
#include <vector>

namespace presyn::grammar {

using namespace tao::pre_tl;

/**
 * The grammar is simple enough that we can make do with a single action, which
 * will update a POD state representing the parsed data.
 */
template <typename Rule>
struct fragment_action : nothing<Rule> {
};

// Grammars make such horrible template invocations that it's best to format
// them ourselves

// clang-format off

// Grammars

struct fragment_name : 
  sor<
    TAO_PEGTL_STRING("linear"),
    TAO_PEGTL_STRING("empty"), 
    TAO_PEGTL_STRING("seq"), 
    TAO_PEGTL_STRING("loop"),
    TAO_PEGTL_STRING("delim"),
    TAO_PEGTL_STRING("fixed"),
    TAO_PEGTL_STRING("if_else"),
    TAO_PEGTL_STRING("if"),
    TAO_PEGTL_STRING("affine"),
    TAO_PEGTL_STRING("index")
  > 
{};

struct constant_int : 
  seq<
    opt<
      sor<
        one<'+'>, 
        one<'-'>
      >
    >, 
    plus<
      digit
    >
  >
{};

struct parameter_name :
  seq<
    one<'@'>,
    identifier
  >
{};

struct template_arg :
  sor<
    constant_int,
    parameter_name
  >
{};

template <typename Left, typename Arg, typename Right>
struct arg_list :
  seq<
    Left,
    pad_opt<
      list<
        Arg,
        one<','>,
        space
      >,
      space
    >,
    Right
  >
{};

struct template_arg_list :
  arg_list<
    one<'<'>,
    template_arg,
    one<'>'>
  >
{};

// Forward declaration to break cycles in the following definitions
struct child_arg;

struct child_arg_list :
  arg_list<
    one<'('>,
    child_arg,
    one<')'>
  >
{};

struct fragment_end :
  TAO_PEGTL_STRING("")
{};

struct fragment :
  seq<
    fragment_name,
    star<space>,
    opt<
      template_arg_list
    >,
    star<space>,
    opt<
      child_arg_list
    >,
    fragment_end
  >
{};

struct child_arg :
  fragment
{};

// clang-format on

using template_arg_state = std::variant<int, std::string>;

struct fragment_parse {
  std::string name = "";
  std::vector<template_arg_state> template_args = {};
  std::vector<fragment_parse> child_args = {};
};

struct fragment_state {
  fragment_parse result;
  std::vector<fragment_parse> stack = {};
};

template <>
struct fragment_action<fragment_name> {
  template <typename Input>
  static void apply(Input const& in, fragment_state& state)
  {
    state.stack.emplace_back();
    state.stack.back().name = in.string();
  }
};

template <>
struct fragment_action<fragment_end> {
  static void apply0(fragment_state& state)
  {
    auto completed = state.stack.back();
    state.stack.pop_back();

    if (!state.stack.empty()) {
      state.stack.back().child_args.push_back(completed);
    }

    state.result = completed;
  }
};

template <>
struct fragment_action<constant_int> {
  template <typename Input>
  static void apply(Input const& in, fragment_state& state)
  {
    state.stack.back().template_args.emplace_back(std::stoi(in.string()));
  }
};

template <>
struct fragment_action<parameter_name> {
  template <typename Input>
  static void apply(Input const& in, fragment_state& state)
  {
    // substring is so that the stored string is *without* the preceding @
    // symbol, which is a lexical format detail and should not be stored
    // alongside the actual name of the parameter.
    state.stack.back().template_args.emplace_back(in.string().substr(1));
  }
};

} // namespace presyn::grammar
