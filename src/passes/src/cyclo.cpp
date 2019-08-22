#include <passes/passes.h>

#include <llvm/IR/Module.h>
#include <llvm/Pass.h>
#include <llvm/Support/raw_ostream.h>

#include <optional>

using namespace llvm;

namespace {

class Cyclo : public FunctionPass {
public:
  static char ID;
  Cyclo()
      : FunctionPass(ID)
      , run_(false)
      , complexity_(0)
  {
  }

  bool runOnFunction(Function& F) override;

  std::optional<size_t> complexity() const;

private:
  bool run_;
  size_t complexity_;
};

std::optional<size_t> Cyclo::complexity() const
{
  if (run_) {
    return complexity_;
  } else {
    return std::nullopt;
  }
}

bool Cyclo::runOnFunction(Function& F) { return false; }

char Cyclo::ID = 0;
static RegisterPass<Cyclo> X(
    "cyclo", "Compute the cyclomatic complexity of a function", false, false);

} // namespace

std::unique_ptr<FunctionPass> createCycloPass()
{
  return std::unique_ptr<FunctionPass>(new Cyclo());
}
