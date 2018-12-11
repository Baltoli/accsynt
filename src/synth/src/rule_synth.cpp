#include "rule_synth.h"

#include "fragment.h"
#include "rules.h"

namespace synth {

rule_synth::rule_synth(props::property_set ps, call_wrapper& ref) :
  synthesizer(ps, ref)
{
  auto choices = std::vector<fragment::frag_ptr>{};

  for(auto rule : rule_registry::all()) {
    auto matches = rule.match(ps);
    for(auto&& choice : matches) {
      choices.push_back(std::move(choice));
    }
  }

  fragments_ = fragment::enumerate(std::move(choices));
}

std::string rule_synth::name() const
{
  return "rule_synth";
}

llvm::Function *rule_synth::candidate()
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

  current_fragment_++;
  return ctx.func_;
}

}
