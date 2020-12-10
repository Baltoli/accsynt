#pragma once

#include <support/call_builder.h>
#include <support/call_wrapper.h>

namespace presyn {

int scalar_distance_error(
    support::output_example const& before,
    support::output_example const& after);

template <typename ErrF>
int compute_error(
    ErrF&& err, support::call_builder args, support::call_wrapper& f1,
    support::call_wrapper& f2)
{
  return 0;
}

} // namespace presyn
