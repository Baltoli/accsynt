#pragma once

#include <props/props.h>

#include <support/assert.h>
#include <support/traits.h>

#include <llvm/ExecutionEngine/GenericValue.h>

#include <algorithm>
#include <cstdint>
#include <type_traits>
#include <vector>

namespace support {

namespace detail {

/**
 * Extract the nth byte of a value, using memcpy (the only portable way to do
 * type punning of the kind required here).
 */
template <typename T>
uint8_t nth_byte(T val, size_t n)
{
  uint8_t data[sizeof(T)] = {0};
  memcpy(data, &val, sizeof(T));
  return data[n];
}

template <typename T>
T from_bytes(uint8_t const* data)
{
  auto ret = T {};
  memcpy(&ret, data, sizeof(T));
  return ret;
}

template <typename T>
std::vector<uint8_t> to_bytes(T val)
{
  auto ret = std::vector<uint8_t>(sizeof(T), 0);

  uint8_t data[sizeof(T)] = {0};
  memcpy(data, &val, sizeof(T));

  std::copy(&data[0], &data[sizeof(T)], ret.begin());

  return ret;
}

} // namespace detail

/**
 * Custom exception class for errors that occur during argument pack
 * construction.
 */
class call_builder_error : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

/**
 * Responsible for accepting input arguments according to a type signature and
 * combining them into an array of bytes that can be passed to a call wrapper.
 *
 * Builders can accept integer and floating point scalar values, and vectors of
 * the same. Scalars are copied directly into the output array, while vector
 * data is handled by storing copies of passed vector arguments inside the
 * builder.
 *
 * The reason for this is that the implementation functions inside call wrappers
 * accept pointers - an alternative design choice would be to copy data out into
 * a central vector, and store argument pointers as offsets into that vector.
 */
class call_builder {
public:
  /**
   * Construct with a type signature - the signature is used to check that each
   * argument is correct when it is added to the pack.
   */
  explicit call_builder(props::signature sig);

  /**
   * Construct a call_builder with a type signature as well as a series of
   * arguments. This just forwards to the variadic helper after delegating the
   * constructor.
   */
  template <typename... Ts>
  explicit call_builder(props::signature sig, Ts&&... args);

  /**
   * Copy constructor and assignment using copy-and-swap. The copy constructor
   * performs a deep copy of stored vectors, ensuring that the newly constructed
   * builder has pointers into its own vectors.
   */
  call_builder(call_builder const&);
  call_builder& operator=(call_builder);

  /**
   * Destroy the currently accumulated arguments and return to the beginning of
   * the building process.
   */
  void reset();

  /**
   * Is this builder ready to be used as arguments to a function? True iff the
   * added argument count is the same as the number of parameters in the
   * underlying signature.
   */
  bool ready() const;

  /**
   * The number of arguments added to this builder so far.
   */
  size_t args_count() const;

  /**
   * The maximum number of arguments that can be added to this builder.
   */
  size_t args_capacity() const;

  /**
   * Add a scalar value to the argument pack, copying its bytes in directly. If
   * the builder is not expecting a scalar argument of the passed type, an
   * exception is thrown.
   *
   * T must be int or float.
   */
  template <typename T>
  void add(T arg);

  void add(int arg);

  /**
   * Add a vector to the argument pack. Copies the vector into the builder's
   * internal storage, then writes the raw bytes of the newly copied vector's
   * data pointer into the argument pack. If the builder is not expecting a
   * vector argument of the passed type, an exception is thrown.
   *
   * T must be int or float.
   */
  template <typename T>
  void add(std::vector<T> arg);

  /**
   * Variadic helper for multiple arguments. The explicit specialisations
   */
  template <typename... Ts>
  void add(Ts...);

  /**
   * Method for testing - allows the value stored in a call_builder's argument
   * pack to be extracted to a particular type. Note that if your types are
   * wrong this will obviously return some garbage, unsafe pointers etc.
   */
  template <typename T>
  T get(size_t idx) const;

  /**
   * Method for dumping IO examples - retrieves the raw bytes as they'd be
   * passed through to the called function, but segregated by parameter type so
   * we can disambiguate them).
   */
  std::vector<uint8_t> get_bytes(size_t idx) const;

