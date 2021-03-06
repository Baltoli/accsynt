#include <support/llvm_types.h>

namespace support {

void type_conversions::register_opaque(llvm::Type* op)
{
  opaque_types_.insert(op);
}

bool type_conversions::is_opaque(llvm::Type* ty) const
{
  return opaque_types_.find(ty) != opaque_types_.end();
}

bool type_conversions::is_lossless(llvm::Type* from, llvm::Type* to) const
{
  if (is_opaque(from)) {
    // Can always losslessly convert from an opaque type to anything
    return true;
  }

  if (is_opaque(to)) {
    // Conversely, can't convert to an opaque type from anything - previous case
    // will handle the opaque -> opaque conversion which is OK.
    return false;
  }

  // For now, say that only exactly equal types can be converted.
  // TODO: improve the logic to catch more cases
  return from == to;
}

} // namespace support
