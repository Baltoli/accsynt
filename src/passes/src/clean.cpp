#include "passes.h"

#include <llvm/Pass.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Transforms/Utils/Cloning.h>

#include <algorithm>

using namespace llvm;

namespace {

struct Clean : public ModulePass {
  static char ID;
  Clean() : ModulePass(ID) {}

  bool runOnModule(Module &M) override;

  BasicBlock* errorBlock(Function &F) const;
  bool hasErrorParameter(Function const &F) const;

  void removeBlock(BasicBlock *BB) const;
  void cloneRetyped(Function &F) const;
};

bool Clean::runOnModule(Module &M)
{
  auto to_clean = std::vector<Function *>{};

  for(auto &F : M) {
    if(errorBlock(F) && hasErrorParameter(F)) {
      to_clean.push_back(&F);
    }
  }

  for(auto F : to_clean) {
    auto err_block = errorBlock(*F);
    removeBlock(err_block);
    cloneRetyped(*F);
  }

  return true;
}

BasicBlock* Clean::errorBlock(Function& F) const
{
  auto err_block_it = std::find_if(F.begin(), F.end(), [] (auto& BB) {
    return BB.getName() == "error";
  });

  if(err_block_it != F.end()) {
    return &(*err_block_it);
  } else {
    return nullptr;
  }
}

bool Clean::hasErrorParameter(Function const& F) const
{
  auto& ctx = F.getContext();
  auto i64_ty = llvm::IntegerType::get(ctx, 64);
  auto ptr_ty = llvm::PointerType::getUnqual(i64_ty);

  return F.arg_begin()->getType() == ptr_ty;
}

void Clean::removeBlock(BasicBlock *BB) const
{
  assert(BB && "Can't remove null basic block!");

  auto to_remove = std::map<BranchInst *, BasicBlock *>{};

  for(auto user : BB->users()) {
    if(auto branch = dyn_cast<BranchInst>(user)) {
      BasicBlock *other_dest = nullptr;
      for(auto i = 0u; i < branch->getNumSuccessors(); ++i) {
        auto succ = branch->getSuccessor(i);
        if(succ != BB) {
          other_dest = succ;
          break;
        }
      }

      to_remove.insert_or_assign(branch, other_dest);
    }
  }

  for(auto [branch, dest] : to_remove) {
    auto parent = branch->getParent();
    branch->eraseFromParent();
    BranchInst::Create(dest, parent);
  }
}

void Clean::cloneRetyped(Function &F) const
{
  auto name = F.getName();
  auto old_fn_ty = F.getFunctionType();

  auto arg = F.arg_begin();
  arg->replaceAllUsesWith(UndefValue::get(arg->getType()));

  auto actual_args = std::vector<Type *>{};
  std::copy(std::next(old_fn_ty->param_begin()), old_fn_ty->param_end(), 
            std::back_inserter(actual_args));
  auto fn_ty = FunctionType::get(old_fn_ty->getReturnType(), actual_args, false);

  auto func = Function::Create(fn_ty, F.getLinkage(), name, F.getParent());

  auto v_map = ValueToValueMapTy{};
  auto returns = SmallVector<ReturnInst*, 8>{};

  func->getBasicBlockList().splice(func->begin(), F.getBasicBlockList());

  for(auto I = std::next(F.arg_begin()), E = F.arg_end(), 
      I2 = func->arg_begin(); I != E; ++I, ++I2)
  {
    I->replaceAllUsesWith(&*I2);
    I2->takeName(&*I);
  }

  F.eraseFromParent();
  func->setName(name);
}

char Clean::ID = 0;
static RegisterPass<Clean> X("clean", "Accsynt cleaning pass",
                             false, false);

}

ModulePass *createCleanPass()
{
  return new Clean{};
}
