#include "opcode.h"
#include "translate.h"

#include <passes/passes.h>

#include <fmt/format.h>

#include <llvm/Pass.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>

#include <memory>
#include <optional>
#include <system_error>

using namespace llvm;

namespace {

struct ConvertToIDL : public FunctionPass {
  static char ID;
  ConvertToIDL(std::string out = "-") : 
    FunctionPass(ID), ec(), output(out, ec, sys::fs::F_RW)
  {
  }

  bool runOnFunction(Function& F) override;

  std::string header(std::string name) const;
  std::string footer() const;

private:
  std::error_code ec;
  raw_fd_ostream output;
};

bool ConvertToIDL::runOnFunction(Function& F)
{
  output << header(F.getName());

  auto constraints = std::vector<std::string>{};
  for(auto const& BB : F) {
    for(auto const& I : BB) {
      if(auto con = constraint(I)) {
        constraints.push_back(con.value());
      }
    }
  }

  for(auto it = constraints.begin();
      it != constraints.end();
      ++it)
  {
    output << " " << *it;
    if(std::next(it) != constraints.end()) {
      output << " and\n";
    }
  }

  output << footer() << '\n';
  return false;
}

std::string ConvertToIDL::header(std::string name) const
{
  name[0] = std::toupper(name[0]);
  return fmt::format("Constraint {}\n(\n", name);
}

std::string ConvertToIDL::footer() const
{
  return "\n)\nEnd";
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
