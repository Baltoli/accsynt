#include <support/file.h>
#include <support/llvm_format.h>
#include <support/load_module.h>
#include <support/options.h>

#include <replacer/replace.h>

#include <nlohmann/json.hpp>

#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/TargetSelect.h>

#include <fstream>

using namespace idlr;
using namespace support;
using namespace llvm;

using json = ::nlohmann::json;

static cl::opt<std::string> SpecFile(
    cl::Positional, cl::desc("<spec file>"),
    cl::value_desc("File containing replacement specification"), cl::Required);

static cl::opt<std::string> Bitcode(
    cl::Positional, cl::desc("<bitcode file>"), cl::value_desc("Input bitcode"),
    cl::Required);

static cl::opt<std::string> OutputFilename(
    "o", cl::desc("Output filename"), cl::value_desc("filename"),
    cl::init("-"));

static cl::opt<bool> Textual(
    "S", cl::desc("Output module as textual IR instead of bitcode"),
    cl::init(false));

static cl::opt<bool> Force(
    "f", cl::desc("Force binary output to the terminal"), cl::init(false));

std::vector<spec> load_specs()
{
  auto ret = std::vector<spec> {};

  auto j = json {};
  auto in = std::ifstream(SpecFile);

  in >> j;

  for (auto& obj : j) {
    ret.emplace_back(obj);
  }

  return ret;
}

int main(int argc, char** argv)
{
  hide_llvm_options();

  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  InitializeNativeTargetAsmParser();

  cl::ParseCommandLineOptions(argc, argv);

  auto specs = load_specs();

  auto mod = load_or_parse_module(Bitcode);
  if (!mod) {
    errs() << "Couldn't load or parse module: " << Bitcode << '\n';
    return 1;
  }

  auto rep = replacer(*mod);

  for (auto const& s : specs) {
    rep.apply(s);
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
