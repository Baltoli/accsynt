#pragma once

#include <props/props.h>
#include <support/traits.h>

#include <llvm/ExecutionEngine/GenericValue.h>

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
  uint8_t data[sizeof(T)] = { 0 };
  memcpy(data, &val, sizeof(T));
  return data[n];
}
}

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
  call_builder(props::signature sig);

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
   * Add a scalar value to the argument pack, copying its bytes in directly. If
   * the builder is not expecting a scalar argument of the passed type, an
   * exception is thrown.
   *
   * T must be int or float.
   */
  template <typename T>
  void add(T arg);

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
   * Access the signature being used to validate arguments.
   */
  props::signature const& signature() const;

  /**
   * Get a pointer to the raw argument data being stored, suitable for being
   * passed to a call wrapper function.
   */
  uint8_t* args();

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
  std::vector<std::vector<int>> int_data_ = {};
  std::vector<std::vector<float>> float_data_ = {};
};

struct output_example {
  uint64_t return_value;
  call_builder output_args;
};

template <typename T>
void call_builder::add(T arg)
{
  using Base = std::decay_t<T>;
  static_assert((std::is_same_v<Base, int> || std::is_same_v<Base, float>)&&!std::is_pointer_v<Base>,
      "Must be int or float and not pointer!");

  if (current_arg_ >= signature_.parameters.size()) {
    throw call_builder_error("Parameter list is already full");
  }

  auto param = signature_.parameters.at(current_arg_);

  if (std::is_same_v<Base, int> && (param.type != props::data_type::integer)) {
    throw call_builder_error("Adding non-integer when integer expected");
  }

  if (std::is_same_v<Base, float> && (param.type != props::data_type::floating)) {
    throw call_builder_error("Adding non-float when float expected");
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
  static_assert(std::is_same_v<T, int> || std::is_same_v<T, float>,
      "Pointed-to data must be of base type");

  assert(current_arg_ < signature_.parameters.size());

  auto param = signature_.parameters.at(current_arg_);

  if constexpr (std::is_same_v<T, int>) {
    assert(param.type == props::data_type::integer);
  }

  if constexpr (std::is_same_v<T, float>) {
    assert(param.type == props::data_type::floating);
  }

  assert(param.pointer_depth == 1);

  void* data = nullptr;
  if constexpr (std::is_same_v<T, int>) {
    int_data_.push_back(arg);
    data = int_data_.back().data();
  } else if constexpr (std::is_same_v<T, float>) {
    float_data_.push_back(arg);
    data = float_data_.back().data();
  }

  assert((data || arg.empty()) && "Something very wrong inside vector building!");

  for (auto i = 0u; i < sizeof(data); ++i) {
    args_.push_back(detail::nth_byte(data, i));
  }

  current_arg_++;
}
}
