#include "rule_synth.h"

#include "accessor_rules.h"
#include "dataflow_synth.h"
#include "fragment.h"
#include "rules.h"

#include <llvm/Support/CommandLine.h>

using namespace support;
using namespace llvm;

static cl::opt<int> MaxFragments(
    "max-fragments", cl::desc("Maximum fragments to combine"), cl::init(-1));

static cl::opt<bool> DumpControl("dump-control",
    cl::desc("Dump control flow before synthesis"), cl::init(false));

namespace synth {

rule_synth::rule_synth(props::property_set ps, call_wrapper& ref)
    : synthesizer(ps, ref)
    , gen_(ps)
{
  make_examples(gen_adaptor(gen_), 1'000);

  auto choices = std::vector<fragment::frag_ptr>{};

  for (auto rule : rule_registry::all()) {
    auto matches = rule.match(ps);
    for (auto&& choice : matches) {
      choices.push_back(choice);
    }
  }

  auto max_frags = std::optional<size_t>{};
  if (MaxFragments >= 0) {
    max_frags = MaxFragments;
  }

  fragments_ = fragment::enumerate(choices, max_frags);

  if (DumpControl) {
    for (auto const& frag : fragments_) {
      errs() << "FRAGMENT:\n";
      errs() << frag->to_str(1) << "\n\n";
    }
  }
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

  auto ctx = compile_context{ mod_, properties_.type_signature,
    accessors_from_rules(properties_) };
  auto& frag = *current_fragment_;

  frag->compile(ctx);
  auto fn = ctx.func_;
  auto meta = ctx.metadata_;

  auto data_synth = dataflow_synth(ctx);
  data_synth.create_dataflow();
  data_synth.create_outputs();

  current_fragment_++;
  return fn;
}
}
