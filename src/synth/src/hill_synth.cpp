#include "hill_synth.h"
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

Function* hill_synth::generate() { return nullptr; }

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
