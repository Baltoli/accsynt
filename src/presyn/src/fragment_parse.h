#pragma once

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

// Grammars make such horrible template invocations that it's best to format
// them ourselves

// clang-format off

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

} // namespace presyn::grammar
