#pragma once

#include <map>
#include <optional>
#include <set>

namespace llvm {
  class Value;
}

class SynthMetadata {
public:
  SynthMetadata() = default;

  std::optional<size_t> index_bound(llvm::Value *v) const;
  bool is_index(llvm::Value *v) const;
  void set_index_bound(llvm::Value *v, size_t b);

  std::set<llvm::Value *> & live_set() { return live_set_; }
private:
  std::map<llvm::Value *, size_t> bounds_ = {};
  std::set<llvm::Value *> live_set_ = {};
};
