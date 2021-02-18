#include "options.h"

#include <props/props.h>

#include <support/argument_generator.h>
#include <support/bit_cast.h>
#include <support/call_wrapper.h>
#include <support/dynamic_library.h>
#include <support/llvm_format.h>
#include <support/options.h>
#include <support/thread_context.h>

#include <fmt/format.h>

#include <llvm/IR/Module.h>
#include <llvm/Support/CommandLine.h>

#include <chrono>
#include <type_traits>

using namespace support;
using namespace llvm;

void dump_pre(call_builder const& build)
{
  build.visit_args(
      [](auto&& sv) { fmt::print("{}\n", sv); },
      [](auto&& vv) { fmt::print("{}\n", fmt::join(vv, ",")); });
}

void dump_post(call_builder const& build)
{
  build.visit_pointer_args(
      [](auto&& vv) { fmt::print("{}\n", fmt::join(vv, ",")); });
}

void dump_rv(uint64_t rv) { fmt::print("{}\n", rv); }

int main(int argc, char** argv)
try {
  LLVMInitializeNativeTarget();
  LLVMInitializeNativeAsmPrinter();
  LLVMInitializeNativeAsmParser();

  hide_llvm_options();
  cl::ParseCommandLineOptions(argc, argv);

  auto property_set = props::property_set::load(PropertiesPath);
  auto fn_name = property_set.type_signature.name;

  auto lib = dynamic_library(LibraryPath);

  auto mod = Module("perf_internal", thread_context::get());
  auto ref = call_wrapper(property_set.type_signature, mod, fn_name, lib);

  auto gen = uniform_generator(MemSize);

  auto build = ref.get_builder();

  fmt::print("{}\n", build.signature());

  gen.gen_args(build);
  dump_pre(build);

  auto rv = ref.call(build);
  dump_post(build);

  dump_rv(rv);

} catch (props::parse_error& perr) {
  errs() << perr.what() << '\n';
  errs() << "  when parsing property set " << PropertiesPath << '\n';
  return 2;
} catch (dyld_error& derr) {
  errs() << derr.what() << '\n';
  errs() << "  when loading dynamic library " << LibraryPath << '\n';
  return 3;
}
