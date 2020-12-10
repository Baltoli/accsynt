#pragma once

#include <support/call_builder.h>
#include <support/call_wrapper.h>

#include <functional>

namespace presyn {

int scalar_distance_error(
    support::output_example const& before,
    support::output_example const& after);

template <typename ErrF>
int compute_error(
    ErrF&& err, support::call_builder args, support::call_wrapper& f1,
    support::call_wrapper& f2)
{
  auto a1 = args;
  auto a2 = args;

  auto r1 = f1.call(a1);
  auto r2 = f2.call(a2);

  return err({r1, a1}, {r2, a2});
}

} // namespace presyn
