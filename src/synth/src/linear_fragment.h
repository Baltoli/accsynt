#pragma once

#include "fragment.h"

#include <llvm/IR/BasicBlock.h>

namespace synth {

template <bool add_data>
class linear_fragment_base : public fragment {
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

template <bool use_data>
fragment::frag_ptr linear_fragment_base<use_data>::clone()
{
  return clone_as<linear_fragment_base<use_data>>();
}

template <bool use_data>
void linear_fragment_base<use_data>::print(std::ostream& os, size_t indent)
{
  if constexpr(use_data) {
    print_indent(os, indent);
    os << "[linear region]" << '\n';
  }
}

/**
 * How does a linear fragment get spliced in between two basic blocks?
 * It needs to keep track of its own block of instructions.
 */
template <bool use_data>
void linear_fragment_base<use_data>::splice(compile_context& ctx, llvm::BasicBlock *entry, llvm::BasicBlock *exit)
{
  auto block_name = [] {
    if constexpr(use_data) {
      return "linear.block";
    } else {
      return "empty.block";
    }
  }();

  block_ = llvm::BasicBlock::Create(entry->getContext(), block_name, ctx.func_);

  llvm::BranchInst::Create(block_, entry);  
  llvm::BranchInst::Create(exit, block_);

  if constexpr(use_data) {
    ctx.metadata_.data_blocks.insert(block_);
  }
}

template <bool use_data>
bool linear_fragment_base<use_data>::add_child(frag_ptr&& f)
{
  return false;
}

using linear_fragment = linear_fragment_base<true>;
using empty_fragment = linear_fragment_base<false>;

}
