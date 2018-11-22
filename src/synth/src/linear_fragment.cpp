#include "linear_fragment.h"

namespace synth {

void linear_fragment::print(std::ostream& os, size_t indent)
{
  os << "I am linear_fragment\n";
}

void linear_fragment::splice(compile_context& ctx, llvm::BasicBlock *entry, llvm::BasicBlock *exit)
{
}

bool linear_fragment::add_child(frag_ptr&& f)
{
  return false;
}

}
