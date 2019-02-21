#pragma once

#include <support/traits.h>
 
#include <limits>
#include <memory>
#include <type_traits>

namespace support {

namespace detail {

/**
 * SFINAE base case - types are not generators unless they meet the requirements
 * of the template specialisation below.
 */
template <typename, typename = std::void_t<>>
struct is_generator : std::false_type {};

/**
 * SFINAE specialisation to detect valid generators. This needs both arms
 * (void_t and is_same) so that a valid type is still formed even when members
 * are missing.
 *
 * This could be a bit neater by using is_detected, but it's OK for now.
 */
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

/**
 * Helper value for convenience.
 */
template <typename T>
constexpr bool is_generator_v = is_generator<T>::value;

}

/**
 * Type-erased wrapper class that allows any type satisfying is_generator to be
 * used generically by code that needs to generate arguments.
 *
 * Defines internal model and concept classes. The provided strategy from
 * construction is stored in a unique_ptr to the concept class, with
 * implementation provided by a templated model object that inherits from the
 * concept class.
 *
 * Method calls to the outer generator type are forwarded to the internal
 * implementations.
 *
 * When an object of this class is constructed, the type passed in is checked
 * using a type trait against a definition of valid generators.
 */
class argument_generator {
public:
  template <typename T>
  argument_generator(T&& strat) :
    strategy_(std::make_unique<model<T>>(FWD(strat)))
  {
    static_assert(detail::is_generator_v<std::decay_t<T>>, "Not a generator");
  }

  // Rule of 5 to make thus class copyable
  argument_generator(argument_generator& other);
  argument_generator& operator=(argument_generator other);
  
  argument_generator(argument_generator&&) = default;
  argument_generator& operator=(argument_generator&&) = default;

  ~argument_generator() = default;

  friend void swap(argument_generator& a, argument_generator& b);

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

private:
  // Type erasure
  struct concept {
    virtual ~concept() {}
    virtual concept* clone() = 0;
    virtual int gen_int(int min, int max) = 0;
    virtual float gen_float(float min, float max) = 0;
  };

  template <typename T>
  struct model : concept {
    model(T obj) :
      object_(obj)
    {
    }

    model<T> *clone() override
    {
      return new model<T>(object_);
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

protected:
  std::unique_ptr<concept> strategy_;
};

}
