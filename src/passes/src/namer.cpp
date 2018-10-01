#include <llvm/Pass.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

namespace {

struct Namer : public ModulePass {
  static char ID;
  Namer() : ModulePass(ID) {}

  bool runOnModule(Module &M) override;
};

bool Namer::runOnModule(Module &M)
{
  int counter = 0;

  for(auto& F : M) {
    for(auto& BB : F) {
      for(auto& I : BB) {
        if(!I.hasName() && !I.getType()->isVoidTy()) {
          I.setName("v" + std::to_string(counter++));
        }
      }
    }

    int argc = 0;
    for(auto& arg : F.args()) {
      arg.setName("arg" + std::to_string(argc++));
    }
  }

  return true;
}

char Namer::ID = 0;
static RegisterPass<Namer> X("name", "Value naming pass for fiddling around",
                             false, false);

}

ModulePass *createNamerPass()
{
  return new Namer{};
}
