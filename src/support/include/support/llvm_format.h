#pragma once

#include <support/string.h>

#include <fmt/format.h>

#include <llvm/IR/Value.h>
#include <llvm/Support/raw_ostream.h>

#include <type_traits>
#include <variant>

template <>
struct fmt::formatter<llvm::Module> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(llvm::Module const& v, FormatContext& ctx)
  {
    auto str = std::string {};
    auto os = llvm::raw_string_ostream(str);

    os << v;
    return format_to(ctx.out(), "{}", ::support::left_trim(str));
  }
};

template <>
struct fmt::formatter<llvm::Value> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(llvm::Value const& v, FormatContext& ctx)
  {
    auto str = std::string {};
    auto os = llvm::raw_string_ostream(str);

    os << v;
    return format_to(ctx.out(), "{}", ::support::left_trim(str));
  }
};
