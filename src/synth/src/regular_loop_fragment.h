#pragma once

#include "fragment.h"

namespace synth {

class regular_loop_fragment : public fragment {
public:
  using fragment::add_child;
  using fragment::print;

  regular_loop_fragment(std::vector<props::value> args);

  virtual fragment::frag_ptr clone();

  virtual void print(std::ostream& os, size_t indent) override;
  virtual void splice(compile_context& ctx, llvm::BasicBlock *entry, llvm::BasicBlock *exit);
  virtual bool add_child(frag_ptr&& f, size_t idx);

  virtual size_t count_holes() const override;

private:
  llvm::Argument *get_pointer(compile_context&);
  llvm::Argument *get_size(compile_context&);
};

}
