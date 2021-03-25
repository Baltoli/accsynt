#include <props/props.h>

#include <support/argument_generator.h>
#include <support/call_builder.h>
#include <support/call_wrapper.h>
#include <support/dynamic_library.h>
#include <support/options.h>
#include <support/terminal.h>
#include <support/thread_context.h>

#include <fmt/format.h>

#include <llvm/IR/Module.h>
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/TargetSelect.h>

using namespace support;
using namespace llvm;

static cl::opt<std::string>
    LibraryPath(cl::Positional, cl::desc("<shared library>"), cl::Required);

static cl::list<std::string>
    PropertyPaths(cl::Positional, cl::desc("[props...]"), cl::ZeroOrMore);

void success(std::string const& name)
{
  fmt::print(
      "[{}OK{}] {}\n", terminal::f_green + terminal::bold, terminal::reset,
      name);
}

void fail(std::string const& name, std::string const& reason)
{
  fmt::print(
      "[{}FAIL{}] {}: {}\n", terminal::f_red + terminal::bold, terminal::reset,
      name, reason);
}

int main(int argc, char** argv)
try {
  InitializeNativeTarget();
  LLVMInitializeNativeAsmPrinter();
  LLVMInitializeNativeAsmParser();

  hide_llvm_options();
  cl::ParseCommandLineOptions(argc, argv);

  auto lib = dynamic_library(LibraryPath);

  auto& ctx = thread_context::get();
  auto mod = Module("sanity-check", ctx);

  for (auto const& path : PropertyPaths) {
    try {
      auto ps = props::property_set::load(path);
      auto name = ps.type_signature.name;

      if (!lib.raw_symbol(name)) {
        fail(name, "no such symbol in dynamic library");
        continue;
      }

      auto ref = call_wrapper(ps.type_signature, mod, name, lib);
      auto gen = uniform_generator();

      auto b = ref.get_builder();
      gen.gen_args(b);

      ref.call(b);

      success(name);
    } catch (props::parse_error& perr) {
      fmt::print(
          stderr, "{}\n  (when parsing property set: {})\n", perr.what(), path);
      return 2;
    }
  }
} catch (dyld_error& derr) {
  fmt::print(
      stderr, "{}\n  (when loading dynamic library: {})\n", derr.what(),
      LibraryPath);
  return 3;
}
