#include <passes/passes.h>

#include <llvm/IR/Module.h>
#include <llvm/Pass.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

namespace {

struct Cyclo : public FunctionPass {
  static char ID;
  Cyclo()
      : FunctionPass(ID)
  {
  }

  bool runOnFunction(Function& F) override;
};

bool Cyclo::runOnFunction(Function& F) { return false; }

char Cyclo::ID = 0;
static RegisterPass<Cyclo> X(
    "cyclo", "Compute the cyclomatic complexity of a function", false, false);

} // namespace
