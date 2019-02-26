#include "translate.h"

#include <passes/passes.h>

#include <fmt/color.h>
#include <fmt/format.h>

#include <llvm/IR/Function.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Module.h>
#include <llvm/Pass.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>

#include <memory>
#include <optional>
#include <system_error>

using namespace llvm;

namespace {

struct ConvertToIDL : public FunctionPass {
  static char ID;
  ConvertToIDL(std::string out = "-")
      : FunctionPass(ID)
      , output_path(out)
  {
  }

  bool runOnFunction(Function& F) override;

private:
  std::string output_path;
};

bool ConvertToIDL::runOnFunction(Function& F)
{
  using namespace fmt::literals;

  if (auto result = convert::to_idl(F)) {
    std::error_code ec;
    raw_fd_ostream output{ output_path, ec, sys::fs::F_Text };
    output << result.value() << '\n';
  } else {
    auto bold_red = "\u001b[1m\u001b[31m";
    auto reset = "\u001b[0m";

    fmt::print(stderr,
        "{color}Error:{reset} converting function '{name}' to IDL\n",
        "color"_a = bold_red, "reset"_a = reset, "name"_a = F.getName().str());
  }

  return false;
}

char ConvertToIDL::ID = 0;
static RegisterPass<ConvertToIDL> X(
    "to-idl", "Convert a function to IDL constraints", false, false);
}

std::unique_ptr<FunctionPass> createConvertToIDLPass()
{
  return std::unique_ptr<FunctionPass>{ new ConvertToIDL{} };
}

std::unique_ptr<FunctionPass> createConvertToIDLPass(std::string file)
{
  return std::unique_ptr<FunctionPass>{ new ConvertToIDL{ file } };
}