  /**
   * Testing methods used primarily for dumping IO examples, but can be used for
   * any kind of behaviour that is uniform over the type of contained data.
   */
  template <typename ScalarF, typename VectorF>
  void visit_args(ScalarF&& on_scalar, VectorF&& on_vector) const;

  template <typename VectorF>
  void visit_pointer_args(VectorF&& on_vector) const;

  template <typename ScalarF>
  void visit_scalar_args(ScalarF&& on_scalar) const;

  /**
   * Testing method that looks up the index of the supplied argument and
   * dispatches to the index-based lookup.
   */
  template <typename T>
  T get(std::string const& name) const;

  /**
   * Access the signature being used to validate arguments.
   */
  props::signature const& signature() const;

  /**
   * Get a pointer to the raw argument data being stored, suitable for being
   * passed to a call wrapper function.
   */
  uint8_t* args();

  /**
   * Scalar equality comparison - are all the scalar arguments to this builder
   * the same as the ones passed to the other builder? This essentially denotes
   * equality up to possible mutation of memory (i.e. if the other builder
   * represents the state after a call, we allow it to have been mutated).
   */
  bool scalar_args_equal(call_builder const& other) const;

  /**
   * Deep equality comparison - descends into stored vectors rather than
   * comparing pointer data for equality.
   */
  bool operator==(call_builder const& other) const;
  bool operator!=(call_builder const& other) const;

  /**
   * ADL swap for copy-and-swap.
   */
  friend void swap(call_builder& left, call_builder& right);

private:
  props::signature signature_;
  std::vector<uint8_t> args_;

