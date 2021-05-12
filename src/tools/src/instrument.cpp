#include "print_opcode.h"

#include <support/file.h>
#include <support/thread_context.h>

#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/CommandLine.h>

#include <fmt/format.h>

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

static cl::opt<std::string>
    Tag("tag", cl::desc("Override function names as row tags"), cl::init(""));

void instrument(Module& mod)
{
  auto p = PromoteVisitor();
  p.visit(mod);
  p.promote();

  auto v = Tag.empty() ? PrintOpcodeVisitor() : PrintOpcodeVisitor(Tag);
  v.visit(mod);
}

int main(int argc, char** argv)
{
  cl::ParseCommandLineOptions(argc, argv);

  auto& ctx = thread_context::get();
  auto err = SMDiagnostic {};

  auto&& mod = parseIRFile(InputFilename, err, ctx);
  if (!mod) {
    err.print(argv[0], errs());
    return 1;
  }

  instrument(*mod);

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
