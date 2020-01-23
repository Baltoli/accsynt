#include "sketch_context.h"

#include "stub.h"

#include <support/assert.h>
#include <support/thread_context.h>

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>

using namespace support;
using namespace llvm;

namespace presyn {

sketch_context::sketch_context(Module& mod, props::signature sig)
    : module_(mod)
    , sig_(sig)
    , opaque_type_(StructType::create(thread_context::get(), "opaque"))
{
}

llvm::Function* sketch_context::stub() { return stub(opaque_type_); }

llvm::Function* sketch_context::stub(llvm::Type* ty)
{
  if (stubs_.find(ty) == stubs_.end()) {
    auto func_type = FunctionType::get(ty, false);
    auto func = Function::Create(
        func_type, GlobalValue::InternalLinkage, "stub", module_);

    stubs_[ty] = func;
  }

  return stubs_[ty];
}

} // namespace presyn
