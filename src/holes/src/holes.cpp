#include <holes/holes.h>

#include <support/thread_context.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>

using namespace llvm;

namespace holes {

provider::provider(LLVMContext& ctx, Module& mod)
    : ctx_(ctx)
    , mod_(mod)
    , hole_type_(StructType::create(ctx_, "hole"))
    , identities_ {}
{
}

Type* provider::hole_type() const { return hole_type_; }

Instruction* provider::create_hole()
{
  auto ud_val = UndefValue::get(hole_type());
  auto id = get_identity(hole_type());
  return CallInst::Create(id, {ud_val}, "hole");
}

Function* provider::get_identity(Type* ty)
{
  if (identities_.find(ty) == identities_.end()) {
    auto ft = FunctionType::get(ty, {ty}, false);
    auto func = Function::Create(ft, GlobalValue::InternalLinkage, "id", &mod_);
    auto arg = func->getArg(0);
    auto bb = BasicBlock::Create(ctx_, "entry", func);
    ReturnInst::Create(ctx_, arg, bb);

    identities_[ty] = func;
  }

  return identities_.at(ty);
}

} // namespace holes
