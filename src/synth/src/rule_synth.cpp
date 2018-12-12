#include "rule_synth.h"

#include "dataflow_synth.h"
#include "fragment.h"
#include "rules.h"

#include <llvm/Support/CommandLine.h>

using namespace llvm;

static cl::opt<int>
MaxFragments(
    "max-fragments", cl::desc("Maximum fragments to combine"), 
    cl::init(-1));

namespace synth {

rule_synth::rule_synth(props::property_set ps, call_wrapper& ref) :
  synthesizer(ps, ref),
  gen_(ps)
{
  make_examples(gen_, 1'000);

  auto choices = std::vector<fragment::frag_ptr>{};

  for(auto rule : rule_registry::all()) {
    auto matches = rule.match(ps);
    for(auto&& choice : matches) {
      choices.push_back(std::move(choice));
    }
  }

  auto max_frags = std::optional<size_t>{};
  if(MaxFragments >= 0) {
    max_frags = MaxFragments;
  }

  fragments_ = fragment::enumerate(std::move(choices), max_frags);
  for(auto& f : fragments_) {
    errs() << "#############################\n";
    errs() << f->to_str() << "\n\n";
  }
  errs() << fragments_.size() << '\n';
  __builtin_trap();
}

std::string rule_synth::name() const
{
  return "rule_synth";
}

Function *rule_synth::candidate()
{
  if(fragments_.empty()) {
    return nullptr;
  }

  if(current_fragment_ == fragments_.end()) {
    current_fragment_ = fragments_.begin();
  }

  auto ctx = compile_context{mod_, properties_.type_signature};
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
