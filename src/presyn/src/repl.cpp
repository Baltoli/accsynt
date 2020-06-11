#include "candidate.h"
#include "fragment.h"
#include "sketch.h"

#include <props/props.h>

#include <support/llvm_format.h>

#include <fmt/format.h>

#include <readline/readline.h>

#include <iostream>

using namespace presyn;

int main()
{
  std::unique_ptr<fragment> current_frag = std::make_unique<hole>();

  std::string line;

  fmt::print(" sig> ");
  std::getline(std::cin, line);
  auto sig = props::signature::parse(line);

  while (true) {
    fmt::print("frag> ");

    // Break out of the REPL if we get ^D
    if (!std::getline(std::cin, line)) {
      fmt::print("\n");
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

  auto cand = candidate(std::move(sk));
  if (cand.is_valid()) {
    fmt::print("; Valid reified candidate - can proceed to execution\n");
  } else {
    fmt::print("; Invalid candidate - no execution\n");
  }

  fmt::print("\n{}", cand.module());
}
