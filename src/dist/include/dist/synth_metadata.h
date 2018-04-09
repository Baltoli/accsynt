#pragma once

#include <algorithm>
#include <map>
#include <optional>
#include <set>

namespace llvm {
  class Value;
}

namespace accsynt {

class SynthMetadata {
public:
  SynthMetadata() = default;

  std::optional<size_t> index_bound(llvm::Value *v) const;
  bool is_index(llvm::Value *v) const;
  void set_index_bound(llvm::Value *v, size_t b);

  void make_live(llvm::Value *v);
  std::set<llvm::Value *> const& live_set() const { return live_set_; }

  template <typename Pred>
  std::set<llvm::Value *> live_with(Pred&& p);

  void make_oob_flag(llvm::Value *v);
  std::set<llvm::Value *> const& oob_flags() const { return oob_flags_; }

  std::optional<size_t> size(llvm::Value *v) const;
  bool has_size(llvm::Value *v) const;
  void set_size(llvm::Value *v, size_t b);
private:
  std::map<llvm::Value *, size_t> bounds_ = {};
  std::map<llvm::Value *, size_t> sizes_ = {};
  std::set<llvm::Value *> live_set_ = {};
  std::set<llvm::Value *> oob_flags_ = {};
};

template <typename Pred>
std::set<llvm::Value *> SynthMetadata::live_with(Pred&& p)
{
  auto ret = std::set<llvm::Value *>{};

  std::copy_if(std::begin(live_set_), std::end(live_set_), 
               std::inserter(ret, std::end(ret)), p);

  return ret;
}

}
