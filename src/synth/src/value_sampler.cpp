#include "value_sampler.h"

#include <support/llvm_values.h>
#include <support/random.h>

#include <llvm/IR/Constant.h>

using namespace support;
using namespace llvm;

namespace synth {

void value_sampler::add_incoming(
    PHINode *phi, 
    std::map<llvm::BasicBlock *, std::vector<Value *>> const& live)
{
  auto ty = phi->getType();
  auto block = phi->getParent();

  auto uses = all_uses(phi);

  for(auto pred : predecessors(block)) {
    auto pred_live = with_type(ty, live.at(pred));
    pred_live.erase(phi);

    if(pred_live.empty()) {
      phi->addIncoming(constant(ty), pred);
    } else {
      if(uses.empty()) {
        auto val = uniform_sample(pred_live);
        phi->addIncoming(*val, pred);
      } else {
        auto use_live = std::set<llvm::Value *>{};
        for(auto p : pred_live) {
          if(uses.find(p) != uses.end()) {
            use_live.insert(p);
          }
        }
        
        if(use_live.empty()) {
          auto val = uniform_sample(pred_live);
          phi->addIncoming(*val, pred);
        } else {
          auto val = uniform_sample(use_live);
          phi->addIncoming(*val, pred);
        }
      }
    }
  }
}

Value *value_sampler::constant(Type *ty) const
{
  return Constant::getNullValue(ty);
}

}
