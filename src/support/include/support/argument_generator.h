#pragma once

#include <support/traits.h>
 
#include <limits>
#include <memory>
#include <type_traits>

namespace support {

template <typename, typename = std::void_t<>>
struct is_generator : std::false_type {};

template <typename T>
struct is_generator<T,
  std::void_t<
    decltype(std::declval<T>().gen_int(0, 0)),
    decltype(std::declval<T>().gen_float(0.0f, 0.0f))
  >> : 
  std::conjunction<
    std::is_same<
      decltype(std::declval<T>().gen_int(0, 0)), 
      int>,
    std::is_same<
      decltype(std::declval<T>().gen_float(0.0f, 0.0f)), 
      float>
  > {};

template <typename T>
constexpr bool is_generator_v = is_generator<T>::value;

class argument_generator {
public:
  template <typename T>
  argument_generator(T&& strat) :
    strategy_(std::make_unique<model<T>>(strat))
  {
    static_assert(is_generator_v<std::decay_t<T>>, "Not a generator");
  }

  // Interface
  int gen_int(int min = std::numeric_limits<int>::min(),
              int max = std::numeric_limits<int>::max())
  {
    return strategy_->gen_int(min, max);
  }

  float gen_float(float min = std::numeric_limits<float>::min(),
                  float max = std::numeric_limits<float>::max())
  {
    return strategy_->gen_float(min, max);
  }

  // Type erasure
  struct concept {
    virtual ~concept() {}
    virtual int gen_int(int min, int max) = 0;
    virtual float gen_float(float min, float max) = 0;
  };

  template <typename T>
  struct model : concept {
    model(T obj) :
      object_(obj)
    {
    }

    int gen_int(int min, int max) override
    {
      return object_.gen_int(min, max);
    }

    float gen_float(float min, float max) override
    {
      return object_.gen_float(min, max);
    }

  private:
    T object_;
  };

private:
  std::unique_ptr<concept> strategy_;
};

}
