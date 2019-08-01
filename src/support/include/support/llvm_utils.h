#pragma once

#include <llvm/IR/Value.h>

namespace support {

template <typename Builder, typename Iterator>
llvm::Value* create_sum(Builder&& b, Iterator begin, Iterator end)
{
  return nullptr;
}

} // namespace support
