#include <support/similarity.h>

#include <cmath>

namespace support {

double return_similarity(uint64_t ret_a, uint64_t ret_b) { return 0.0; }

double params_similarity(call_builder const& a, call_builder const& b)
{
  return 0.0;
}

double similarity(uint64_t ret_a, call_builder const& a, uint64_t ret_b,
    call_builder const& b)
{
  if (a.signature() != b.signature()) {
    return 0.0;
  } else if (a == b) {
    return 1.0;
  }

  constexpr auto return_weight = 0.5;
  constexpr auto params_weight = (1 - return_weight);

  auto return_comp = return_weight * return_similarity(ret_a, ret_b);
  auto params_comp = params_weight * params_similarity(a, b);

  return return_comp + params_comp;
}

} // namespace support
