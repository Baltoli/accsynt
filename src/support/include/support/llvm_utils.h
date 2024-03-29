#pragma once

#include <llvm/IR/Value.h>

#include <string>

namespace support {

template <typename Builder, typename Iterator>
llvm::Value* create_sum(
    Builder& b, Iterator begin, Iterator end, std::string const& name)
{
  if (begin == end) {
    return nullptr;
  }

  auto sum = *begin;
  for (auto it = std::next(begin); it != end; ++it) {
    sum = b.CreateAdd(sum, *it, name);
  }

  return sum;
}

template <typename Builder, typename Iterator>
llvm::Value* create_sum(Builder& b, Iterator begin, Iterator end)
{
  return create_sum(b, begin, end, "");
}

} // namespace support
