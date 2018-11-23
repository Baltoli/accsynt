#pragma once

#include "fragment.h"

namespace synth {

class linear_fragment : public fragment {
public:
  using fragment::fragment;
  using fragment::print;

  virtual void print(std::ostream& os, size_t indent) override;
  virtual void splice(compile_context& ctx, llvm::BasicBlock *entry, llvm::BasicBlock *exit);
  virtual bool add_child(frag_ptr&& f);

private:
};

}
