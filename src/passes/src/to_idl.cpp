#include <passes/passes.h>

#include <llvm/Pass.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>

#include <memory>
#include <optional>
#include <system_error>

using namespace llvm;

namespace {

bool is_add(Instruction const& inst)
{
  return inst.getOpcode() == Instruction::Add;
}

struct ConvertToIDL : public FunctionPass {
  static char ID;
  ConvertToIDL(std::string out = "-") : 
    FunctionPass(ID), ec(), output(out, ec)
  {
  }

  bool runOnFunction(Function& F) override;

private:
  std::error_code ec;
  raw_fd_ostream output;
};

bool ConvertToIDL::runOnFunction(Function& F)
{
  for(auto const& BB : F) {
    for(auto const& I : BB) {
      output << I << '\n';
    }
  }
  return false;
}

char ConvertToIDL::ID = 0;
static RegisterPass<ConvertToIDL> X("to-idl", "Convert a function to IDL constraints",
                                    false, false);

}

std::unique_ptr<FunctionPass> createConvertToIDLPass()
{
  return std::unique_ptr<FunctionPass>{new ConvertToIDL{}};
}

std::unique_ptr<FunctionPass> createConvertToIDLPass(std::string file)
{
  return std::unique_ptr<FunctionPass>{new ConvertToIDL{file}};
}
