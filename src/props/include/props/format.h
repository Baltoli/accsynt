#pragma once

#include <props/props.h>

#include <fmt/format.h>

template <>
struct fmt::formatter<props::data_type> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const props::data_type& dt, FormatContext& ctx)
  {
    if(dt == props::data_type::integer) {
      return format_to(ctx.out(), "int");
    } else if(dt == props::data_type::floating) {
      return format_to(ctx.out(), "float");
    } else {
      return format_to(ctx.out(), "<BAD TYPE>");
    }
  }
};

template <>
struct fmt::formatter<props::param> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const props::param& p, FormatContext& ctx)
  {
    constexpr auto pointers = [] (auto n) {
      return std::string(n, '*');
    };

    return format_to(ctx.out(), 
        "{} {}{}", p.type, pointers(p.pointer_depth), p.name);
  }
};

template <>
struct fmt::formatter<props::signature> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const props::signature& sig, FormatContext& ctx)
  {
    auto ret = [&] {
      if(sig.return_type) {
        return fmt::format("{}", sig.return_type.value());
      } else {
        return std::string("void");
      }
    }();

    return format_to(ctx.out(), "{} {}({})",
      ret, sig.name, join(sig.parameters.begin(), sig.parameters.end(), ", "));
  }
};
