#include <support/llvm_format.h>
#include <support/load_module.h>
#include <support/options.h>

#include <replacer/replace.h>

#include <nlohmann/json.hpp>

#include <llvm/Support/CommandLine.h>
#include <llvm/Support/TargetSelect.h>

#include <fstream>

using namespace idlr;
using namespace support;
using namespace llvm;

using json = ::nlohmann::json;

cl::opt<std::string> SpecFile(
    cl::Positional, cl::desc("<spec file>"),
    cl::value_desc("File containing replacement specification"), cl::Required);

cl::opt<std::string> Bitcode(
    cl::Positional, cl::desc("<bitcode file>"), cl::value_desc("Input bitcode"),
    cl::Required);

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
  for (auto s : specs) {
    fmt::print("{}\n", s);
  }

  auto mod = load_or_parse_module(Bitcode);
  if (!mod) {
    errs() << "Couldn't load or parse module: " << Bitcode << '\n';
    return 1;
  }

  auto rep = replacer(*mod);

  for (auto const& s : specs) {
    rep.apply(s);
  }

  fmt::print("{}\n", *mod);
}
