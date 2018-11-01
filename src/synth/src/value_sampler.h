#pragma once

#include <support/random.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CFG.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Intrinsics.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/raw_ostream.h>

#include <vector>

namespace synth {

/*
 * TODO: this is BLAS specific code - need to tidy it up and put it behind a
 * more general interface so that other domains can then pick how they want to
 * build their dataflow. Keeping instructions restricted for now.
 */
class value_sampler {
public:
  value_sampler() = default;

  template <typename Builder>
  void block(Builder&&, size_t, std::vector<llvm::Value *>&);

  void add_incoming(
    llvm::PHINode *phi, 
    std::map<llvm::BasicBlock *, std::vector<llvm::Value *>> const& live);

  llvm::Value *constant(llvm::Type *ty) const;

protected:
  template <typename Builder>
  llvm::Value *arithmetic(Builder&& B, llvm::Value *v1, llvm::Value *v2) const;

private:
  // Internal state kept during the generation process
};

template <typename Builder>
void value_sampler::block(Builder&& B, size_t n, 
                          std::vector<llvm::Value *>& live)
{
  auto non_const = [] (auto *v) {
    return !llvm::isa<llvm::Constant>(v);
  };

  for(auto i = 0u; i < n; ++i) {
    if(!live.empty()) {
      auto v1 = support::uniform_sample_if(live, non_const);
      auto v2 = support::uniform_sample_if(live, non_const);
      if(v1 != live.end() && v2 != live.end()) { 
        live.push_back(arithmetic(B, *v1, *v2));
      }
    }
  }
}

template <typename Builder>
llvm::Value *make_fabs(Builder&& B, llvm::Value *v1)
{
  auto mod = B.GetInsertBlock()->getParent()->getParent();
  auto intrinsic = llvm::Intrinsic::getDeclaration(mod, llvm::Intrinsic::fabs, v1->getType());
  return B.CreateCall(intrinsic, v1);
}

template <typename Builder>
llvm::Value *value_sampler::arithmetic(
    Builder&& B, llvm::Value *v1, llvm::Value *v2) const
{
  // TODO: be more forgiving to different types being passed in here - look for
  // common base type etc and try to do some extensions / upcasting
  
  if(v1->getType() != v2->getType()) {
    return nullptr;
  }

  // TODO: check integer vs. floating point etc
  auto choice = support::random_int(0, 1);
  switch(choice) {
    case 0: return B.CreateFAdd(v1, v2);
    case 1: return B.CreateFMul(v1, v2);
    case 2: return make_fabs(std::forward<decltype(B)>(B), v1);
    case 3: return B.CreateFSub(v1, v2);
  }

  __builtin_unreachable();
}


}
