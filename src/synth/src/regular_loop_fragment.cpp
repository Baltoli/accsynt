#include "regular_loop_fragment.h"

namespace synth {

regular_loop_fragment::regular_loop_fragment(std::vector<props::value> args) :
  fragment(args)
{
}

fragment::frag_ptr regular_loop_fragment::clone()
{
  return clone_as<regular_loop_fragment>();
}

void regular_loop_fragment::print(std::ostream& os, size_t indent)
{
  print_indent(os, indent);
  os << "[regular loop]\n";
}

void regular_loop_fragment::splice(compile_context& ctx, llvm::BasicBlock *entry, llvm::BasicBlock *exit)
{
}

bool regular_loop_fragment::add_child(frag_ptr&& f)
{
  return false;
}

}
