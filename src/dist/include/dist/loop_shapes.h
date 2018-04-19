#pragma once

#include <iostream>
#include <memory>

namespace accsynt {

template <typename T>
struct is_loop_shape : std::false_type {};

template <typename T>
constexpr bool is_loop_shape_v = is_loop_shape<T>::value;

struct Hole {
  constexpr Hole() = default;

  constexpr size_t size() const noexcept 
  { 
    return 1; 
  }

  std::string str() const noexcept 
  { 
    return "()";
  }
};

template <>
struct is_loop_shape<Hole> : std::true_type {};

template <
  typename Inner, 
  typename = std::enable_if_t<is_loop_shape_v<Inner>>
>
struct Nest {
  constexpr Nest(Inner in) :
    inner(in) {}

  constexpr size_t size() const noexcept
  { 
    return 1 + inner.size(); 
  }

  std::string str() const noexcept { 
    return "()[" + inner.str() + "]"; 
  }

  const Inner inner;
};

template <typename Inner>
struct is_loop_shape<Nest<Inner>> : std::true_type {};

template <
  typename First,
  typename Second,
  typename = std::enable_if_t<
    is_loop_shape_v<First> && is_loop_shape_v<Second>
  >
>
struct Seq {
  constexpr Seq(First f, Second s) :
    first(f), second(s) {}

  constexpr size_t size() const noexcept { 
    return first.size() + second.size(); 
  }
  
  std::string str() const noexcept { 
    return first.str() + " " + second.str(); 
  }

  const First first;
  const Second second;
};

template <typename First, typename Second>
struct is_loop_shape<Seq<First, Second>> : std::true_type {};

template <typename T, typename = std::enable_if_t<is_loop_shape_v<T>>>
std::ostream& operator<<(std::ostream& os, const T& s)
{
  os << s.str();
  return os;
}

}
