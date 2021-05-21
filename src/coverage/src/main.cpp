#include "options.h"

#include <coverage/coverage.h>

#include <support/argument_generator.h>
#include <support/load_module.h>
#include <support/options.h>
#include <support/timeout.h>

#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

#include <fast-cpp-csv-parser/csv.h>

#include <fmt/format.h>

#include <chrono>

using namespace support;
using namespace llvm;

struct manifest_entry {
  std::string function;
  std::string group;
  std::string implementation;
};

std::vector<manifest_entry> read_manifest(std::string const& path)
{
  return {};
}

std::vector<manifest_entry> get_effective_input()
{
  if (FunctionName != "-" && ManifestPath == "-") {
    return {{FunctionName, "", FunctionName}};
  } else if (FunctionName == "-" && ManifestPath != "-") {
    return read_manifest(ManifestPath);
  } else {
    fmt::print(
        stderr,
        "Must specify exactly one of function name ({}) or manifest path "
        "({})\n",
        FunctionName, ManifestPath);
    std::exit(3);
  }
}

Function* get_single_function(Module& mod)
{
  Function* ret_func = nullptr;

  for (auto& func : mod) {
    if (!func.isDeclaration()) {
      if (ret_func == nullptr) {
        // If this is the only defined function we've seen so far, keep track
        ret_func = &func;
      } else {
        // If this and another function are both definitions, then there's no
        // unambiguous candidate.
        return nullptr;
      }
    }
  }

  return ret_func;
}

coverage::wrapper get_wrapper(Module& mod, std::string const& name)
{
  return coverage::wrapper(mod, name);
}

int main(int argc, char** argv)
try {
  using namespace fmt::literals;
  using namespace std::chrono_literals;

  hide_llvm_options();

  InitializeNativeTarget();
  LLVMInitializeNativeAsmPrinter();
  LLVMInitializeNativeAsmParser();

  cl::ParseCommandLineOptions(argc, argv);

  auto mod = load_or_parse_module(InputFile);
  if (!mod) {
    errs() << "Couldn't load or parse module: " << InputFile << '\n';
    return 1;
  }

  if (Header) {
    fmt::print("{},{},{},{}\n", "name", "inputs", "covered", "total");
  }

  auto gen = uniform_generator();

  for (auto [func, gr, impl] : get_effective_input()) {
    auto wrapper = get_wrapper(*mod, impl);

    for (auto i = 0; i < NumInputs; ++i) {
      auto build = wrapper.get_builder();
      gen.gen_args(build);

      wrapper.call(build);

      if (!Single || i == NumInputs - 1) {
        fmt::print(
            "{name},{iter},{cover},{total}\n", "name"_a = wrapper.name(),
            "iter"_a = i + 1, "cover"_a = wrapper.covered_conditions(),
            "total"_a = wrapper.total_conditions());
      }
    }
  }

} catch (std::runtime_error& e) {
  llvm::errs() << "Error creating coverage JIT wrapper:  ";
  llvm::errs() << e.what() << '\n';
  std::exit(2);
}
