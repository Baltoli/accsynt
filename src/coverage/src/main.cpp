#include "options.h"

#include <coverage/coverage.h>

#include <support/load_module.h>

#include <llvm/Support/raw_ostream.h>

using namespace llvm;

int main(int argc, char** argv)
{
  cl::ParseCommandLineOptions(argc, argv);

  auto mod = ::support::load_or_parse_module(InputFile);
  if (!mod) {
    errs() << "Couldn't load or parse module: " << InputFile << '\n';
    return 1;
  }

  auto func = mod->getFunction(FunctionName);
  if (!func) {
    errs() << "Error looking up function " << FunctionName << " in module\n";
    return 2;
  }
}
