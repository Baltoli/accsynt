#include "hill_synth.h"

#include "compile_context.h"
#include "generator_rules.h"
#include "rules.h"

#include <support/thread_context.h>

#include <fmt/format.h>

using namespace support;
using namespace props;
using namespace llvm;

namespace synth {

hill_synth::hill_synth(property_set ps, call_wrapper& ref)
    : mod_("hill-synth", thread_context::get())
    , choices_ {}
    , properties_(ps)
{
  for (auto rule : rule_registry::all()) {
    auto matches = rule.match(ps);
    for (auto&& choice : matches) {
      choices_.push_back(choice);
    }
  }
}

// This will be a large overall method containing the full generation of any /
// all possible functions - it needs to handle score tracking, fragment
// sampling / enumeration and progress printing (i.e. seeing how scores / number
// of fragments / programs etc. evolve as the process goes on).
generate_result hill_synth::generate()
{
  auto ctx = compile_context(mod_, properties_.type_signature);
  auto frag = fragment::sample(choices_, 2);
  frag->compile(ctx);

  return {1, ctx.func_};
}

} // namespace synth
