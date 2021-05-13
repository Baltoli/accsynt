#include "candidate.h"
#include "fragment.h"
#include "oracle_options.h"
#include "rule_filler.h"
#include "sketch.h"

#include <props/props.h>

#include <support/argument_generator.h>
#include <support/assert.h>
#include <support/call_builder.h>
#include <support/call_wrapper.h>
#include <support/dynamic_library.h>
#include <support/input.h>
#include <support/llvm_cloning.h>
#include <support/llvm_format.h>
#include <support/terminal.h>
#include <support/thread_context.h>

#include <llvm/IR/Module.h>
#include <llvm/Support/TargetSelect.h>

#include <fmt/format.h>

#include <fstream>

using namespace support;
using namespace presyn;

using namespace fmt::literals;
using namespace llvm;

namespace cl = llvm::cl;
namespace term = ::support::terminal;
namespace opts = presyn::oracle::opts;

// Read a line of input, either from a file or from standard input. If from
// stdin, then display a prompt as well.
std::string read_line(std::string const& prompt)
{
  if (opts::InputFilename == "-") {
    return get_line(prompt);
  } else {
    static auto file = std::ifstream();

    if (!file.is_open()) {
      file.open(opts::InputFilename);
    }

    auto line = std::string();
    std::getline(file, line);
    return line;
  }
}

props::signature get_sig()
{
  auto sig_line = read_line(" sig> ");

  try {
    return props::signature::parse(sig_line);
  } catch (std::runtime_error& e) {
    fmt::print(
        stderr, "{}Invalid signature:{} {}\n"_format(
                    term::f_red, term::reset, sig_line));
    std::exit(1);
  }
}

std::unique_ptr<fragment> get_fragment()
{
  std::unique_ptr<fragment> current_frag = std::make_unique<hole>();

  while (true) {
    auto line = read_line("frag> ");

    // Break out of the REPL if we get ^D or an empty input
    if (line.empty()) {
      break;
    }

    // ...or if we get garbage input.
    // could make this stricter if we like
    if (auto frag = fragment::parse(line)) {
      current_frag = current_frag->compose(std::move(frag));
    } else {
      fmt::print(
          stderr,
          "{}Invalid fragment:{} {}\n"_format(term::f_red, term::reset, line));
      std::exit(2);
    }
  }

  return current_frag;
}

bool test(call_wrapper& a, call_wrapper& b)
{
  auto gen = uniform_generator();

  for (auto i = 0; i < 64; ++i) {
    auto build = a.get_builder();

    gen.gen_args(build);

    auto a_bef = build;
    auto b_bef = build;

    auto a_res = a.call(build);
    auto b_res = b.call(build);

    if (a_res != b_res) {
      return false;
    }
  }

  return true;
}

int main(int argc, char** argv)
try {
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  InitializeNativeTargetAsmParser();

  cl::ParseCommandLineOptions(argc, argv);

  auto sig = get_sig();
  auto frag = get_fragment();

  auto lib = dynamic_library(opts::SharedLibrary);
  auto module = Module("oracle", thread_context::get());
  auto ref_impl = call_wrapper(sig, module, sig.name, lib);

  while (true) {
    auto cand = candidate(sketch(sig, *frag), std::make_unique<rule_filler>());
    assertion(cand.is_valid(), "Reification produced an invalid candidate");

    auto cand_impl = call_wrapper(cand.function());

    if (test(ref_impl, cand_impl)) {
      fmt::print("{}\n", cand.module());
      return 0;
    }
  }
} catch (std::runtime_error& e) {
  fmt::print(
      stderr,
      "{}Synthesis error:{} {}\n"_format(term::f_red, term::reset, e.what()));
  std::exit(2);
} catch (dyld_error& derr) {
  fmt::print(
      stderr, "{}\n  when loading dynamic library {}\n", derr.what(),
      opts::SharedLibrary);
  std::exit(3);
}
