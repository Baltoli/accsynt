#include <support/llvm_types.h>

namespace support {

void type_conversions::register_opaque(llvm::Type* op)
{
  opaque_types_.insert(op);
}

} // namespace support
