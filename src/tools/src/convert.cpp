#include <passes/passes.h>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/SourceMgr.h>

using namespace llvm;

static cl::opt<std::string>
FunctionName(cl::Positional, cl::desc("<function to convert to IDL>"),
    cl::value_desc("function name"));

static cl::opt<std::string>
InputFilename(cl::Positional, cl::desc("<input bitcode file>"),
    cl::init("-"), cl::value_desc("filename"));

static cl::opt<std::string>
OutputFilename("o",
    cl::desc("Filename to save the generated constraints to"),
    cl::value_desc("filename"),
    cl::init("-"));

int main(int argc, char **argv)
{
  cl::ParseCommandLineOptions(argc, argv);
  LLVMContext Context;
  SMDiagnostic Err;

  auto&& mod = parseIRFile(InputFilename, Err, Context, true, "");
  if(!mod) {
    Err.print(argv[0], errs());
    return 1;
  }

  if(OutputFilename == "-") {
    OutputFilename = FunctionName + ".idl";
  }
}
