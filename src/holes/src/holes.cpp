#include <holes/holes.h>

#include <support/thread_context.h>

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>

#include <unordered_map>

using namespace llvm;

namespace holes {

provider::provider(Module& mod, LLVMContext& ctx)
    : mod_(mod)
    , ctx_(ctx)
    , hole_type_(StructType::create(ctx_, "hole"))
{
}

Type* provider::hole_type() const { return hole_type_; }

Instruction* provider::create_hole() const
{
  return nullptr;
  ;
}

} // namespace holes
