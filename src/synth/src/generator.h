#pragma once

#include "blas_properties.h"
#include "call_builder.h"

#include <props/props.h>

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

  virtual void generate(call_builder& builder);

protected:
  virtual void generate_value(call_builder& builder,
                              props::param param);

  int random_int(int min = std::numeric_limits<int>::min(), 
                 int max = std::numeric_limits<int>::max());
  float random_float(float min = std::numeric_limits<float>::min(),
                     float max = std::numeric_limits<float>::max());

  props::property_set properties_;

private:
  std::random_device rd_;

protected:
  std::mt19937 random_;
};

class blas_generator : public generator {
public:
  blas_generator(props::property_set ps);

  void generate(call_builder& builder) override;

private:
  blas_properties blas_props_;

  size_t max_size_ = 128;
  std::map<size_t, int> sizes_;

  void create_next_sizes();
  int random_size();

  std::vector<float> random_float_data(
      int length,
      float min = std::numeric_limits<float>::min(),
      float max = std::numeric_limits<float>::max());
};

}
