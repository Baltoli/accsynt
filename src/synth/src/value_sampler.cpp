#include "value_sampler.h"

#include <support/llvm_values.h>
#include <support/random.h>

#include <llvm/IR/Constant.h>

using namespace support;
using namespace llvm;

namespace synth {

// Sampling predicates

bool both_floats(Type* t1, Type* t2)
{
  return t1->isFloatTy() && t2->isFloatTy();
}

bool one_float(llvm::Type* t, llvm::Type*) { return t->isFloatTy(); }

bool same_ints(llvm::Type* t1, llvm::Type* t2)
{
  return t1->isIntegerTy() && t2->isIntegerTy()
      && (t1->getIntegerBitWidth() == t2->getIntegerBitWidth());
}

bool one_int(llvm::Type* t, llvm::Type*) { return t->isIntegerTy(); }

bool same_type(llvm::Type* t1, llvm::Type* t2) { return t1 == t2; }

// Sampler implementation

void value_sampler::add_incoming(
    PHINode* phi, std::map<llvm::BasicBlock*, std::vector<Value*>> const& live)
{
  auto ty = phi->getType();
  auto block = phi->getParent();

  auto uses = all_uses(phi);

  for (auto pred : predecessors(block)) {
    auto pred_live = with_type(ty, live.at(pred));
    pred_live.insert(Constant::getNullValue(ty));
    pred_live.erase(phi);

    if (uses.empty()) {
      auto val = uniform_sample(pred_live);
      phi->addIncoming(*val, pred);
    } else {
      auto use_live = std::set<llvm::Value*>{};
      for (auto p : pred_live) {
        if (uses.find(p) != uses.end()) {
          use_live.insert(p);
        }
      }

      if (use_live.empty()) {
        auto val = uniform_sample(pred_live);
        phi->addIncoming(*val, pred);
      } else {
        auto val = uniform_sample(use_live);
        phi->addIncoming(*val, pred);
      }
    }
  }
}

Value* value_sampler::constant(Type* ty) const
{
  return Constant::getNullValue(ty);
}
} // namespace synth