  size_t current_arg_ = 0;
  std::vector<std::vector<int64_t>> int_data_ = {};
  std::vector<std::vector<float>> float_data_ = {};
  std::vector<std::vector<char>> char_data_ = {};
};

struct output_example {
  uint64_t return_value;
  call_builder output_args;
};

template <typename... Ts>
call_builder::call_builder(props::signature sig, Ts&&... args)
    : call_builder(sig)
{
  add(std::forward<Ts>(args)...);
}

template <typename T>
void call_builder::add(T arg)
{
  using Base = std::decay_t<T>;

  // clang-format off
  static_assert((
    is_buildable_int_v<Base> ||
    std::is_same_v<Base, float> || 
    std::is_same_v<Base, char>) &&
    !std::is_pointer_v<Base>, "Must be scalar, not pointer!");
  // clang-format on

  if (ready()) {
    throw call_builder_error("Parameter list is already full");
  }

  auto param = signature_.parameters.at(current_arg_);

  if constexpr (std::is_same_v<Base, char>) {
    if (param.type != props::base_type::character) {
      throw call_builder_error("Adding non-character when character expected");
    }
  }

  if constexpr (is_buildable_int_v<Base>) {
    if (param.type != props::base_type::integer) {
      throw call_builder_error("Adding non-integer when integer expected");
    }
  }

  if constexpr (std::is_same_v<Base, float>) {
    if (param.type != props::base_type::floating) {
      throw call_builder_error("Adding non-float when float expected");
    }
  }

  if (param.pointer_depth != 0) {
    throw call_builder_error("Adding non-pointer when pointer expected");
  }

  for (auto i = 0u; i < sizeof(T); ++i) {
    args_.push_back(detail::nth_byte(arg, i));
  }

  current_arg_++;
}

template <typename T>
void call_builder::add(std::vector<T> arg)
{
  static_assert(
      is_buildable_int_v<
          T> || std::is_same_v<T, float> || std::is_same_v<T, char>,
      "Pointed-to data must be of base type");

  assertion(!ready(), "Cannot add argument when pack is ready!");

  auto param = signature_.parameters.at(current_arg_);

  if constexpr (std::is_same_v<T, char>) {
    if (param.type != props::base_type::character) {
      throw call_builder_error("Adding non-character when character expected");
    }
  }

  if constexpr (is_buildable_int_v<T>) {
    if (param.type != props::base_type::integer) {
      throw call_builder_error("Adding non-integer when integer expected");
    }
  }

  if constexpr (std::is_same_v<T, float>) {
    if (param.type != props::base_type::floating) {
      throw call_builder_error("Adding non-float when float expected");
    }
  }

  assertion(
      param.pointer_depth == 1, "Cannot add nested pointers (param: {})",
      param);

  void* data = nullptr;
  if constexpr (std::is_same_v<T, char>) {
    char_data_.push_back(arg);
    data = char_data_.back().data();
  } else if constexpr (is_buildable_int_v<T>) {
    int_data_.push_back(arg);
    data = int_data_.back().data();
  } else if constexpr (std::is_same_v<T, float>) {
    float_data_.push_back(arg);
    data = float_data_.back().data();
  }

  assertion(
      data || arg.empty(), "Something very wrong inside vector building!");

  for (auto i = 0u; i < sizeof(data); ++i) {
    args_.push_back(detail::nth_byte(data, i));
  }

  current_arg_++;
}

template <typename... Ts>
void call_builder::add(Ts... args)
{
  (add(args), ...);
}

template <typename T>
T call_builder::get(size_t idx) const
{
  if (!(idx < current_arg_)) {
    throw call_builder_error("Can't extract - not enough arguments packed");
  }

  size_t offset = 0;
  size_t int_offset = 0;
  size_t float_offset = 0;
  size_t char_offset = 0;

  for (auto i = 0u; i < idx; ++i) {
    auto const& param = signature_.parameters.at(i);

    if (param.pointer_depth == 0) {
      offset += base_type_size(param.type);
    } else {
      if (param.pointer_depth != 1) {
        throw std::runtime_error("Can't extract nested pointers");
      }

      if (param.type == props::base_type::character) {
        ++char_offset;
      } else if (param.type == props::base_type::integer) {
        ++int_offset;
      } else if (param.type == props::base_type::floating) {
        ++float_offset;
      }

      offset += 8;
    }
  }

  if constexpr (
      is_buildable_int_v<
          T> || std::is_same_v<T, float> || std::is_same_v<T, char>) {
    return detail::from_bytes<T>(args_.data() + offset);
  } else if constexpr (std::is_same_v<T, std::vector<int64_t>>) {
    return int_data_.at(int_offset);
  } else if constexpr (std::is_same_v<T, std::vector<float>>) {
    return float_data_.at(float_offset);
  } else if constexpr (std::is_same_v<T, std::vector<char>>) {
    return char_data_.at(float_offset);
  } else {
    static_assert(false_v<T>, "Unknown type when extracting!");
  }
}

template <typename T>
T call_builder::get(std::string const& name) const
{
  auto b = signature_.parameters.begin();
  auto e = signature_.parameters.end();

  auto found = std::find_if(b, e, [&](auto p) { return p.name == name; });
  if (found != e) {
    return get<T>(std::distance(b, found));
  } else {
    throw call_builder_error("Parameter name not found when extracting");
  }
}

template <typename ScalarF, typename VectorF>
void call_builder::visit_args(ScalarF&& on_scalar, VectorF&& on_vector) const
{
  for (auto i = 0u; i < args_count(); ++i) {
    auto const& param = signature_.parameters.at(i);

    if (param.pointer_depth == 0) {
      if (param.type == props::base_type::character) {
        std::forward<ScalarF>(on_scalar)(get<char>(i));
      } else if (param.type == props::base_type::integer) {
        std::forward<ScalarF>(on_scalar)(get<int64_t>(i));
      } else if (param.type == props::base_type::floating) {
        std::forward<ScalarF>(on_scalar)(get<float>(i));
      } else {
        invalid_state();
      }
    } else {
      assertion(
          param.pointer_depth == 1, "Can't visit nested pointers (param: {})",
          param);

      if (param.type == props::base_type::character) {
        std::forward<VectorF>(on_vector)(get<std::vector<char>>(i));
      } else if (param.type == props::base_type::integer) {
        std::forward<VectorF>(on_vector)(get<std::vector<int64_t>>(i));
      } else if (param.type == props::base_type::floating) {
        std::forward<VectorF>(on_vector)(get<std::vector<float>>(i));
      } else {
        invalid_state();
      }
    }
  }
}

template <typename VectorF>
void call_builder::visit_pointer_args(VectorF&& on_vector) const
{
  visit_args([](auto&&) {}, std::forward<VectorF>(on_vector));
}

template <typename ScalarF>
void call_builder::visit_scalar_args(ScalarF&& on_scalar) const
{
  visit_args(std::forward<ScalarF>(on_scalar), [](auto&&) {});
}

} // namespace support
