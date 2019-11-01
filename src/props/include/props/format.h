#pragma once

#include <props/props.h>

#include <fmt/format.h>

inline std::string pointers(int n) { return std::string(n, '*'); }

template <>
struct fmt::formatter<props::base_type> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const props::base_type& dt, FormatContext& ctx)
  {
    switch (dt) {
    case props::base_type::character:
      return format_to(ctx.out(), "char");
    case props::base_type::floating:
      return format_to(ctx.out(), "float");
    case props::base_type::integer:
      return format_to(ctx.out(), "int");
    case props::base_type::boolean:
      return format_to(ctx.out(), "bool");
    default:
      return format_to(ctx.out(), "<BAD TYPE>");
    }
  }
};

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
    if (dt.pointers > 0) {
      return format_to(ctx.out(), "{} {}", dt.base, pointers(dt.pointers));
    } else {
      return format_to(ctx.out(), "{}", dt.base);
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
    return format_to(
        ctx.out(), "{} {}{}", p.type, pointers(p.pointer_depth), p.name);
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
      if (sig.return_type) {
        return fmt::format("{}", sig.return_type.value());
      } else {
        return std::string("void");
      }
    }();

    return format_to(ctx.out(), "{} {}({})", ret, sig.name,
        join(sig.parameters.begin(), sig.parameters.end(), ", "));
  }
};

template <>
struct fmt::formatter<props::value> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const props::value& val, FormatContext& ctx)
  {
    switch (val.value_type) {
    case props::value::type::integer:
      return format_to(ctx.out(), "{}", val.int_val);
      break;
    case props::value::type::floating:
      return format_to(ctx.out(), "{}", val.float_val);
      break;
    case props::value::type::parameter:
      return format_to(ctx.out(), "{}", val.param_val);
      break;
    case props::value::type::string:
      return format_to(ctx.out(), "\"{}\"", val.string_val);
      break;
    }

    return format_to(ctx.out(), "<BADVAL>");
  }
};

template <>
struct fmt::formatter<props::property> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const props::property& p, FormatContext& ctx)
  {
    using namespace fmt::literals;

    return format_to(ctx.out(), "{name}{sep}{vals}", "name"_a = p.name,
        "sep"_a = p.values.empty() ? "" : " ",
        "vals"_a = fmt::join(p.values, ", "));
  }
};

template <>
struct fmt::formatter<props::property_set> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(const props::property_set& ps, FormatContext& ctx)
  {
    using namespace fmt::literals;

    return format_to(ctx.out(), "{sig}{sep}{props}",
        "sig"_a = ps.type_signature,
        "sep"_a = ps.properties.empty() ? "" : "\n",
        "props"_a = fmt::join(ps.properties, "\n"));
  }
};
