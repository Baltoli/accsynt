#include "passes.h"

#include <llvm/Pass.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

namespace {

struct ConvertToIDL : public FunctionPass {
  static char ID;
  ConvertToIDL() : FunctionPass(ID) {}

  bool runOnFunction(Function& F) override;
};

bool ConvertToIDL::runOnFunction(Function& F)
{
  return false;
}

char ConvertToIDL::ID = 0;
static RegisterPass<ConvertToIDL> X("to_idl", "Convert a function to IDL constraints",
                                    false, false);

}

FunctionPass *createConvertToIDLPass()
{
  return new ConvertToIDL{};
}
