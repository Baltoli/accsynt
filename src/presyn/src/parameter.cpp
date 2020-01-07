#include "parameter.h"

#include <fmt/format.h>

namespace presyn {

using namespace fmt::literals;

// Constant ints

constant_int::constant_int(int v)
    : value_(v)
{
}

llvm::Type* constant_int::type() const
{
  // TODO unimplemented
  return nullptr;
}

llvm::Value* constant_int::get() const
{
  // TODO unimplemented
  return nullptr;
}

std::string constant_int::to_string() const { return "{}"_format(value_); }

// Named parameters

named::named(llvm::Type* t, std::string n)
    : type_(t)
    , name_(n)
{
}

llvm::Type* named::type() const { return type_; }

llvm::Value* named::get() const
{
  // TODO unimplemented
  return nullptr;
}

std::string named::to_string() const { return "@{}"_format(name_); }

} // namespace presyn
