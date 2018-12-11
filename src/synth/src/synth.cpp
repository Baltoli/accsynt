#include "call_wrapper.h"
#include "blas_synth.h"

#include <props/props.h>
#include <support/dynamic_library.h>
#include <support/thread_context.h>

#include <fmt/format.h>

#include <llvm/IR/Module.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/TargetSelect.h>

using namespace support;
using namespace synth;
using namespace llvm;

static cl::opt<std::string>
PropertiesPath(
    cl::Positional, cl::Required,
    cl::desc("<properties file>"));

static cl::opt<std::string>
LibraryPath(
    cl::Positional, cl::Required,
    cl::desc("<shared library>"));

static cl::opt<bool>
UseBLAS(
    "blas", cl::desc("Use old BLAS synthesiser implementation"),
    cl::init(false));

// In the future, specifications...

void report(Function *fn)
{
  if(fn) {
    outs() << *fn << '\n';
  } else {
    errs() << "No function found\n";
  }
}

int main(int argc, char **argv)
{
  InitializeNativeTarget();
  LLVMInitializeNativeAsmPrinter();
  LLVMInitializeNativeAsmParser();

  cl::ParseCommandLineOptions(argc, argv);

  auto property_set = props::property_set::load(PropertiesPath);
  auto fn_name = property_set.type_signature.name;

  auto lib = dynamic_library(LibraryPath);

  auto mod = Module("test_mod", thread_context::get());
  auto ref = call_wrapper(property_set.type_signature, mod, fn_name, lib);

  if(UseBLAS) {
    auto synth = blas_synth(property_set, ref);
    report(synth.generate());
  } else {
    report(nullptr);
  }
}
