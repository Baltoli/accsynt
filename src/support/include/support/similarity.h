#pragma once

#include <support/bit_cast.h>
#include <support/call_builder.h>

namespace support {

/**
 * Compute the similarity between the two call builders (before or after they
 * have been passed to a call_wrapper and potentially modified).
 *
 * The design of this metric is currently as follows:
 *  - A score of 1.0 indicates that the two are totally identical (i.e. they
 *    compare equal using operator==).
 *  - If the two have different type signatures, then the two are the "least
 *    similar" they possibly could be, so return 0.0.
 *  - Otherwise, the following rules are used to define similarity:
 */
double similarity(uint64_t ret_a, call_builder const& a, uint64_t ret_b,
    call_builder const& b);

/**
 * Compute the similarity between two return values using a templated algorithm
 * and bitcasting that should work the same between both versions.
 */
template <typename Num>
double scalar_similarity(uint64_t ret_a, uint64_t ret_b)
{
  if (ret_a == ret_b) {
    return 1.0;
  }

  constexpr auto sign_penalty = 0.75;

  auto a_val = bit_cast<Num>(ret_a);
  auto b_val = bit_cast<Num>(ret_b);

  double a_abs = std::abs(a_val);
  double b_abs = std::abs(b_val);

  auto max_v = std::max(a_abs, b_abs);
  auto min_v = std::min(a_abs, b_abs);

  auto diff = max_v - min_v;
  auto mean = (a_abs + b_abs) / 2;

  auto score = 1 - std::tanh(diff / mean);
  if (std::signbit(a_val) != std::signbit(b_val)) {
    return sign_penalty * score;
  } else {
    return score;
  }
}

} // namespace support
