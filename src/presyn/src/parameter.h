#pragma once

#include <string>

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

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

private:
  int value_;
};

/**
 * A parameter that represents a named argument (e.g. to specify the pointer /
 * size over which a loop could iterate).
 */
class named final : public parameter {
public:
  named(llvm::Type*, std::string);

  llvm::Type* type() const override;
  llvm::Value* get() const override;

  std::string to_string() const override;

private:
  llvm::Type* type_;
  std::string name_;
};

} // namespace presyn
