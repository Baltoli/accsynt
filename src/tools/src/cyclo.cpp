#include <passes/passes.h>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

static cl::opt<std::string> InputFilename(
    cl::Positional, cl::desc("<input bitcode file>"), cl::init("-"),
    cl::value_desc("filename"));

int main(int argc, char** argv)
{
  cl::ParseCommandLineOptions(argc, argv);

  LLVMContext Context;
  SMDiagnostic Err;

  auto&& mod = parseIRFile(InputFilename, Err, Context);
  if (!mod) {
    Err.print(argv[0], errs());
    return 1;
  }

  auto pass = createCycloPass();

  for (auto& fn : *mod) {
    pass->runOnFunction(fn);
  }
}
