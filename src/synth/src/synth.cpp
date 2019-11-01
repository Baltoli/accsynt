#include "blas_synth.h"
#include "hill_synth.h"
#include "rule_synth.h"
#include "synth_options.h"

#include <props/props.h>

#include <support/call_wrapper.h>
#include <support/dynamic_library.h>
#include <support/file.h>
#include <support/thread_context.h>

#include <fmt/format.h>

#include <llvm/IR/Module.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/TargetSelect.h>

using namespace support;
using namespace synth;
using namespace llvm;

static cl::opt<std::string> PropertiesPath(
    cl::Positional, cl::Required, cl::desc("<properties file>"));

static cl::opt<std::string> LibraryPath(
    cl::Positional, cl::Required, cl::desc("<shared library>"));

static cl::opt<std::string> OutputPath("output",
    cl::desc("Specify output filename"), cl::value_desc("filename"),
    cl::init("-"));

static cl::alias OutputPathA(
    "o", cl::desc("Alias for -output"), cl::aliasopt(OutputPath));

static cl::opt<bool> PrintAttempts("attempts",
    cl::desc("Print the number of attempts to stdout"), cl::init(false));

static cl::opt<bool> UseBLAS("blas",
    cl::desc("Use old BLAS synthesiser implementation"), cl::init(false));

static cl::opt<bool> HillClimb("climb",
    cl::desc("Use the new hill-climbing synthesis implementation"),
    cl::init(false));

// In the future, specifications...

void report(generate_result result)
{
  to_file_or_default(OutputPath, [result](auto& os) {
    if (result.function) {
      os << *result.function->getParent();

      if (PrintAttempts) {
        outs() << result.attempts << '\n';
      }
    } else {
      os << "No function found\n";
    }
  });
}

int main(int argc, char** argv) try {
  if (UseBLAS && HillClimb) {
    // TODO: make these into an enum to choose the implementation
    errs() << "Cannot use both BLAS and hill climber implementations\n";
    return 1;
  }

  InitializeNativeTarget();
  LLVMInitializeNativeAsmPrinter();
  LLVMInitializeNativeAsmParser();

  cl::ParseCommandLineOptions(argc, argv);

  auto property_set = props::property_set::load(PropertiesPath);
  auto fn_name = property_set.type_signature.name;

  auto lib = dynamic_library(LibraryPath);

  auto mod = Module("test_mod", thread_context::get());

  auto ref = call_wrapper(property_set.type_signature, mod, fn_name, lib);

  if (!DryRun) {
    if (UseBLAS) {
      auto synth = blas_synth(property_set, ref);
      report(synth.generate());
    } else if (HillClimb) {
      auto synth = hill_synth(property_set, ref);
      report(synth.generate());
    } else {
      auto synth = rule_synth(property_set, ref);
      report(synth.generate());
    }
  }
} catch (props::parse_error& perr) {
  errs() << perr.what() << '\n';
  errs() << "  when parsing property set " << PropertiesPath << '\n';
  return 2;
} catch (dyld_error& derr) {
  errs() << derr.what() << '\n';
  errs() << "  when loading dynamic library " << LibraryPath << '\n';
  return 3;
}
