#include <passes/passes.h>

#include <fmt/format.h>

#include <llvm/Analysis/AssumptionCache.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/PassManager.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/Path.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Transforms/Utils/Mem2Reg.h>

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

void run_prepare_passes(Function& fn)
{
  auto pm = FunctionPassManager{};
  pm.addPass(PromotePass());

  auto fam = FunctionAnalysisManager{};
  auto pb = PassBuilder{};
  pb.registerFunctionAnalyses(fam);

  pm.run(*fn, fam);
}

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

  auto function = mod->getFunction(FunctionName);
  if(!function) {
    auto err_string = fmt::format("No such function: {}", FunctionName);
    auto fn_err = SMDiagnostic(sys::path::filename(InputFilename), 
                               SourceMgr::DK_Error, err_string);
    fn_err.print(argv[0], errs());
    return 2;
  }

  run_prepare_passes(*function);

  auto pass = std::unique_ptr<FunctionPass>{createConvertToIDLPass()};
  pass->runOnFunction(*function);
}
