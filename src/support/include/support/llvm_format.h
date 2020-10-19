#pragma once

#include <support/string.h>

#include <fmt/format.h>

#include <llvm/ADT/StringRef.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/raw_ostream.h>

#include <type_traits>
#include <variant>

namespace support::detail {

template <typename T>
struct llvm_formattable {
  // clang-format off
  static constexpr bool value =
    std::is_same_v<llvm::StringRef, T>  || 
    std::is_same_v<llvm::Module, T>     || 
    std::is_base_of_v<llvm::Value, T>   ||
    std::is_base_of_v<llvm::Type, T>;
  // clang-format on
};

template <typename T>
constexpr inline bool llvm_formattable_v = llvm_formattable<T>::value;

} // namespace support::detail

template <typename Val>
struct fmt::formatter<
    Val, std::enable_if_t<support::detail::llvm_formattable_v<Val>, char>> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(Val const& v, FormatContext& ctx)
  {
    auto str = std::string {};
    auto os = llvm::raw_string_ostream(str);

    os << v;
    return format_to(ctx.out(), "{}", ::support::left_trim(os.str()));
  }
};
