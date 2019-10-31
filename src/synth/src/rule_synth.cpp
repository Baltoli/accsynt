#include "rule_synth.h"

#include "accessor_rules.h"
#include "dataflow_synth.h"
#include "fragment.h"
#include "generator_rules.h"
#include "linear_fragment.h"
#include "rules.h"
#include "synth_options.h"

#include <model/model.h>

#include <support/argument_generator.h>
#include <support/file.h>
#include <support/hash.h>

#include <fmt/format.h>

#include <llvm/Support/CommandLine.h>

using namespace support;
using namespace llvm;

namespace synth {

rule_synth::rule_synth(props::property_set ps, call_wrapper& ref)
    : synthesizer(ps, ref)
{
  using namespace fmt::literals;

  make_examples(generator_for(ps), 1'000);

  auto choices = std::vector<fragment::frag_ptr> {};

  if (NewRules) {
    ps = model::predict(ps);
  }

  for (auto rule : rule_registry::all()) {
    auto matches = rule.match(ps);
    for (auto&& choice : matches) {
      choices.push_back(choice);
    }
  }

  if (choices.empty()) {
    choices.emplace_back(new linear_fragment { {} });
  }

  auto max_frags = std::optional<size_t> {};
  if (MaxFragments >= 0) {
    max_frags = MaxFragments;
  }

  fragments_ = fragment::enumerate(choices, max_frags);

  to_file_or_default(ControlOutputFile, [&](auto& os) {
    if (DumpControl) {
      for (auto const& frag : fragments_) {
        os << "FRAGMENT {hash}:\n{frag}\n\n"_format(
            "hash"_a = nice_hash(frag), "frag"_a = frag->to_str(1));
      }
    }

    if (CountControl) {
      os << "Total fragments: {fs}\n"_format("fs"_a = fragments_.size());
    }
  });
}

std::string rule_synth::name() const { return "rule_synth"; }

Function* rule_synth::candidate()
{
  if (fragments_.empty()) {
    return nullptr;
  }

  if (current_fragment_ == fragments_.end()) {
    current_fragment_ = fragments_.begin();
  }

  auto ctx = compile_context { mod_, properties_.type_signature,
    accessors_from_rules(properties_) };
  auto& frag = *current_fragment_;

  frag->compile(ctx);
  auto fn = ctx.func_;
  auto meta = ctx.metadata_;

  auto data_synth = dataflow_synth(ctx);
  data_synth.create_dataflow();
  data_synth.create_outputs();

  current_fragment_++;

  if (AllPrograms) {
    errs() << *fn << '\n';
  }

  return fn;
}

} // namespace synth
