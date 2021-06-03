#include <passes/passes.h>

#include <support/file.h>

#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/raw_ostream.h>

#include <fmt/format.h>

using namespace support;
using namespace llvm;

static cl::opt<std::string> InputFilename(
    cl::Positional, cl::desc("<input bitcode file>"), cl::Required,
    cl::value_desc("filename"));

static cl::opt<std::string> OutputFilename(
    "o", cl::desc("Output filename"), cl::value_desc("filename"),
    cl::init("-"));

static cl::opt<bool> Textual(
    "S", cl::desc("Output module as textual IR instead of bitcode"),
    cl::init(false));

static cl::opt<bool> Force(
    "f", cl::desc("Force binary output to the terminal"), cl::init(false));

int main(int argc, char** argv)
{
  cl::ParseCommandLineOptions(argc, argv);

  LLVMContext Context;
  SMDiagnostic Err;

  auto mod = parseIRFile(InputFilename, Err, Context);
  if (!mod) {
    Err.print(argv[0], errs());
    return 1;
  }

  auto pass = createNamerPass();
  for (auto& func : *mod) {
    pass->runOnFunction(func);
  }

  to_file_or_default(OutputFilename, [&mod](auto&& os) {
    if (!Textual) {
      if (OutputFilename == "-" && !Force) {
        fmt::print(
            stderr, "Not outputting binary data to the terminal (use -f if"
                    "you really want to)\n");
        return;
      }

      WriteBitcodeToFile(*mod, os);
    } else {
      mod->print(os, nullptr);
    }
  });
}
