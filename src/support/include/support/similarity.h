#pragma once

#include <support/call_builder.h>

namespace support {

/**
 * Compute the similarity between the two call builders (before or after they
 * have been passed to a call_wrapper and potentially modified).
 *
 * The design of this metric is currently as follows:
 *  - A score of 0.0 indicates that the two are totally identical (i.e. they
 *    compare equal using operator==).
 *  - If the two have different type signatures, then the two are the "least
 *    similar" they possibly could be, so return infinity.
 *  - Otherwise, the following rules are used to define similarity:
 */
double similarity(call_builder const& a, call_builder const& b);

} // namespace support
