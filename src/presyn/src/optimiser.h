#pragma once

#include <holes/holes.h>

#include <support/assert.h>
#include <support/call_wrapper.h>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

#include <unordered_map>

namespace presyn {

class optimiser {
public:
  optimiser(holes::provider&&);

  void run(llvm::Function*, support::call_wrapper& wrap);

private:
  template <typename Value>
  llvm::Instruction* get_constant(Value, llvm::Type*);

  void rauw_nt_proxy(llvm::Instruction* before, llvm::Instruction* after);

  holes::provider provider_;

  std::unordered_map<llvm::Instruction*, std::unordered_set<llvm::Instruction*>>
      live_values_;

  std::unordered_map<llvm::Type*, llvm::Function*> constants_;
};

template <typename Value>
llvm::Instruction* optimiser::get_constant(Value v, llvm::Type* ty)
{
  if (auto int_ty = llvm::dyn_cast<llvm::IntegerType>(ty)) {
    if (constants_.find(int_ty) == constants_.end()) {
      auto fn_ty
          = llvm::FunctionType::get(int_ty, {int_ty, int_ty, int_ty}, false);

      auto cst_fn = llvm::Function::Create(
          fn_ty, llvm::GlobalValue::InternalLinkage, "const",
          &provider_.module());

      auto bb = llvm::BasicBlock::Create(cst_fn->getContext(), "", cst_fn);

      llvm::ReturnInst::Create(bb->getContext(), cst_fn->getArg(2), bb);

      constants_[ty] = cst_fn;
    }

    auto fn = constants_.at(ty);
    auto undef = llvm::UndefValue::get(ty);
    return llvm::CallInst::Create(
        fn, {undef, undef, llvm::ConstantInt::get(int_ty, v)});
  } else {
    unimplemented();
  }
}

} // namespace presyn
