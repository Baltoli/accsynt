#pragma once

namespace llvm {
class LLVMContext;
class Type;
} // namespace llvm

namespace holes {

llvm::Type* get_hole_type(llvm::LLVMContext&);
llvm::Type* get_hole_type();

} // namespace holes
