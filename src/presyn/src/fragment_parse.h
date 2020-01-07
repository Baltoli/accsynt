#pragma once

#define TAO_PEGTL_NAMESPACE pre_tl
#include <tao/pegtl.hpp>

namespace presyn::grammar {

// Grammars make such horrible template invocations that it's best to format
// them ourselves

// clang-format off

struct fragment_name : 
  tao::pre_tl::sor<
    TAO_PEGTL_STRING("linear"),
    TAO_PEGTL_STRING("empty"), 
    TAO_PEGTL_STRING("seq")
  > 
{};

// clang-format on

} // namespace presyn::grammar
