#pragma once

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

#include <set>

namespace support {

struct type_conversions {
public:
  type_conversions() = default;

  void register_opaque(llvm::Type*);

private:
  std::set<llvm::Type*> opaque_types_;
};

} // namespace support
