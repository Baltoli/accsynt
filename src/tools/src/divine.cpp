#include <support/llvm_format.h>
#include <support/options.h>

#include <fmt/format.h>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/SourceMgr.h>

using namespace support;
using namespace llvm;

static cl::opt<std::string> InputFilename(
    cl::Positional, cl::desc("<input bitcode file>"), cl::init("-"),
    cl::value_desc("filename"));

/*
 * The gist of what this tool needs to do is as follows:
 *
 * - Load in multiple bitcode files and a properties file
 * - For each of the modules loaded, rename and then clone the relevant function
 *   into a new module so that they're all in one place.
 * - Either hand-compile or link in testing runtime features (randomly generated
 *   inputs, calls to the divine svcomp features).
 *   - Possibly worth having a loop around this?
 * - Write everything out to a single bitcode file.
 */

int main(int argc, char** argv)
{
  hide_llvm_options();

  cl::ParseCommandLineOptions(argc, argv);
  LLVMContext Context;
  SMDiagnostic Err;

  auto&& mod = parseIRFile(InputFilename, Err, Context, true, "");
  if (!mod) {
    Err.print(argv[0], errs());
    return 1;
  }

  fmt::print("{}\n", *mod);
}
