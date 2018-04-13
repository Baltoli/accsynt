#pragma once

#include <algorithm>
#include <map>
#include <optional>
#include <set>

namespace llvm {
  class Value;
}

namespace accsynt {

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

private:
  std::map<Key, Value> data_ = {};

public:
  using iterator = typename decltype(data_)::iterator;
  using const_iterator = const iterator;

  iterator begin() const noexcept { return std::begin(data_); }
  iterator end() const noexcept { return std::end(data_); }
  iterator begin() noexcept { return std::begin(data_); }
  iterator end() noexcept { return std::end(data_); }
  const_iterator cbegin() const noexcept { return std::begin(data_); }
  const_iterator cend() const noexcept { return std::cend(data_); }
};

template <typename Key>
class MetadataEntry<bool, Key> {
public:
  auto operator()(Key k) { return LookupRef<bool, Key>(data_, k); }

private:
  std::set<Key> data_ = {};

public:
  using iterator = typename decltype(data_)::iterator;
  using const_iterator = const iterator;

  iterator begin() const noexcept { return std::begin(data_); }
  iterator end() const noexcept { return std::end(data_); }
  iterator begin() noexcept { return std::begin(data_); }
  iterator end() noexcept { return std::end(data_); }
  const_iterator cbegin() const noexcept { return std::begin(data_); }
  const_iterator cend() const noexcept { return std::cend(data_); }
};

struct SynthMetadata {
  MetadataEntry<size_t> size;
  MetadataEntry<size_t> index_bound;
  MetadataEntry<bool>   oob;
  MetadataEntry<bool>   live;
  MetadataEntry<bool>   output;
};

}
