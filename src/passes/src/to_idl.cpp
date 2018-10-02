#include <passes/passes.h>

#include <llvm/Pass.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>

#include <optional>

using namespace llvm;

namespace {

bool is_add(Instruction const& inst)
{
  return inst.getOpcode() == Instruction::Add;
}

struct ConvertToIDL : public FunctionPass {
  static char ID;
  ConvertToIDL() : FunctionPass(ID) {}

  bool runOnFunction(Function& F) override;
};

bool ConvertToIDL::runOnFunction(Function& F)
{
  for(auto const& BB : F) {
    for(auto const& I : BB) {
    }
  }
  return false;
}

char ConvertToIDL::ID = 0;
static RegisterPass<ConvertToIDL> X("to-idl", "Convert a function to IDL constraints",
                                    false, false);

}

FunctionPass *createConvertToIDLPass()
{
  return new ConvertToIDL{};
}
