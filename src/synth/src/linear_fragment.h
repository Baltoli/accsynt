#pragma once

#include "fragment.h"

#include <llvm/IR/BasicBlock.h>

namespace synth {

template <bool add_data>
class linear_fragment_base : public fragment {
public:
  using fragment::fragment;

  virtual fragment::frag_ptr clone();

  virtual void splice(compile_context& ctx, llvm::BasicBlock *entry, llvm::BasicBlock *exit);
  virtual bool add_child(frag_ptr&& f, size_t idx);

  virtual std::string to_str(size_t indent=0) override;

  virtual size_t count_holes() const override;

private:
  llvm::BasicBlock *block_;
};

template <bool use_data>
fragment::frag_ptr linear_fragment_base<use_data>::clone()
{
  return clone_as(*this);
}

template <bool use_data>
std::string linear_fragment_base<use_data>::to_str(size_t indent)
{
  // TODO indent
  return "[linear region]";
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
bool linear_fragment_base<use_data>::add_child(frag_ptr&& f, size_t idx)
{
  return false;
}

template <bool use_data>
size_t linear_fragment_base<use_data>::count_holes() const
{
  return 0;
}

using linear_fragment = linear_fragment_base<true>;
using empty_fragment = linear_fragment_base<false>;

}
