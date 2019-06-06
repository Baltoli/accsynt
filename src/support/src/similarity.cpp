#include <props/props.h>
#include <support/similarity.h>

#include <cmath>

namespace support {

double similarity(uint64_t ret_a, call_builder const& a, uint64_t ret_b,
    call_builder const& b)
{
  if (a.signature() != b.signature()) {
    return 0.0;
  } else if (ret_a == ret_b && a == b) {
    return 1.0;
  }

  auto return_weight = 0.5;
  auto return_comp = 0.0;
  auto params_weight = 0.5;

  auto const& sig = a.signature();
  if (auto rt_opt = sig.return_type) {
    if (*rt_opt == props::data_type::integer) {
      return_comp
          = scalar_similarity(bit_cast<int>(ret_a), bit_cast<int>(ret_b));
    } else if (*rt_opt == props::data_type::floating) {
      return_comp
          = scalar_similarity(bit_cast<float>(ret_a), bit_cast<float>(ret_b));
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

double params_similarity(call_builder const& a, call_builder const& b)
{
  // Should only be called from `similarity`, which enforces this condition
  // anyway.
  assert(a.signature() == b.signature());

  if (a == b) {
    return 1.0;
  }

  double score = 0.0;
  int n = 0;

  // clang-format off
  auto visitor = props::sig_visitor{
    [&] {
      score += scalar_similarity<int>(a.get<int>(n), b.get<int>(n));
      n += 1;
    },
    [&] {
      score += scalar_similarity<float>(a.get<float>(n), b.get<float>(n));
      n += 1;
    },
    [&](int d) {
      if(d > 1) { throw std::runtime_error("Pointers nested"); }

      n += 1;
    },
    [&](int d) {
      if(d > 1) { throw std::runtime_error("Pointers nested"); }

      n += 1;
    }
  };
  // clang-format on

  visitor.visit(a.signature());

  if (n == 0) {
    return 1.0;
  } else {
    return score / n;
  }
}

} // namespace support
