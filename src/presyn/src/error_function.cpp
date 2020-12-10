#include "error_function.h"

#include <support/assert.h>

using namespace support;

namespace presyn {

int scalar_distance_error(
    output_example const& before, output_example const& after)
{
  assertion(
      before.output_args.signature().compatible(after.output_args.signature()),
      "Can't compute error function on argument packs with different "
      "underlying signatures");

  assertion(
      !before.output_args.signature().accepts_pointer(),
      "Can't compute scalar error if signature accepts any pointer arguments");

  return 0;
}

} // namespace presyn
