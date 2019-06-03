#include <support/similarity.h>

#include <numeric_limits>

namespace support {

double similarity(call_builder const& a, call_builder const& b)
{
  if (a.signature() != b.signature()) {
    return std::numeric_limits<double>::infinity();
  } else if (a == b) {
    return 0.0;
  }

  return 1.0;
}

} // namespace support
