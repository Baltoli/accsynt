#include <passes/passes.h>

#include <llvm/IR/Module.h>
#include <llvm/Pass.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

namespace {

struct FixFloats : public FunctionPass {
  static char ID;

  FixFloats()
      : FunctionPass(ID)
  {
  }

  bool runOnFunction(Function& f) override;
};

bool FixFloats::runOnFunction(Function& f)
{
  return false;
}

char FixFloats::ID = 0;
static RegisterPass<FixFloats> X(
    "fix-floats", "Do some unsafe floating point optimisations", false, false);
}
