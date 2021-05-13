#include "candidate.h"
#include "fragment.h"
#include "rule_filler.h"
#include "sketch.h"

#include <props/props.h>

#include <support/input.h>
#include <support/llvm_format.h>

#include <fmt/format.h>

using namespace presyn;

int main()
{
  std::unique_ptr<fragment> current_frag = std::make_unique<hole>();

  auto sig_line = support::get_line(" sig> ");
  auto sig = props::signature::parse(sig_line);

  while (true) {
    auto line = support::get_line("frag> ");

    // Break out of the REPL if we get ^D or an empty input
    if (line.empty()) {
      break;
    }

    // ...or if we get garbage input.
    // could make this stricter if we like
    if (auto frag = fragment::parse(line)) {
      current_frag = current_frag->compose(std::move(frag));
    } else {
      break;
    }
  }

  fmt::print("; frag = {}\n", *current_frag);
  fmt::print("; sig  = {}\n", sig);

  auto sk = sketch(sig, *current_frag);

  auto cand = candidate(std::move(sk), std::make_unique<rule_filler>());
  if (cand.is_valid()) {
    fmt::print("; Valid reified candidate - can proceed to execution\n");
  } else {
    fmt::print("; Invalid candidate - no execution\n");
  }

  fmt::print("\n{}", cand.module());
}
