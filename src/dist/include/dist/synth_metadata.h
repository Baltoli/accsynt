#pragma once

#include <algorithm>
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

  void make_live(llvm::Value *v);
  std::set<llvm::Value *> & live_set() { return live_set_; }

  template <typename Pred>
  std::set<llvm::Value *> live_with(Pred&& p);

private:
  std::map<llvm::Value *, size_t> bounds_ = {};
  std::set<llvm::Value *> live_set_ = {};
};

template <typename Pred>
std::set<llvm::Value *> SynthMetadata::live_with(Pred&& p)
{
  auto ret = std::set<llvm::Value *>{};

  std::copy_if(std::begin(live_set_), std::end(live_set_), 
               std::inserter(ret, std::end(ret)), p);

  return ret;
}
