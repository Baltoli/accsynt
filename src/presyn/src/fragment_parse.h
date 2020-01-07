#pragma once

// This header should only be included in the corresponding implementation file,
// and the unit test file. If included elsewhere, namespace pollution is
// possible.

#define TAO_PEGTL_NAMESPACE pre_tl
#include <tao/pegtl.hpp>

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

struct template_arg_list :
  seq<
    one<'<'>,
    pad_opt<
      list<
        template_arg,
        one<','>,
        space
      >,
      space
    >,
    one<'>'>
  >
{};

// clang-format on

} // namespace presyn::grammar
