#pragma once

#include <map>
#include <optional>

namespace llvm {
  class Value;
}

class SynthMetadata {
public:
  SynthMetadata() = default;

  std::optional<size_t> index_bound(llvm::Value *v) const;
  void set_index_bound(llvm::Value *v, size_t b);

private:
  std::map<llvm::Value *, size_t> bounds_ = {};
};
