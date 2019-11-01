#include "fragment_id.h"

#include <set>

namespace synth::detail {

std::set<char*>& reg_ptrs()
{
  static std::set<char*> ret {};
  return ret;
}

void register_frag(char* ptr) { reg_ptrs().insert(ptr); }

std::optional<int> get_id(char* ptr)
{
  auto found = reg_ptrs().find(ptr);

  if (found == reg_ptrs().end()) {
    return std::nullopt;
  } else {
    return std::distance(reg_ptrs().begin(), found);
  }
}

} // namespace synth::detail
