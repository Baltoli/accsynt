#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

#include <llvm/IR/Module.h>
#include <llvm/Support/TargetSelect.h>

using namespace llvm;

int main(int argc, char* argv[])
{
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  InitializeNativeTargetAsmParser();

  int result = Catch::Session().run(argc, argv);
  return result;
}
