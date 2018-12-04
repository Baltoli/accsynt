#pragma once

#include <cstddef>
#include <functional>
#include <iterator>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

namespace support {

template <typename T, typename It>
class cartesian_product_iterator;

template <typename ElementType, typename NestedIterator>
class cartesian_product {
public:
  using iterator = cartesian_product_iterator<ElementType, NestedIterator>;
  friend iterator;

  cartesian_product(NestedIterator b, NestedIterator e) :
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

  template <typename Container>
  cartesian_product(Container&& c) :
    cartesian_product(
      [&] { using std::begin; return begin(c); }(),
      [&] { using std::end; return end(c); }()
    )
  {
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
  std::vector<ElementType> get(size_t idx)
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

    auto ret = std::vector<ElementType>();
    for(auto i = 0u; i < product_size_; ++i) {
      auto it = begin_;
      std::advance(it, i);

      auto bb = begin(*it);
      std::advance(bb, offsets[i]);

      ret.push_back(*bb);
    }
    return ret;
  }

private:
  NestedIterator begin_;

  size_t product_size_;
  std::vector<size_t> element_sizes_;

  size_t n_products_;
};

/*
 * Horrible class template argument deduction guide. Breaking it down, what this
 * does is use iterator_traits to get the inner type stored in the container,
 * then again to get the element type within those containers.
 *
 * This means that NestedIterator needs to dereference to a container type with
 * an iterator typedef within it.
 */
template <typename NestedIterator>
cartesian_product(NestedIterator, NestedIterator) ->
  cartesian_product<
    typename std::iterator_traits<
      typename std::iterator_traits<
        NestedIterator
      >::value_type::iterator
    >::value_type,
    NestedIterator
  >;

template <typename Container>
cartesian_product(Container&&) ->
  cartesian_product<
    typename std::iterator_traits<
      typename std::iterator_traits<
        typename std::decay_t<Container>::iterator
      >::value_type::iterator
    >::value_type,
    typename std::decay_t<Container>::iterator
  >;

template <typename ElementType, typename NestedIterator>
class cartesian_product_iterator {
private:
  using iter_t = cartesian_product_iterator<ElementType, NestedIterator>;
  using product_t = cartesian_product<ElementType, NestedIterator>;

public:
  using value_type = std::vector<ElementType>;
  using difference_type = size_t;
  using pointer = std::vector<ElementType>*;
  using reference = std::vector<ElementType> const&;
  using iterator_category = std::random_access_iterator_tag;

  cartesian_product_iterator(size_t idx, size_t size, product_t& data) :
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

  iter_t& operator++()
  {
    needs_reload_ = true;
    ++index_;
    return *this;
  }

  iter_t operator++(int)
  {
    needs_reload_ = true;
    auto copy = *this;
    ++index_;
    return copy;
  }

  iter_t& operator--()
  {
    needs_reload_ = true;
    --index_;
    return *this;
  }

  iter_t operator--(int)
  {
    needs_reload_ = true;
    auto copy = *this;
    --index_;
    return copy;
  }

  iter_t& operator+=(difference_type n)
  {
    needs_reload_ = true;
    index_ += n;
    return *this;
  }

  friend iter_t operator+(iter_t it, difference_type n)
  {
    it.needs_reload_ = true;
    it.index_ += n;
    return it;
  }

  friend iter_t operator+(difference_type n, iter_t it)
  {
    it.needs_reload_ = true;
    it.index_ += n;
    return it;
  }

  iter_t& operator-=(difference_type n)
  {
    needs_reload_ = true;
    index_ -= n;
    return *this;
  }

  friend iter_t operator-(iter_t it, difference_type n)
  {
    it.needs_reload_ = true;
    it.index_ -= n;
    return it;
  }

  friend difference_type operator-(iter_t it, iter_t it2)
  {
    return it.index_ - it2.index_;
  }

  value_type operator[](difference_type n)
  {
    return *(*this + n);
  }

  bool operator==(iter_t const& other)
  {
    return std::tie(index_, size_, data_) ==
           std::tie(other.index_, other.size_, other.data_);
  }

  bool operator!=(iter_t const& other)
  {
    return !(*this == other);
  }

  bool operator<(iter_t const& other)
  {
    return std::tie(index_, size_, data_) <
           std::tie(other.index_, other.size_, other.data_);
  }

  bool operator>(iter_t const& other)
  {
    return std::tie(index_, size_, data_) >
           std::tie(other.index_, other.size_, other.data_);
  }

  bool operator<=(iter_t const& other)
  {
    return !(*this > other);
  }

  bool operator>=(iter_t const& other)
  {
    return !(*this < other);
  }

  friend void swap(iter_t& a, iter_t& b)
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
  product_t* data_;

  std::vector<ElementType> state_ = {};

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
