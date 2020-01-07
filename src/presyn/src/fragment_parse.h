#pragma once
#include <fmt/format.h>

// This header should only be included in the corresponding implementation file,
// and the unit test file. If included elsewhere, namespace pollution is
// possible.

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
    TAO_PEGTL_STRING("seq")
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
    >
  >
{};

struct child_arg :
  fragment
{};

// clang-format on

using template_arg_state = std::variant<int, std::string>;

struct fragment_state {
  std::string name;
  std::vector<template_arg_state> template_args;
  std::vector<fragment_state> child_args;
};

template <>
struct fragment_action<fragment_name> {
  template <typename Input>
  static void apply(Input const& in, fragment_state& state)
  {
    fmt::print("Rooty tooty: {}\n", in.string());
    state.name = in.string();
  }
};

/* template <> */
/* struct fragment_action<child_arg> : change_states<fragment_state> { */
/*   template <typename Input> */
/*   static void apply(Input const& in, fragment_state& state) */
/*   { */
/*   } */

/*   template <typename Input> */
/*   static void success( */
/*       Input const& in, fragment_state& new_s, fragment_state& old) */
/*   { */
/*   } */
/* }; */

} // namespace presyn::grammar
