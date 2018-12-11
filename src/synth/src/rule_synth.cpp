#include "rule_synth.h"

#include "dataflow_synth.h"
#include "fragment.h"
#include "rules.h"

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
  auto fn = ctx.func_;
  auto meta = ctx.metadata_;

  auto data_synth = dataflow_synth(ctx);
  data_synth.create_dataflow();

  /* for(auto out_ptr : outputs) { */
  /*   // TODO: unsafe cast */
  /*   auto type = cast<PointerType>(out_ptr->getType())->getElementType(); */

  /*   auto block = out_ptr->getParent(); */
  /*   auto block_live = with_type(type, live.at(block)); */

  /*   if(!block_live.empty()) { */
  /*     // TODO: in some situations phis are preferable - basically if we have */
  /*     // nested loops. Work out a way to integrate this. */

  /*     auto store_val = *uniform_sample(block_live); */

  /*     // TODO: configure this from heuristics */
  /*     /1* auto phi_s = uniform_sample_if(block_live, [] (auto v) { *1/ */
  /*     /1*   return isa<PHINode>(v); *1/ */
  /*     /1* }); *1/ */
  /*     /1* if(phi_s != block_live.end()) { *1/ */
  /*     /1*   store_val = *phi_s; *1/ */
  /*     /1* } *1/ */
  /*     new StoreInst(store_val, out_ptr, block->getTerminator()); */
  /*   } */
  /* } */

  /* if(!rt->isVoidTy()) { */
  /*   auto ret = exit->getTerminator(); */
  /*   ret->eraseFromParent(); */

  /*   auto exit_live = live.at(exit); */
  /*   auto ret_val = *uniform_sample(with_type(rt, exit_live)); */
  /*   ReturnInst::Create(ctx, ret_val, exit); */
  /* } */

  current_fragment_++;
  llvm::errs() << *fn << '\n';
  return fn;
}

}
