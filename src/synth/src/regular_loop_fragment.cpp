#include "regular_loop_fragment.h"

#include <fmt/format.h>

#include <llvm/IR/Instructions.h>
#include <llvm/IR/IRBuilder.h>

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
  // TODO: print child
  using namespace fmt::literals;
  auto str = "for(elt in {ptr}[0...{size}]) {{\nlive += elt\n}}"_format(
    "ptr"_a = args_.at(0).param_val,
    "size"_a = args_.at(1).param_val
  );

  os << str << '\n';
}

void regular_loop_fragment::splice(compile_context& ctx, llvm::BasicBlock *entry, llvm::BasicBlock *exit)
{
  // General structure of a regular loop: header that checks the value of the
  // iterator, body depending on children (entry / exit)
  if(children_.empty()) {
    // If no children, then we can just branch from entry to exit?
    BranchInst::Create(exit, entry);
  } else {
    auto ptr = get_pointer(ctx);
    auto size = get_size(ctx);

    auto header = BasicBlock::Create(ptr->getContext(), "loop-header", ctx.func_);
    auto pre_body = BasicBlock::Create(ptr->getContext(), "pre-body", ctx.func_);
    auto post_body = BasicBlock::Create(ptr->getContext(), "post-body", ctx.func_);

    auto B = IRBuilder<>(entry);
    B.CreateBr(header);

    B.SetInsertPoint(header);
    auto iter = B.CreatePHI(size->getType(), 2, "iter");
    iter->addIncoming(ConstantInt::get(iter->getType(), 0), entry);
    auto cond = B.CreateICmpSLT(iter, size);
    B.CreateCondBr(cond, pre_body, exit);

    B.SetInsertPoint(post_body);
    auto next = B.CreateAdd(iter, ConstantInt::get(iter->getType(), 1), "next-iter");
    iter->addIncoming(next, post_body);
    B.CreateBr(header);

    // TODO: gep?
    children_.at(0)->splice(ctx, pre_body, post_body);
  }
}

bool regular_loop_fragment::add_child(frag_ptr&& f)
{
  if(children_.empty()) {
    children_.push_back(std::move(f));
    return true;
  } else {
    return children_.front()->add_child(std::move(f));
  }
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
