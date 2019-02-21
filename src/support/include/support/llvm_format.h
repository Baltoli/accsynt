#pragma once

#include <fmt/format.h>

#include <llvm/Support/raw_ostream.h>

template <>
struct fmt::formatter<llvm::Value *> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(llvm::Value *v, FormatContext& ctx)
  {
    auto str = std::string{};
    auto os = llvm::raw_string_ostream(str);

    os << *v;
    return format_to(ctx.out(), str);
  }
};
