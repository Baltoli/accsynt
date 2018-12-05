#pragma once

#include "fragment.h"

#include <llvm/IR/BasicBlock.h>

namespace synth {

template <bool use_data>
class linear_fragment_base;

template <bool use_data>
void swap(linear_fragment_base<use_data>&, linear_fragment_base<use_data>&);

template <bool use_data>
class linear_fragment_base : public fragment {
public:
  linear_fragment_base(std::vector<props::value> args);

  linear_fragment_base(linear_fragment_base<use_data> const&) = default;
  linear_fragment_base<use_data>& operator=(linear_fragment_base<use_data>&) = default;

  linear_fragment_base(linear_fragment_base<use_data>&&) = default;
  linear_fragment_base<use_data>& operator=(linear_fragment_base<use_data>&&) = default;

  virtual fragment::frag_ptr clone();

  virtual void splice(compile_context& ctx, llvm::BasicBlock *entry, llvm::BasicBlock *exit);
  virtual bool add_child(frag_ptr&& f, size_t idx);

  virtual std::string to_str(size_t indent=0) override;

  virtual size_t count_holes() const override;

  friend void swap<use_data>(linear_fragment_base<use_data>& a, linear_fragment_base<use_data>& b);
};

template <bool use_data>
linear_fragment_base<use_data>::linear_fragment_base(
    std::vector<props::value> args) :
  fragment(args)
{
  if(!args.empty()) {
    throw std::invalid_argument("Linear fragments take no arguments");
  }
}

template <bool use_data>
fragment::frag_ptr linear_fragment_base<use_data>::clone()
{
  return clone_as(*this);
}

template <bool use_data>
std::string linear_fragment_base<use_data>::to_str(size_t indent)
{
  if constexpr(use_data) {
    return fmt::format("{}[linear region]", support::indent{indent});
  } else {
    return fmt::format("{}[empty region]", support::indent{indent});
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

  auto block = llvm::BasicBlock::Create(entry->getContext(), block_name, ctx.func_);

  llvm::BranchInst::Create(block, entry);  
  llvm::BranchInst::Create(exit, block);

  if constexpr(use_data) {
    ctx.metadata_.data_blocks.insert(block);
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

template <bool use_data>
void swap(linear_fragment_base<use_data>& a, linear_fragment_base<use_data>& b)
{
  using std::swap;
  swap(a.args_, b.args_);
}

using linear_fragment = linear_fragment_base<true>;
using empty_fragment = linear_fragment_base<false>;

}
