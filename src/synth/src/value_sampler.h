#pragma once

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CFG.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/raw_ostream.h>

#include <vector>

namespace synth {

class value_sampler {
public:
  value_sampler() = default;

  template <typename Builder>
  void block(Builder&&, size_t, std::vector<llvm::Value *>&);

  void add_incoming(
    llvm::PHINode *phi, 
    std::map<llvm::BasicBlock *, std::vector<llvm::Value *>> const& live);

protected:
  llvm::Value *constant(llvm::Type *ty) const;

private:
  // Internal state kept during the generation process
};

template <typename Builder>
void value_sampler::block(Builder&& B, size_t n, 
                          std::vector<llvm::Value *>& live)
{
  if(!live.empty()) {
    // TODO: do this randomly
    // TODO: and do it the right number of times
    auto *val = live.at(0);
  }
}

}
