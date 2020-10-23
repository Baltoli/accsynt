#pragma once

#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>

#include <set>

namespace support {

struct type_conversions {
public:
  type_conversions() = default;

  void register_opaque(llvm::Type*);

  bool is_opaque(llvm::Type*) const;
  bool is_lossless(llvm::Type* from, llvm::Type* to) const;

private:
  std::set<llvm::Type*> opaque_types_;
};

} // namespace support
