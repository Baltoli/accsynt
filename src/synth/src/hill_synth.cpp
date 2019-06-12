#include "hill_synth.h"
#include "rules.h"

#include <fmt/format.h>

using namespace support;
using namespace props;
using namespace llvm;

namespace synth {

hill_synth::hill_synth(property_set ps, call_wrapper& ref)
    : choices_{}
    , properties_(ps)
    , reference_(ref)
{
  for (auto rule : rule_registry::all()) {
    auto matches = rule.match(ps);
    for (auto&& choice : matches) {
      choices_.push_back(choice);
    }
  }
}

Function* hill_synth::generate()
{
  for (int i = 0; i < 3; ++i) {
    auto sol = fragment::sample(choices_, 2);
    fmt::print("{}\n\n", sol->to_str());
  }
  return nullptr;
}

} // namespace synth
