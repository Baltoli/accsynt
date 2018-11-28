#include "linear_fragment.h"

#include <llvm/IR/Instructions.h>

using namespace llvm;

namespace synth {

fragment::frag_ptr linear_fragment::clone()
{
  return clone_as<linear_fragment>();
}

void linear_fragment::print(std::ostream& os, size_t indent)
{
  print_indent(os, indent);
  os << "[linear region]" << '\n';
}

/**
 * How does a linear fragment get spliced in between two basic blocks?
 * It needs to keep track of its own block of instructions.
 */
void linear_fragment::splice(compile_context& ctx, llvm::BasicBlock *entry, llvm::BasicBlock *exit)
{
  block_ = BasicBlock::Create(entry->getContext(), "linear.block", ctx.func_);

  BranchInst::Create(block_, entry);  
  BranchInst::Create(exit, block_);

  ctx.metadata_.data_blocks.insert(block_);
}

bool linear_fragment::add_child(frag_ptr&& f)
{
  return false;
}

}
