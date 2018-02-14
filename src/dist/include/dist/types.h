#pragma once

namespace llvm {
  class Type;
}

namespace types {

class Integer {
public:
  Integer(size_t b = 32, bool s = true) :
    bits_(b), is_signed_(s)
  {}

  llvm::Type *llvm_type() const;

private:
  size_t bits_;
  bool is_signed_;
};

}
