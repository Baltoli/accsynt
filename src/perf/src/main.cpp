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

#include <algorithm>
#include <chrono>
#include <string_view>
#include <type_traits>

using namespace support;
using namespace llvm;
using namespace props;

void warmup(call_wrapper& ref)
{
  auto gen = uniform_generator();
  auto b = ref.get_builder();

  gen.gen_args(b);

  ref.call(b);
}

void run_fixed(
    std::vector<std::string> params, call_wrapper& ref, std::string_view tag)
{
  warmup(ref);

  fmt::print("param,value,time,tag\n");

  for (auto i = 0u; i < params.size(); ++i) {
    auto gen
        = override_generator(std::unordered_map<std::string, long> {}, MemSize);

    for (auto i = 1u; i < params.size(); ++i) {
      gen.set_value(params[i], Independent);
    }

    for (int val = Start; val < End; val += Step) {
      gen.set_value(params[0], val);

      for (auto i = 0; i < Reps; ++i) {
        auto b = ref.get_builder();
        gen.gen_args(b);

        auto [res, t] = ref.call_timed(b);
        fmt::print("{},{},{},{}\n", params[0], val, t.count(), tag);
      }
    }

    std::rotate(params.begin(), params.begin() + 1, params.end());
  }
}

void run_random(
    std::vector<std::string> params, call_wrapper& ref, std::string_view tag)
{
  warmup(ref);

  auto gen_base = uniform_generator(128);
  gen_base.int_min = Min;
  gen_base.int_max = Max;
  gen_base.float_min = float(Min);
  gen_base.float_max = float(Max);

  fmt::print("param,value,time,tag\n");

  for (auto const& param : params) {
    for (int val = 0; val < Values; ++val) {
      auto b = ref.get_builder();
      gen_base.gen_args(b);

      for (auto i = 0; i < Reps; ++i) {
        auto clone = b;

        auto [res, t] = ref.call_timed(clone);
        auto used_arg = clone.get<int64_t>(param);

        fmt::print("{},{},{},{}\n", param, used_arg, t.count(), tag);
      }
    }
  }
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

  auto params = [&]() -> std::vector<std::string> {
    if (Parameters.empty()) {
      auto ret = std::vector<std::string> {};
      sig_visitor {on(base_type::integer, [&](auto const& p) {
        ret.push_back(p.name);
      })}.visit(property_set.type_signature);
      return ret;
    } else {
      return Parameters;
    }
  }();

  auto tag = [&]() -> std::string {
    if (Tag.empty()) {
      return property_set.type_signature.name;
    } else {
      return Tag;
    }
  }();

  auto lib = dynamic_library(LibraryPath);
  auto disable_trace = lib.symbol<void()>("disable_trace");
  disable_trace();

  auto mod = Module("perf_internal", thread_context::get());
  auto ref = call_wrapper(property_set.type_signature, mod, fn_name, lib);

  switch (Mode) {
  case LinearSpace:
    run_fixed(params, ref, tag);
    return 0;
  case Random:
    run_random(params, ref, tag);
    return 0;
  default:
    unimplemented();
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
