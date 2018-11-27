#include "regular_loop_fragment.h"

using namespace props;
using namespace llvm;

namespace synth {

// TODO: make an abstract validation function that can handle the common cases?

regular_loop_fragment::regular_loop_fragment(std::vector<props::value> args) :
  fragment(args)
{
  if(args_.size() != 2) {
    throw fragment_args_error("Regular loop requires exactly 2 arguments");
  }

  auto const& ptr_arg = args_.at(0);
  auto const& size_arg = args_.at(1);

  if(ptr_arg.value_type != value::type::parameter ||
     size_arg.value_type != value::type::parameter)
  { 
    throw fragment_args_error("Regular loop arguments must both be parameter references");
  }
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

llvm::Argument *regular_loop_fragment::get_pointer(compile_context& ctx)
{
  return ctx.argument(args_.at(0).param_val);
}

llvm::Argument *regular_loop_fragment::get_size(compile_context& ctx)
{
  return ctx.argument(args_.at(1).param_val);
}

}
