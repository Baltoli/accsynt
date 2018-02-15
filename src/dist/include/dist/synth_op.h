#pragma once

#include <dist/types.h>

#include <tuple>
#include <vector>

namespace llvm {
  template <typename> class ArrayRef;
  class Value;
}

using value_array = llvm::ArrayRef<llvm::Value *>;

class Add {
public:
  bool validate(value_array args);

  template <typename B>
  llvm::Value *combine(B&& b, value_array args)
  {
    if(!validate(args)) {
      return nullptr;
    }

    return b.CreateAdd(args[0], args[1]);
  }
};

class Mul {
public:
  bool validate(value_array args);

  template <typename B>
  llvm::Value *combine(B&& b, value_array args)
  {
    if(!validate(args)) {
      return nullptr;
    }

    return b.CreateMul(args[0], args[1]);
  }
};
