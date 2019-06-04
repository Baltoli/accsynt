#pragma once

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

} // namespace support
