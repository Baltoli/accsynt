#include <props/props.h>
#include <support/similarity.h>

#include <cmath>

using namespace props;

namespace support {

double similarity(uint64_t ret_a, call_builder const& a, uint64_t ret_b,
    call_builder const& b)
{
  if (a.signature() != b.signature()) {
    return 0.0;
  } else if (ret_a == ret_b && a == b) {
    return 1.0;
  }

  // Weight the params equally if the signature accepts any pointers, otherwise
  // just look at the return value.
  auto return_weight = a.signature().accepts_pointer() ? 0.5 : 1.0;
  auto return_comp = 0.0;

  auto params_weight = 1.0 - return_weight;

  auto const& sig = a.signature();
  if (auto rt_opt = sig.return_type) {
    if (rt_opt->base == props::base_type::integer) {
      return_comp
          = scalar_similarity(bit_cast<int>(ret_a), bit_cast<int>(ret_b));
    } else if (rt_opt->base == props::base_type::floating) {
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

double mean(std::vector<double> const& v)
{
  auto sum = 0.0;
  for (auto d : v) {
    sum += d;
  }
  return sum / v.size();
}

template <typename T>
auto vector_similarity_func(
    call_builder const& a, call_builder const& b, std::vector<double>& scores)
{
  return [&a, &b, &scores](param const& p) {
    auto a_vec = a.get<std::vector<T>>(p.name);
    auto b_vec = b.get<std::vector<T>>(p.name);
    auto sim_vec = std::vector<double>{};

    // TODO: what if different sizes?
    for (auto i = 0u; i < a_vec.size(); ++i) {
      sim_vec.push_back(scalar_similarity<T>(a_vec[i], b_vec[i]));
    }

    scores.push_back(mean(sim_vec));
  };
}

double params_similarity(call_builder const& a, call_builder const& b)
{
  // Should only be called from `similarity`, which enforces this condition
  // anyway.
  assert(a.signature() == b.signature());

  if (a == b) {
    return 1.0;
  }

  auto scores = std::vector<double>{};

  // clang-format off
  sig_visitor{
    on(base_type::integer, 1, vector_similarity_func<int>(a, b, scores)),
    on(base_type::floating, 1, vector_similarity_func<float>(a, b, scores))
  }.visit(a.signature());
  // clang-format on

  if (scores.empty()) {
    return 1.0;
  } else {
    return mean(scores);
  }
}

} // namespace support
