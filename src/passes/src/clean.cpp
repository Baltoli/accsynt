#include <llvm/Pass.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>

#include <algorithm>

using namespace llvm;

namespace {

struct Clean : public ModulePass {
  static char ID;
  Clean() : ModulePass(ID) {}

  BasicBlock* errorBlock(Function &F) const;
  bool hasErrorParameter(Function const &F) const;

  bool runOnModule(Module &M) override;
};

bool Clean::runOnModule(Module &M)
{
  for(auto &F : M) {
    auto err_block = errorBlock(F);

    if(err_block && hasErrorParameter(F)) {
      llvm::errs() << F.getName() << " to be cleaned!\n";
    }
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

char Clean::ID = 0;
static RegisterPass<Clean> X("clean", "Accsynt cleaning pass",
                             false, false);

}
