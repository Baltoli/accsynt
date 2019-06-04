#include <props/props.h>
#include <support/bit_cast.h>
#include <support/similarity.h>

#include <cmath>

namespace support {

template <typename Num>
double return_similarity(uint64_t ret_a, uint64_t ret_b)
{
  auto a_val = bit_cast<Num>(ret_a);
  auto b_val = bit_cast<Num>(ret_b);

  auto a_abs = std::abs(a_val);
  auto b_abs = std::abs(b_val);

  auto ratio = std::max(a_abs, b_abs) / std::min(a_abs, b_abs);

  return std::tanh(std::log(ratio));
}

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

  auto return_weight = 0.5;
  auto return_comp = 0.0;
  auto params_weight = 0.5;

  auto const& sig = a.signature();
  if (auto rt_opt = sig.return_type) {
    if (*rt_opt == props::data_type::integer) {
      return_comp = return_similarity<int>(ret_a, ret_b);
    } else if (*rt_opt == props::data_type::floating) {
      return_comp = return_similarity<float>(ret_a, ret_b);
    } else {
      throw std::runtime_error("Invalid return type for metric");
    }
  } else {
    return_weight = 0.0;
    params_weight = 1.0;
  }

  auto params_comp = params_similarity(a, b);
  return return_weight * return_comp + params_weight * params_comp;
}

} // namespace support
