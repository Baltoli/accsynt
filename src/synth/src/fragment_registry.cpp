#include "rules.h"

#include "affine_fragment.h"
#include "data_loop_fragment.h"
#include "loop_to_n_fragment.h"
#include "regular_loop_fragment.h"
#include "string_loop_fragment.h"

using namespace bsc;
using namespace props;
using namespace support;

namespace synth {

value_ptr<fragment> fragment_registry::get(
    std::string const& name, std::vector<value> args)
{
  if (name == "regularLoop") {
    return make_val<regular_loop_fragment>(args);
  }

  if (name == "outputLoop") {
    return make_val<regular_loop_fragment>(args, true);
  }

  if (name == "dataLoop") {
    return make_val<data_loop_fragment>(args);
  }

  if (name == "stringLoop") {
    return make_val<string_loop_fragment>(args);
  }

  if (name == "stringOutputLoop") {
    return make_val<string_loop_fragment>(args, true);
  }

  if (name == "affineAccess") {
    return make_val<affine_fragment>(args);
  }

  if (name == "loopToN") {
    return make_val<loop_to_n_fragment>(args);
  }

  return nullptr;
}

} // namespace synth
