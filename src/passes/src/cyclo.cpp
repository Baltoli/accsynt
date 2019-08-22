#include <passes/passes.h>

#include <llvm/ADT/SCCIterator.h>
#include <llvm/IR/CFG.h>
#include <llvm/IR/Module.h>
#include <llvm/Pass.h>
#include <llvm/Support/raw_ostream.h>

#include <optional>

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

bool Cyclo::runOnFunction(Function& F)
{
  if (F.isDeclaration()) {
    return false;
  }

  outs() << F.getName() << ": ";

  auto ccs = 1; // true?
  auto nodes = 0;
  auto edges = 0;

  for (auto& bb : F) {
    ++nodes;

    for (auto it = succ_begin(&bb); it != succ_end(&bb); ++it) {
      ++edges;
    }
  }

  outs() << (edges - nodes + (2 * ccs)) << '\n';

  return false;
}

char Cyclo::ID = 0;
static RegisterPass<Cyclo> X(
    "cyclo", "Compute the cyclomatic complexity of a function", false, false);

} // namespace

std::unique_ptr<FunctionPass> createCycloPass()
{
  return std::unique_ptr<FunctionPass>(new Cyclo());
}
