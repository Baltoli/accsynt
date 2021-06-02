#pragma once

#include <fmt/format.h>

#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

#include <nlohmann/json.hpp>

#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace idlr {

std::unordered_map<std::string, llvm::Value*> collect_names(llvm::Module& mod);

class call;
class spec;

class replacer {
public:
  explicit replacer(llvm::Module&);

  void apply(spec const&);

private:
  llvm::Module& mod_;
  std::unordered_map<std::string, llvm::Value*> name_map_;
};

class call {
public:
  explicit call(nlohmann::json);

  std::string const& target() const { return target_; }

  std::vector<std::string> const& args() const { return args_; }

private:
  std::string target_;
  std::vector<std::string> args_;
};

class spec {
public:
  explicit spec(nlohmann::json);

  std::string const& function() const { return func_; }

  std::unordered_map<std::string, call> const& replacements() const
  {
    return replacements_;
  }

private:
  std::string func_;
  std::unordered_map<std::string, call> replacements_;
};

} // namespace idlr

template <>
struct fmt::formatter<::idlr::call> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(::idlr::call const& call, FormatContext& ctx)
  {
    return format_to(
        ctx.out(), "Call({}, [{}])", call.target(),
        fmt::join(call.args(), ", "));
  }
};

template <>
struct fmt::formatter<::idlr::spec> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(::idlr::spec const& spec, FormatContext& ctx)
  {
    auto reps = std::vector<std::string> {};

    for (auto const& [k, v] : spec.replacements()) {
      reps.emplace_back(fmt::format("{} -> {}", k, v));
    }

    return format_to(
        ctx.out(), "Spec({}, [{}])", spec.function(), fmt::join(reps, ", "));
  }
};
