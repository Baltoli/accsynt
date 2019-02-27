#pragma once

#include <functional>
#include <memory>
#include <type_traits>

namespace support {

template <typename T>
class value_ptr {
public:
  using pointer = T*;

  template <typename U>
  friend class value_ptr;

private:
  struct pmr_concept {
    virtual ~pmr_concept() {}

    virtual pmr_concept* clone() = 0;
    virtual T* get() = 0;
    virtual T& operator*() = 0;
    virtual T* release() = 0;
  };

  template <typename D>
  struct pmr_model : pmr_concept {
    pmr_model(D* ptr)
        : ptr_(ptr)
    {
    }

    ~pmr_model()
    {
      if (ptr_) {
        delete ptr_;
      }
    }

    pmr_model<D>* clone() override { return new pmr_model<D>(new D(*ptr_)); }

    D* get() override { return ptr_; }

    D& operator*() override { return *ptr_; }

    D* release() override
    {
      auto ptr = ptr_;
      ptr_ = nullptr;
      return ptr;
    }

    D* ptr_;
  };

public:
  template <typename U>
  value_ptr(U* ptr)
      : impl_(new pmr_model(ptr))
  {
  }

  template <typename U,
      typename = std::enable_if_t<
          std::is_convertible_v<typename value_ptr<U>::pointer, pointer>>>
  value_ptr(value_ptr<U> other)
  {
    auto clone = other.impl_->clone();
    impl_ = new pmr_model(clone->release());
    delete clone;
  }

  value_ptr(std::nullptr_t)
      : impl_(nullptr)
  {
  }

  value_ptr()
      : value_ptr(nullptr)
  {
  }

  value_ptr(value_ptr<T> const& other)
      : impl_(other.impl_->clone())
  {
  }

  value_ptr<T>& operator=(value_ptr<T> other)
  {
    using std::swap;
    swap(*this, other);
    return *this;
  }

  value_ptr(value_ptr<T>&& other)
      : impl_(std::move(other.impl_))
  {
    other.impl_ = nullptr;
  }

  value_ptr<T>& operator=(std::nullptr_t)
  {
    reset();
    return *this;
  }

  ~value_ptr()
  {
    if (impl_) {
      delete impl_;
    }
  }

  T* get() const { return impl_->get(); }
  T* operator->() const { return impl_->get(); }
  T& operator*() const { return **impl_; }

  operator bool() { return static_cast<bool>(impl_); }

  T* release()
  {
    auto ptr = impl_->release();
    delete impl_;
    impl_ = nullptr;
    return ptr;
  }

  void reset(T* ptr = nullptr)
  {
    if (impl_) {
      delete impl_;
    }

    if (ptr) {
      impl_ = new pmr_model(ptr);
    } else {
      impl_ = nullptr;
    }
  }

  void swap(value_ptr<T>& other)
  {
    using std::swap;
    swap(impl_, other.impl_);
  }

protected:
  pmr_concept* impl_;
};

template <typename T1, typename T2>
bool operator==(value_ptr<T1> const& a, value_ptr<T2> const& b)
{
  return a.get() == b.get();
}

template <typename T1, typename T2>
bool operator!=(value_ptr<T1> const& a, value_ptr<T2> const& b)
{
  return a.get() != b.get();
}

template <typename T1, typename T2>
bool operator<(value_ptr<T1> const& a, value_ptr<T2> const& b)
{
  using CT = std::common_type_t<typename value_ptr<T1>::pointer,
      typename value_ptr<T2>::pointer>;
  return std::less<CT>()(a.get(), b.get());
}

template <typename T1, typename T2>
bool operator<=(value_ptr<T1> const& a, value_ptr<T2> const& b)
{
  return !(b < a);
}

template <typename T1, typename T2>
bool operator>(value_ptr<T1> const& a, value_ptr<T2> const& b)
{
  return b < a;
}

template <typename T1, typename T2>
bool operator>=(value_ptr<T1> const& a, value_ptr<T2> const& b)
{
  return !(a < b);
}

template <typename T>
bool operator==(value_ptr<T> const& a, std::nullptr_t)
{
  return !a;
}

template <typename T>
bool operator==(std::nullptr_t, value_ptr<T> const& a)
{
  return !a;
}

template <typename T>
bool operator!=(value_ptr<T> const& a, std::nullptr_t)
{
  return (bool)a;
}

template <typename T>
bool operator!=(std::nullptr_t, value_ptr<T> const& a)
{
  return (bool)a;
}

template <typename T>
bool operator<(value_ptr<T> const& a, std::nullptr_t)
{
  return std::less<typename value_ptr<T>::pointer>()(a.get(), nullptr);
}

template <typename T>
bool operator<(std::nullptr_t, value_ptr<T> const& a)
{
  return std::less<typename value_ptr<T>::pointer>()(nullptr, a.get());
}

template <typename T>
bool operator<=(value_ptr<T> const& a, std::nullptr_t)
{
  return !(nullptr < a);
}

template <typename T>
bool operator<=(std::nullptr_t, value_ptr<T> const& a)
{
  return !(a < nullptr);
}

template <typename T>
bool operator>(value_ptr<T> const& a, std::nullptr_t)
{
  return nullptr < a;
}

template <typename T>
bool operator>(std::nullptr_t, value_ptr<T> const& a)
{
  return a < nullptr;
}

template <typename T>
bool operator>=(value_ptr<T> const& a, std::nullptr_t)
{
  return !(a < nullptr);
}

template <typename T>
bool operator>=(std::nullptr_t, value_ptr<T> const& a)
{
  return !(nullptr < a);
}

template <typename T>
void swap(value_ptr<T>& a, value_ptr<T>& b)
{
  a.swap(b);
}

template <typename T, typename... Args>
auto make_value(Args&&... args)
{
  return value_ptr<T>(new T(std::forward<Args>(args)...));
}
}

namespace std {

template <typename T>
struct hash<support::value_ptr<T>> {
  std::size_t operator()(support::value_ptr<T> const& ptr) const
  {
    return std::hash<typename support::value_ptr<T>::pointer>()(ptr.get());
  }
};
}
