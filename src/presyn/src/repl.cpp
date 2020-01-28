#include "candidate.h"
#include "fragment.h"
#include "sketch.h"

#include <props/props.h>

#include <support/llvm_format.h>

#include <fmt/format.h>

#include <iostream>

using namespace presyn;

int main()
{
  std::unique_ptr<fragment> current_frag = std::make_unique<hole>();

  for (std::string line; std::getline(std::cin, line);) {
    if (line == "compile") {
      break;
    }

    auto frag = fragment::parse(line);
    current_frag = current_frag->compose(std::move(frag));
  }

  std::string sig_line;
  std::getline(std::cin, sig_line);
  auto sig = props::signature::parse(sig_line);

  fmt::print("; frag = {}\n", *current_frag);
  fmt::print("; sig  = {}\n", sig);

  auto sk = sketch(sig, *current_frag);
  fmt::print("\n{}", sk.module());

  auto cand = std::move(sk).reify();
  if (cand.is_valid()) {
    fmt::print("Valid reified candidate - can proceed to execution\n");
  } else {
    fmt::print("Invalid candidate - no execution\n");
  }
}
