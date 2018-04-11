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

namespace v2 {

template <typename Value, typename Key>
class LookupRef {
public:
  LookupRef(std::map<Key, Value>& m, Key k) :
    map_(m), k_(k) {}

  operator Value*() const
  {
    if(auto d = map_.find(k_); d != std::end(map_)) {
      return &(d->second);
    } else {
      return nullptr;
    }
  }

  LookupRef<Value, Key>& operator=(Value v)
  {
    map_.insert_or_assign(k_, v);
    return *this;
  }

private:
  std::map<Key, Value>& map_;
  Key k_;
};

template <typename Key>
class LookupRef<bool, Key> {
public:
  LookupRef(std::set<Key>& m, Key k) :
    items_(m), k_(k) {}

  operator bool() const
  {
    auto d = items_.find(k_); 
    return d != std::end(items_);
  }

  LookupRef<bool, Key>& operator=(bool v)
  {
    if(v) {
      items_.insert(k_);
    } else {
      items_.erase(k_);
    }
    return *this;
  }

private:
  std::set<Key>& items_;
  Key k_;
};

template <typename Value, typename Key = llvm::Value *>
class MetadataEntry {
public:
  auto operator()(Key k) { return LookupRef<Value, Key>(data_, k); }
  void unset(Key k) { data_.erase(k); }

  auto begin() { return std::begin(data_); }
  auto end() { return std::end(data_); }

private:
  std::map<Key, Value> data_ = {};
};

template <typename Key>
class MetadataEntry<bool, Key> {
public:
  auto operator()(Key k) { return LookupRef<bool, Key>(data_, k); }

  auto begin() { return std::begin(data_); }
  auto end() { return std::end(data_); }

private:
  std::set<Key> data_ = {};
};

struct SynthMetadata {
  MetadataEntry<size_t> size;
  MetadataEntry<size_t> index_bound;
  MetadataEntry<bool>   oob;
  MetadataEntry<bool>   live;
};

}

}
