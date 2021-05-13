#include "sketch.h"

#include "sketch_context.h"

#include <support/thread_context.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IRBuilder.h>

using namespace support;
using namespace llvm;

namespace presyn {

sketch::sketch(Module& mod, props::signature sig, fragment const& frag)
    : module_(mod)
    , ctx_(module(), sig)
    , stubs_ {}
{
  auto function = sig.create_function(module());

  auto entry
      = BasicBlock::Create(thread_context::get(), "sketch.entry", function);
  auto exit
      = BasicBlock::Create(thread_context::get(), "sketch.exit", function);

  auto frag_entry = frag.compile(ctx_, exit);

  auto build = IRBuilder(entry);
  build.CreateBr(frag_entry);

  create_return_stub(exit);
}

sketch::sketch(
    Module& mod, props::signature sig, std::unique_ptr<fragment> const& frag)
    : sketch(mod, sig, *frag)
{
}

Module& sketch::module() { return module_; }

Module const& sketch::module() const { return module_; }

llvm::Value* sketch::create_return_stub(llvm::BasicBlock* exit)
{
  auto build = IRBuilder(exit);
  auto func = exit->getParent();
  auto ret_ty = func->getReturnType();

  if (ret_ty->isVoidTy()) {
    return build.CreateRetVoid();
  } else {
    auto call = build.Insert(ctx_.stub(ret_ty));
    return build.CreateRet(call);
  }
}

} // namespace presyn
