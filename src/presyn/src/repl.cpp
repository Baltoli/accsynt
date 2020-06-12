#include "candidate.h"
#include "fragment.h"
#include "rule_filler.h"
#include "sketch.h"

#include <props/props.h>

#include <support/llvm_format.h>

#include <fmt/format.h>

#include <readline/history.h>
#include <readline/readline.h>

#include <iostream>

using namespace presyn;

std::string get_line(std::string const& prompt)
{
  char* buf = readline(prompt.c_str());

  if (!buf) {
    return "";
  }

  auto str = std::string(buf);
  free(buf);

  if (str.size() > 0) {
    add_history(str.c_str());
  }

  return str;
}

int main()
{
  std::unique_ptr<fragment> current_frag = std::make_unique<hole>();

  auto sig_line = get_line(" sig> ");
  auto sig = props::signature::parse(sig_line);

  while (true) {
    auto line = get_line("frag> ");

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
