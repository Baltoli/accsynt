#pragma once

#include "blas_properties.h"

#include <props/props.h>
#include <support/argument_generator.h>
#include <support/call_builder.h>

#include <cstdint>
#include <limits>
#include <map>
#include <random>

namespace synth {

/*
 * The initial generator implementation is just going to randomly generate the
 * values for the signature. However, the interface will accept a property_set
 * rather than just a signature so that the properties can be used during the
 * generation process (i.e. respecting fixed values, zeroing outputs etc).
 */
class generator {
public:
  generator(props::property_set ps);

  virtual void generate(support::call_builder& builder);

protected:
  virtual void
  generate_value(support::call_builder& builder, props::param param);

  int64_t random_int(
      int64_t min = std::numeric_limits<int64_t>::min(),
      int64_t max = std::numeric_limits<int64_t>::max());
  float random_float(
      float min = std::numeric_limits<float>::min(),
      float max = std::numeric_limits<float>::max());

  std::vector<float> random_float_data(
      int length, float min = std::numeric_limits<float>::min(),
      float max = std::numeric_limits<float>::max());

  std::vector<int64_t> random_int_data(
      int length, int64_t min = std::numeric_limits<int64_t>::min(),
      int64_t max = std::numeric_limits<int64_t>::max());

  props::property_set properties_;

protected:
  std::mt19937 random_;
};

class blas_generator : public generator {
public:
  blas_generator(props::property_set ps);

  void generate(support::call_builder& builder) override;

private:
  blas_properties blas_props_;

  size_t max_size_ = 16;
  std::map<size_t, int64_t> sizes_;

  void create_next_sizes();
  int64_t random_size();
};

template <typename Old>
struct gen_adaptor {
  gen_adaptor(Old og)
      : old_gen_(og)
  {
  }

  void gen_args(support::call_builder& b) { old_gen_.generate(b); }

private:
  Old old_gen_;
};

static_assert(
    support::detail::is_generator_v<gen_adaptor<generator>>,
    "Default generator should adapt to new interface");
static_assert(
    support::detail::is_generator_v<gen_adaptor<blas_generator>>,
    "BLAS generator should adapt to new interface");
} // namespace synth
