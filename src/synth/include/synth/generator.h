#pragma once

#include <tuple>

template<class T, class Base>
struct Generator {
  using return_t = T;

  T operator()() {
    return static_cast<Base &>(*this).next();
  }
};

template<class... Gs>
struct Args : Generator<std::tuple<typename Gs::return_t...>, Args<Gs...>> {
  using tuple_t = std::tuple<typename Gs::return_t...>;

  Args(Gs... gs) :
    gens(gs...) {}

  tuple_t next() {
    return std::apply([](auto&&... x){
      return std::make_tuple(x()...);},
    gens);
  };

  std::tuple<Gs...> gens;
};

struct Sequential : Generator<int, Sequential> {
  int next();
  void reset();

private:
  int state_ = 0;
};

struct Zero : Generator<int, Zero> {
  int next();
};

template<class T>
struct Hint : Generator<T, Hint<T>> {
  Hint(T t) :
    hint_(t) {}

  T next() {
    return hint_;
  }

  void set_hint(T t) {
    hint_ = t;
  }
private:
  T hint_;
};
