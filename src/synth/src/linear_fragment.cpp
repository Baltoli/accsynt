#include "linear_fragment.h"

#include "fragment_id.h"

namespace synth {

template <>
char linear_fragment::ID = 0;
static register_fragment_id<linear_fragment> X;

template <>
char empty_fragment::ID = 0;
static register_fragment_id<empty_fragment> Y;

} // namespace synth
