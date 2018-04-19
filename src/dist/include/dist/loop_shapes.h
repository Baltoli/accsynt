#pragma once

#include <dist/utils.h>

#include <iostream>
#include <memory>
#include <numeric>
#include <tuple>
#include <variant>
#include <vector>

namespace accsynt {

template <typename T>
struct is_loop_shape : std::false_type {};

template <typename T>
constexpr bool is_loop_shape_v = is_loop_shape<T>::value;

/**
 * Loop specifications:
 * A loop specification combines a shape with instantiated IDs.
 */
struct Loop {
  std::string str() const noexcept
  {
    return "L" + std::to_string(ID);
  }

  int ID;
};

template <>
struct is_loop_shape<Loop> : std::true_type {};

/**
 * Loop shapes:
 * The shape of a loop describes the control flow structure of a fixed number of
 * loops, but not which iterator corresponds to which loop. They can be
 * instantiated by walking their tree and assigning iterator IDs to each loop
 */
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

  template <typename Iterator>
  auto instantiate(Iterator it) const noexcept
  {
    auto l = Loop{*it};
    return std::make_pair(l, std::next(it));
  }
};

template <>
struct is_loop_shape<Hole> : std::true_type {};

template <
  typename Inner,
  typename Outer,
  typename = std::enable_if_t<is_loop_shape_v<Inner>>
>
struct Nest {
  constexpr Nest(Inner in, Outer out) :
    hole(out), inner(in) {}

  constexpr size_t size() const noexcept
  { 
    return 1 + inner.size(); 
  }

  std::string str() const noexcept { 
    return hole.str() + "[" + inner.str() + "]"; 
  }

  template <typename Iterator>
  auto instantiate(Iterator it) const noexcept
  {
    auto&& [hole_i, h_it] = hole.instantiate(it);
    auto&& [inner_i, i_it] = inner.instantiate(h_it);
    return std::make_pair(
      Nest<decltype(inner_i), decltype(hole_i)>(inner_i, hole_i),
      i_it
    );
  }

  const Outer hole;
  const Inner inner;
};

template <typename T>
auto make_nest(T t)
{
  return Nest(t, Hole{});
}

template <typename Inner, typename Outer>
struct is_loop_shape<Nest<Inner, Outer>> : std::true_type {};

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

  template <typename Iterator>
  auto instantiate(Iterator it) const noexcept
  {
    auto [first_i, f_it] = first.instantiate(it);
    auto [second_i, s_it] = second.instantiate(f_it);
    return std::make_pair(
      Seq<decltype(first_i), decltype(second_i)>{first_i, second_i},
      s_it
    );
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

template <typename Shape>
auto next_shapes(Shape s)
{
  return std::make_tuple(
    Seq{Hole{}, s},
    Seq{s, Hole{}},
    make_nest(s)
  );
}

}
