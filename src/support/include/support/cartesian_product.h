#pragma once

#include <cstddef>
#include <functional>
#include <iterator>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

#include <iostream>

namespace support {

template <typename T, typename It>
class cartesian_product_iterator;

template <typename T, typename Iterator>
class cartesian_product {
public:
  using iterator = cartesian_product_iterator<T, Iterator>;
  friend iterator;

  cartesian_product(Iterator b, Iterator e) :
    begin_(b),
    product_size_(std::distance(b, e)),
    element_sizes_(product_size_)
  {
    using std::begin;
    using std::end;

    auto i = size_t{0};
    for(auto it = b; it != e; ++it) {
      element_sizes_[i++] = std::distance(begin(*it), end(*it));
    }

    n_products_ = std::accumulate(element_sizes_.begin(), element_sizes_.end(), 1, std::multiplies{});
  }

  size_t product_size() const
  {
    return product_size_;
  }

  size_t size() const
  {
    return n_products_;
  }

  iterator begin()
  {
    return iterator(0, n_products_, *this);
  }

  iterator end()
  {
    return iterator(n_products_, n_products_, *this);
  }

protected:
  std::vector<T> get(size_t idx)
  {
    using std::begin;

    auto offsets = std::vector<size_t>(product_size_, 0);

    for(auto i = 0u; i < idx; ++i) {
      auto ptr = size_t{0};
      offsets[ptr]++;
      while(offsets[ptr] == element_sizes_[ptr]) {
        offsets[ptr++] = 0;
        offsets[ptr]++;
      }
    }

    auto ret = std::vector<T>(product_size_);
    for(auto i = 0u; i < product_size_; ++i) {
      auto it = begin_;
      std::advance(it, i);

      auto bb = begin(*it);
      std::advance(bb, offsets[i]);

      ret[i] = *bb;
    }
    return ret;
  }

private:
  Iterator begin_;

  size_t product_size_;
  std::vector<size_t> element_sizes_;

  size_t n_products_;
};

template <typename Iterator>
cartesian_product(Iterator, Iterator) ->
  cartesian_product<
    typename std::iterator_traits<
      typename std::iterator_traits<Iterator>::value_type::iterator
    >::value_type,
    Iterator>;

/**
 * Construct with: index, max bound for end, ref to data
 * Random access - can jump around by incrementing
 * Deref: bump the iterators by the right amount, and return a vector of
 * appropriate data.
 *
 * Type param is the value type.
 */
template <typename T, typename It>
class cartesian_product_iterator {
public:
  using value_type = std::vector<T>;
  using difference_type = size_t;
  using pointer = std::vector<T>*;
  using reference = std::vector<T> const&;
  using iterator_category = std::random_access_iterator_tag;

  cartesian_product_iterator(size_t idx, size_t size, cartesian_product<T, It>& data) :
    index_(idx), size_(size), data_(&data)
  {
  }

  cartesian_product_iterator() :
    cartesian_product_iterator(0, 0, nullptr)
  {
  }

  reference operator*()
  {
    reload();
    return state_;
  }

  pointer operator->()
  {
    reload();
    return std::addressof(state_);
  }

  cartesian_product_iterator<T, It>& operator++()
  {
    needs_reload_ = true;
    ++index_;
    return *this;
  }

  cartesian_product_iterator<T, It> operator++(int)
  {
    needs_reload_ = true;
    auto copy = *this;
    ++index_;
    return copy;
  }

  cartesian_product_iterator<T, It>& operator--()
  {
    needs_reload_ = true;
    --index_;
    return *this;
  }

  cartesian_product_iterator<T, It> operator--(int)
  {
    needs_reload_ = true;
    auto copy = *this;
    --index_;
    return copy;
  }

  cartesian_product_iterator<T, It>& operator+=(difference_type n)
  {
    needs_reload_ = true;
    index_ += n;
    return *this;
  }

  friend cartesian_product_iterator<T, It> operator+(
      cartesian_product_iterator<T, It> it, difference_type n)
  {
    it.needs_reload_ = true;
    it.index_ += n;
    return it;
  }

  friend cartesian_product_iterator<T, It> operator+(
      difference_type n, cartesian_product_iterator<T, It> it)
  {
    it.needs_reload_ = true;
    it.index_ += n;
    return it;
  }

  cartesian_product_iterator<T, It>& operator-=(difference_type n)
  {
    needs_reload_ = true;
    index_ -= n;
    return *this;
  }

  friend cartesian_product_iterator<T, It> operator-(
      cartesian_product_iterator<T, It> it, difference_type n)
  {
    it.needs_reload_ = true;
    it.index_ -= n;
    return it;
  }

  friend difference_type operator-(
      cartesian_product_iterator<T, It> it, cartesian_product_iterator<T, It> it2)
  {
    return it.index_ - it2.index_;
  }

  value_type operator[](difference_type n)
  {
    return *(*this + n);
  }

  bool operator==(cartesian_product_iterator<T, It> const& other)
  {
    return std::tie(index_, size_, data_) ==
           std::tie(other.index_, other.size_, other.data_);
  }

  bool operator!=(cartesian_product_iterator<T, It> const& other)
  {
    return !(*this == other);
  }

  bool operator<(cartesian_product_iterator<T, It> const& other)
  {
    return std::tie(index_, size_, data_) <
           std::tie(other.index_, other.size_, other.data_);
  }

  bool operator>(cartesian_product_iterator<T, It> const& other)
  {
    return std::tie(index_, size_, data_) >
           std::tie(other.index_, other.size_, other.data_);
  }

  bool operator<=(cartesian_product_iterator<T, It> const& other)
  {
    return !(*this > other);
  }

  bool operator>=(cartesian_product_iterator<T, It> const& other)
  {
    return !(*this < other);
  }

  friend void swap(cartesian_product_iterator<T, It>& a, cartesian_product_iterator<T, It>& b)
  {
    using std::swap;
    swap(a.index_, b.index_);
    swap(a.size_, b.size_);
    swap(a.data_, b.data_);
    swap(a.state_, b.state_);
  }

private:
  size_t index_;
  size_t size_;
  cartesian_product<T, It>* data_;

  std::vector<T> state_ = {};

  bool needs_reload_ = true;

  void reload()
  {
    if(needs_reload_) {
      state_ = data_->get(index_);
    }

    needs_reload_ = false;
  }
};

}
