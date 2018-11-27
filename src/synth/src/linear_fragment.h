#pragma once

#include "fragment.h"

#include <llvm/IR/BasicBlock.h>

namespace synth {

class linear_fragment : public fragment {
public:
  using fragment::fragment;
  using fragment::print;

  virtual fragment::frag_ptr clone();

  virtual void print(std::ostream& os, size_t indent) override;
  virtual void splice(compile_context& ctx, llvm::BasicBlock *entry, llvm::BasicBlock *exit);
  virtual bool add_child(frag_ptr&& f);

private:
  llvm::BasicBlock *block_;
};

}
