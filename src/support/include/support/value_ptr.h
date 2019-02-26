#pragma once

namespace support {

template <typename T>
class value_ptr;

template <typename T>
void swap(value_ptr<T>& a, value_ptr<T>& b);

template <typename T>
class value_ptr {
private:
  struct pmr_concept {
    virtual ~pmr_concept() {}

    virtual pmr_concept* clone() = 0;
    virtual T* get() = 0;
    virtual T* operator->() = 0;
    virtual T& operator*() = 0;
  };

  template <typename D>
  struct pmr_model : pmr_concept {
    pmr_model(D* ptr)
        : ptr_(ptr)
    {
    }

    ~pmr_model() { delete ptr_; }

    pmr_model<D>* clone() override { return new pmr_model<D>(new D(*ptr_)); }

    D* get() override { return ptr_; }

    D* operator->() override { return ptr_; }

    D& operator*() override { return *ptr_; }

    D* ptr_;
  };

public:
  template <typename U>
  value_ptr(U* ptr)
      : impl_(new pmr_model(ptr))
  {
  }

  explicit value_ptr(std::nullptr_t)
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
    delete impl_;
    impl_ = nullptr;
    return *this;
  }

  ~value_ptr() { delete impl_; }

  T* get() { return impl_->get(); }
  T* operator->() { return impl_->get(); }
  T& operator*() { return **impl_; }

  operator bool() { return static_cast<bool>(impl_); }

  friend void swap<T>(value_ptr<T>&, value_ptr<T>&);

protected:
  pmr_concept* impl_;
};

template <typename T>
void swap(value_ptr<T>& a, value_ptr<T>& b)
{
  using std::swap;
  swap(a.impl_, b.impl_);
}
}
