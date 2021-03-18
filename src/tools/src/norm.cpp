#include <support/file.h>
#include <support/thread_context.h>

#include <fmt/format.h>

#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Transforms/IPO/PassManagerBuilder.h>

using namespace support;
using namespace llvm;

static cl::opt<std::string> InputFilename(
    cl::Positional, cl::desc("<input bitcode file>"), cl::init("-"),
    cl::value_desc("filename"));

static cl::opt<std::string> OutputFilename(
    "o", cl::desc("Filename to save the generated constraints to"),
    cl::value_desc("filename"), cl::init("-"));

static cl::opt<bool> Textual(
    "S", cl::desc("Output module as textual IR instead of bitcode"),
    cl::init(false));

static cl::opt<bool> Force(
    "f", cl::desc("Force binary output to the terminal"), cl::init(false));

void run_norm_passes(Module& mod)
{
  auto pm = legacy::PassManager();

  auto pmb = PassManagerBuilder();
  pmb.OptLevel = 2;
  pmb.DisableUnrollLoops = true;
  pmb.LoopVectorize = false;
  pmb.SLPVectorize = false;
  pmb.populateModulePassManager(pm);

  pm.run(mod);
}

int main(int argc, char** argv)
{
  cl::ParseCommandLineOptions(argc, argv);

  auto& ctx = thread_context::get();
  auto err = SMDiagnostic {};

  auto&& mod = parseIRFile(InputFilename, err, ctx, true, "");
  if (!mod) {
    err.print(argv[0], errs());
    return 1;
  }

  run_norm_passes(*mod);

  to_file_or_default(OutputFilename, [&mod](auto&& os) {
    if (!Textual) {
      if (OutputFilename == "-" && !Force) {
        fmt::print(
            stderr, "Not outputting binary data to the terminal (use -f if "
                    "you really want to)\n");
        return;
      }

      WriteBitcodeToFile(*mod, os);
    } else {
      mod->print(os, nullptr);
    }
  });
}
