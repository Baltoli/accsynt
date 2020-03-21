#include "options.h"

#include <coverage/coverage.h>

#include <support/argument_generator.h>
#include <support/load_module.h>

#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

#include <fmt/format.h>

using namespace llvm;

int main(int argc, char** argv)
try {
  InitializeNativeTarget();
  LLVMInitializeNativeAsmPrinter();
  LLVMInitializeNativeAsmParser();

  cl::ParseCommandLineOptions(argc, argv);

  auto mod = ::support::load_or_parse_module(InputFile);
  if (!mod) {
    errs() << "Couldn't load or parse module: " << InputFile << '\n';
    return 1;
  }

  auto wrapper = coverage::wrapper(*mod, FunctionName);

  for (auto i = 0; i < NumInputs; ++i) {
  }
} catch (std::runtime_error& e) {
  llvm::errs() << "Error creating coverage JIT wrapper:  ";
  llvm::errs() << e.what() << '\n';
  std::exit(2);
}
