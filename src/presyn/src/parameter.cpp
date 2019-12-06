#include "parameter.h"

namespace presyn {

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

} // namespace presyn
