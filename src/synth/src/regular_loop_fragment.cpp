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
  auto n_childs = children_.size();

  if(n_childs >= 1) {
    children_.at(0)->print(os, indent);
  }

  if(n_childs >= 2) {
    print_indent(os, indent); 
    os << "[regular loop] {\n";
    children_.at(1)->print(os, indent+1);
    print_indent(os, indent);
    os << "}\n";
  }

  if(n_childs >= 3) {
    children_.at(2)->print(os, indent);
  }
}

void regular_loop_fragment::splice(compile_context& ctx, llvm::BasicBlock *entry, llvm::BasicBlock *exit)
{
  auto& llvm_ctx = entry->getContext();

  auto inter_first = BasicBlock::Create(llvm_ctx, "reg-loop.inter0", ctx.func_);
  auto inter_second = BasicBlock::Create(llvm_ctx, "reg-loop.inter1", ctx.func_);

  auto n_childs = children_.size();
  auto last_exit = entry;
  
  if(n_childs >= 1) {
    children_.at(0)->splice(ctx, last_exit, inter_first);
    last_exit = inter_first;
  }

  if(n_childs >= 2) {
    auto ptr = get_pointer(ctx);
    auto size = get_size(ctx);

    auto header = BasicBlock::Create(llvm_ctx, "reg-loop.header", ctx.func_);
    auto pre_body = BasicBlock::Create(llvm_ctx, "reg-loop.pre-body", ctx.func_);
    auto post_body = BasicBlock::Create(llvm_ctx, "reg-loop.post-body", ctx.func_);

    auto B = IRBuilder<>(inter_first);
    B.CreateBr(header);

    B.SetInsertPoint(header);
    auto iter = B.CreatePHI(size->getType(), 2, "reg-loop.iter");
    iter->addIncoming(ConstantInt::get(iter->getType(), 0), inter_first);
    auto cond = B.CreateICmpSLT(iter, size, "reg-loop.cond");
    B.CreateCondBr(cond, pre_body, inter_second);

    B.SetInsertPoint(pre_body);
    auto gep = B.CreateGEP(ptr, iter, "reg-loop.gep");
    auto load = B.CreateLoad(gep, "reg-loop.load");

    B.SetInsertPoint(post_body);
    auto next = B.CreateAdd(iter, ConstantInt::get(iter->getType(), 1), "reg-loop.next-iter");
    iter->addIncoming(next, post_body);
    B.CreateBr(header);

    children_.at(1)->splice(ctx, pre_body, post_body);
    last_exit = inter_second;
  }

  if(n_childs >= 3) {
    children_.at(2)->splice(ctx, last_exit, exit);
    last_exit = exit;
  }

  if(last_exit != exit) {
    BranchInst::Create(exit, last_exit);
  }
}

bool regular_loop_fragment::add_child(frag_ptr&& f)
{
  if(children_.size() < 3) {
    children_.push_back(std::move(f));
    return true;
  } else {
    for(auto& child : children_) {
      if(child->add_child(std::move(f))) {
        return true;
      }
    }
  }

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
