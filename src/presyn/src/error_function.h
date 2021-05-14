#pragma once

#include <support/call_builder.h>
#include <support/call_wrapper.h>

#include <functional>
#include <type_traits>

namespace presyn {

int scalar_distance_error(
    support::output_example const& before,
    support::output_example const& after);

template <typename ErrF>
int compute_error(
    ErrF&& err, support::call_builder args, support::call_wrapper& f1,
    support::call_wrapper& f2)
{
  static_assert(
      std::is_invocable_r_v<
          int, ErrF, support::output_example, support::output_example>,
      "Must be able to invoke error function with two output examples");

  auto a1 = args;
  auto a2 = args;

  auto r1 = f1.call(a1);
  auto r2 = f2.call(a2);

  return std::invoke(
      std::forward<ErrF>(err), support::output_example {r1, a1},
      support::output_example {r2, a2});
}

} // namespace presyn
