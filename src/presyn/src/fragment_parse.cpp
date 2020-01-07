#include "fragment_parse.h"
#include "fragment.h"

#include <support/assert.h>

namespace presyn {

std::unique_ptr<fragment> fragment::parse(std::string_view) { unimplemented(); }

} // namespace presyn
