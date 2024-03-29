#include "compile_context.h"

using namespace llvm;
using namespace props;

namespace synth {

/**
 * From what I've thought about, I think the best thing to do is to have a
 * context "own" / manage a single function which is created when we create a
 * context object - then we can also keep track of the appropriate basic blocks
 * with the context object as well.
 */
compile_context::compile_context(Module& mod, signature sig, accessor_map&& map)
    : sig_(sig)
    , mod_(mod)
    , func_(sig_.create_function(mod_))
    , entry_(BasicBlock::Create(mod_.getContext(), "entry", func_))
    , exit_(BasicBlock::Create(mod_.getContext(), "exit", func_))
    , metadata_(func_)
    , accessor_map_(std::move(map))
{
  auto& ctx = mod_.getContext();

  auto rt = func_->getFunctionType()->getReturnType();
  if (rt->isVoidTy()) {
    return_ = ReturnInst::Create(ctx, exit_);
  } else {
    auto zero = Constant::getNullValue(rt);
    return_ = ReturnInst::Create(ctx, zero, exit_);
  }
}

llvm::Argument* compile_context::argument(std::string const& name) const
{
  return std::next(func_->arg_begin(), sig_.param_index(name));
}

accessor const& compile_context::accessor_for(std::string const& name) const
{
  return accessor_map_(name);
}

std::set<llvm::Value*> compile_context::create_geps_for(std::string const& name,
    llvm::Value* base, llvm::Value* ptr, llvm::IRBuilder<>& builder,
    std::string const& prefix) const
{
  return accessor_for(name).create_geps(metadata_, base, ptr, builder, prefix);
}
} // namespace synth
