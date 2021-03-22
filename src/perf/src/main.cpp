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

template <typename F>
auto timed(F&& func)
{
  auto clk = std::chrono::steady_clock {};

  auto start = clk.now();
  auto ret = std::forward<F>(func)();
  auto end = clk.now();

  return std::pair {end - start, ret};
}

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

  auto gen = override_generator(Parameter, 0LL, MemSize);

  fmt::print("param,value,time\n");

  for (int val = Start; val < End; val += Step) {
    gen.set_value(val);

    for (auto i = 0; i < Reps; ++i) {
      auto b = ref.get_builder();
      gen.gen_args(b);

      auto [res, t] = ref.call_timed(b);
      fmt::print("{},{},{}\n", Parameter, val, t.count());
    }
  }

} catch (props::parse_error& perr) {
  fmt::print(
      stderr, "{}\n  when parsing property set {}\n", perr.what(),
      PropertiesPath);
  return 2;
} catch (dyld_error& derr) {
  fmt::print(
      stderr, "{}\n  when loading dynamic library {}\n", derr.what(),
      LibraryPath);
  return 3;
}
