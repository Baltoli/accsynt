#pragma once

#include <dist/utils.h>

#include <random>
#include <tuple>

namespace gen {

template <typename T>
class Geometric {
public:
  using gen_t = T;

  Geometric(double p = 0.5) :
    engine_(std::random_device{}()), geo_(p) {}

  gen_t operator()()
  {
    return geo_(engine_);
  }

private:
  std::default_random_engine engine_;
  std::geometric_distribution<T> geo_;
};

template <typename T>
class Sequential {
public:
  using gen_t = T;

  Sequential(T start = 0) :
    state_(start) {}
  
  gen_t operator()()
  {
    return state_++;
  }
private:
  T state_; 
};

template <typename T>
class Constant {
  using gen_t = T;

  Constant(T v) :
    value_(v) {}

  gen_t operator()() const
  {
    return value_;
  }
private:
  const T value_;
};

template<class... Args>
class Tuple {
public:
  using gen_t = std::tuple<typename Args::gen_t...>;

  Tuple(Args... args) :
    generators_(std::make_tuple(args...)) {}

  Tuple(std::tuple<Args...> args) :
    generators_(args) {}

  gen_t operator()()
  {
    auto ret = gen_t{};
    zip_for_each(ret, generators_, [this](auto&& t, auto&& d) {
      t = d();
    });

    return ret;
  }

private:
  std::tuple<Args...> generators_;
};

}
