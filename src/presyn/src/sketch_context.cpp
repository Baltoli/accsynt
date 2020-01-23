#include "sketch_context.h"

#include "stub.h"

#include <support/assert.h>
#include <support/thread_context.h>

#include <llvm/IR/Constants.h>
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
    auto func_type = FunctionType::get(ty, true);
    auto func = Function::Create(
        func_type, GlobalValue::InternalLinkage, "stub", module_);

    stubs_[ty] = func;
  }

  return stubs_[ty];
}

llvm::Function* sketch_context::stub(std::string const& name)
{
  auto const_name = constant_name(name);
  auto func = stub();
}

llvm::Constant* sketch_context::constant_name(std::string const& name)
{
  if (names_.find(name) == names_.end()) {
    auto char_ty = IntegerType::get(module_.getContext(), 8);
    auto name_chars = std::vector<llvm::Constant*>();

    for (auto c : name) {
      name_chars.push_back(ConstantInt::get(char_ty, c, false));
    }

    auto array_type = ArrayType::get(char_ty, name_chars.size());
    names_[name] = ConstantArray::get(array_type, name_chars);
  }

  return names_[name];
}

} // namespace presyn
