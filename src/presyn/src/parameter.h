#pragma once

#include <fmt/format.h>

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

#include <string>

namespace presyn {

/**
 * The virtual behaviour of a parameter is to produce a correctly typed value -
 * for instance, a parameter representing a function argument will produce a
 * contextual hole, while one representing a constant would instead produce that
 * constant.
 */
class parameter {
public:
  /**
   * Get the underlying LLVM type for this parameter.
   */
  virtual llvm::Type* type() const = 0;

  /**
   * Produce a value corresponding to this parameter - this could be a call to a
   * function or an integer constant expression. The value can then be inserted
   * into a program appropriately.
   */
  virtual llvm::Value* get() const = 0;

  /**
   * Print this parameter as a string. Used by the parent fragment to print
   * 'template' argument lists.
   */
  virtual std::string to_string() const = 0;

  virtual ~parameter() = default;
};

/**
 * A parameter representing a constant integer (e.g. to specify an unrolling
 * factor or some other constant data).
 */
class constant_int final : public parameter {
public:
  constant_int(int);

  llvm::Type* type() const override;
  llvm::Value* get() const override;

  std::string to_string() const override;

  int value() const { return value_; }

private:
  int value_;
};

/**
 * A parameter that represents a named argument (e.g. to specify the pointer /
 * size over which a loop could iterate).
 */
class named final : public parameter {
public:
  named(std::string);

  llvm::Type* type() const override;
  llvm::Value* get() const override;

  std::string name() const { return name_; }
  std::string to_string() const override;

private:
  llvm::Type* type_;
  std::string name_;
};

} // namespace presyn

template <>
struct fmt::formatter<presyn::parameter> {
  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx)
  {
    return ctx.begin();
  }

  template <typename FormatContext>
  auto format(presyn::parameter const& p, FormatContext& ctx)
  {
    return format_to(ctx.out(), "{}", p.to_string());
  }
};
