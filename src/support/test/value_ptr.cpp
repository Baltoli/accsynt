#include <catch2/catch.hpp>

#include <support/value_ptr.h>

namespace support {

template <typename T>
class value_ptr {
private:
  struct pmr_concept {
    virtual ~pmr_concept()
    {
    }

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

    ~pmr_model()
    {
      delete ptr_;
    }

    D* get() override
    {
      return ptr_;
    }

    D* operator->() override
    {
      return ptr_;
    }

    D& operator*() override
    {
      return *ptr_;
    }

    D* ptr_;
  };

public:
  template <typename U>
  value_ptr(U* ptr)
      : impl_(new pmr_model(ptr))
  {
  }

private:
  pmr_concept* impl_;
};
}
