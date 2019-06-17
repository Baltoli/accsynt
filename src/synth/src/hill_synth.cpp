#include "hill_synth.h"

#include "compile_context.h"
#include "evaluator.h"
#include "generator_rules.h"
#include "gp_sampler.h"
#include "rules.h"

#include <support/thread_context.h>

#include <fmt/format.h>

using namespace support;
using namespace props;
using namespace llvm;

namespace synth {

hill_synth::hill_synth(property_set ps, call_wrapper& ref)
    : mod_("hill-synth", thread_context::get())
    , eval_(make_examples(ps, ref))
    , choices_{}
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

// This will be a large overall method containing the full generation of any /
// all possible functions - it needs to handle score tracking, fragment
// sampling / enumeration and progress printing (i.e. seeing how scores / number
// of fragments / programs etc. evolve as the process goes on).
Function* hill_synth::generate()
{
  auto sampler = gp_sampler(eval_);

  // interim process before I get the full score-tracking machinery up and
  // running.
  auto ctx = compile_context(mod_, properties_.type_signature);
  auto frag = fragment::sample(choices_, 2);
  frag->compile(ctx);

  sampler.sample(properties_, ctx.metadata_);

  return ctx.func_;
}

example_set hill_synth::make_examples(property_set ps, call_wrapper& ref)
{
  auto examples = example_set{};

  auto gen = generator_for(ps);
  for (auto i = 0; i < num_examples; ++i) {
    auto cb = ref.get_builder();
    gen.gen_args(cb);
    auto before = cb;
    auto ret = ref.call(cb);
    examples.push_back({ before, { ret, cb } });
  }

  return examples;
}

} // namespace synth
