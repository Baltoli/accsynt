#ifndef GENERATOR_H
#define GENERATOR_H

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
    gens_(gs...) {}

  tuple_t next() {
    return std::apply([](auto&&... x){
      return std::make_tuple(x()...);},
    gens_);
  };
private:
  std::tuple<Gs...> gens_;
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


#endif
