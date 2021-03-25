#include <props/props.h>

#include <support/assert.h>
#include <support/call_wrapper.h>
#include <support/dynamic_library.h>
#include <support/options.h>
#include <support/thread_context.h>

#include <fmt/format.h>

#include <llvm/Support/CommandLine.h>
#include <llvm/Support/TargetSelect.h>

using namespace support;
using namespace llvm;

static cl::opt<std::string>
    LibraryPath(cl::Positional, cl::desc("<shared library>"), cl::Required);

static cl::list<std::string>
    PropertyPaths(cl::Positional, cl::desc("[props...]"), cl::ZeroOrMore);

int main(int argc, char** argv)
try {
  InitializeNativeTarget();

  hide_llvm_options();
  cl::ParseCommandLineOptions(argc, argv);

  auto lib = dynamic_library(LibraryPath);

  auto& ctx = thread_context::get();

  for (auto const& path : PropertyPaths) {
    try {
      auto ps = props::property_set::load(path);
    } catch (props::parse_error& perr) {
      unimplemented();
    }
  }
} catch (dyld_error& derr) {
  fmt::print(
      stderr, "{}\n  (when loading dynamic library: {})\n", derr.what(),
      LibraryPath);
  return 3;
}
