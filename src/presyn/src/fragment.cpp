#include "fragment.h"

namespace presyn {

std::unique_ptr<fragment> fragment::parse(std::string_view)
{
  // TODO unimplemented
  return nullptr;
}

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

} // namespace presyn
