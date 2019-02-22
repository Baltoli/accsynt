#include <passes/passes.h>

#include <llvm/IR/Module.h>
#include <llvm/Pass.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

namespace {

bool should_rename(Instruction const& I)
{
  // Probaby rename if it doesn't have a name already
  if (!I.hasName()) {
    // Unless it's a void type (i.e. doesn't name a value)
    return !I.getType()->isVoidTy();
  }

  auto name = I.getName().str();
  return !std::isalpha(name[0]);
}

struct Namer : public FunctionPass {
  static char ID;
  Namer()
      : FunctionPass(ID)
  {
  }

  bool runOnFunction(Function& F) override;
};

bool Namer::runOnFunction(Function& F)
{
  int counter = 0;

  for (auto& BB : F) {
    for (auto& I : BB) {
      if (should_rename(I)) {
        I.setName("v" + std::to_string(counter++));
      }
    }
  }

  int argc = 0;
  for (auto& arg : F.args()) {
    if (!arg.hasName()) {
      arg.setName("arg" + std::to_string(argc++));
    }
  }

  return true;
}

char Namer::ID = 0;
static RegisterPass<Namer> X(
    "name", "Value naming pass for fiddling around", false, false);
}

std::unique_ptr<FunctionPass> createNamerPass()
{
  return std::unique_ptr<FunctionPass>{ new Namer{} };
}
