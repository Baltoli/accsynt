#include "error_function.h"

#include <support/assert.h>

using namespace support;

namespace presyn {

int scalar_distance_error(
    output_example const& before, output_example const& after)
{
  assertion(
      before.output_args.signature() == after.output_args.signature(),
      "Can't compute error function on argument packs with different "
      "underlying signatures");

  for (auto param : before.output_args.signature().parameters) {
  }

  return 0;
}

} // namespace presyn
