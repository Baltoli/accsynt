#include "candidate.h"
#include "fragment.h"
#include "oracle_options.h"
#include "rule_filler.h"
#include "sketch.h"

#include <props/props.h>

#include <support/assert.h>
#include <support/input.h>
#include <support/llvm_format.h>
#include <support/terminal.h>

#include <fmt/format.h>

#include <fstream>

using namespace support;
using namespace presyn;

using namespace fmt::literals;

namespace cl = llvm::cl;
namespace term = support::terminal;
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

int main(int argc, char** argv)
try {
  cl::ParseCommandLineOptions(argc, argv);

  auto sig = get_sig();
  auto frag = get_fragment();

  fmt::print("; frag = {}\n", *frag);
  fmt::print("; sig  = {}\n", sig);

  auto cand = candidate(sketch(sig, *frag), std::make_unique<rule_filler>());

  if (cand.is_valid()) {
    fmt::print("; Valid reified candidate - can proceed to execution\n");
  } else {
    fmt::print("; Invalid candidate - no execution\n");
  }

  fmt::print("\n{}", cand.module());
} catch (std::runtime_error& e) {
  fmt::print(
      stderr,
      "{}Synthesis error:{} {}\n"_format(term::f_red, term::reset, e.what()));
  std::exit(3);
}
