#pragma once

#include <cstddef>
#include <iterator>
#include <tuple>
#include <utility>
#include <vector>

namespace support {

template <typename T>
class cartesian_product_iterator;

/**
 * Wrapper view class that accepts a range to product over, and gives iterators
 * that dereference to vectors of objects.
 *
 * Some maths to think about:
 *  * Easy to work out the total number of items the product view will produce -
 *    just the product over the lengths of its elements.
 *  * Which means that an integer in this range uniquely identifies a product
 *    element.
 *  * So the first bit of setup.
 */
template <typename T>
class cartesian_product {
public:
  using iterator = cartesian_product_iterator<T>;
  friend iterator;

  template <typename Iterator>
  cartesian_product(Iterator b, Iterator e) :
    size_(std::distance(b, e))
  {
  }

  iterator begin()
  {
    return iterator(0, size_, *this);
  }

  iterator end()
  {
    return iterator(size_, size_, *this);
  }

protected:
  std::vector<T> get(size_t idx)
  {
    return std::vector<T>(idx);
  }

private:
  size_t size_;
};

template <typename Iterator>
cartesian_product(Iterator b, Iterator e) -> 
  cartesian_product<typename std::iterator_traits<Iterator>::value_type>;

/**
 * Construct with: index, max bound for end, ref to data
 * Random access - can jump around by incrementing
 * Deref: bump the iterators by the right amount, and return a vector of
 * appropriate data.
 *
 * Type param is the value type.
 */
template <typename T>
class cartesian_product_iterator {
public:
  using value_type = std::vector<T>;
  using difference_type = size_t;
  using pointer = std::vector<T>*;
  using reference = std::vector<T> const&;
  using iterator_category = std::input_iterator_tag;

  cartesian_product_iterator(size_t idx, size_t size, cartesian_product<T>& data) :
    index_(idx), size_(size), data_(&data)
  {
  }

  cartesian_product_iterator() :
    cartesian_product_iterator(0, 0, nullptr)
  {
  }

  value_type operator*()
  {
    return state_;
  }

  pointer operator->()
  {
    return std::addressof(state_);
  }

  cartesian_product_iterator<T>& operator++()
  {
    ++index_;
    reload();
    return *this;
  }

  cartesian_product_iterator<T>& operator++(int)
  {
    auto copy = *this;
    ++index_;
    reload();
    return copy;
  }

  bool operator==(cartesian_product_iterator<T>& other)
  {
    return std::tie(index_, size_, data_) ==
           std::tie(other.index_, other.size_, other.data_);
  }

  bool operator!=(cartesian_product_iterator<T>& other)
  {
    return !(*this == other);
  }

  friend void swap(cartesian_product_iterator<T>& a, cartesian_product_iterator<T>& b)
  {
    using std::swap;
    swap(a.index_, b.index_);
    swap(a.size_, b.size_);
    swap(a.data_, b.data_);
  }

private:
  size_t index_;
  size_t size_;
  cartesian_product<T>* data_;

  std::vector<T> state_ = {};

  void reload()
  {
    state_ = data_->get(index_);
  }
};

}
