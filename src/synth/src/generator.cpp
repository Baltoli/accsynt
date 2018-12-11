#include "generator.h"

#include <fmt/format.h>

using namespace props;

namespace synth {

/**
 *  Basic generator
 */

generator::generator(property_set ps) :
  properties_(ps), 
  rd_(), random_(rd_())
{
}

void generator::generate(call_builder& builder)
{
  for(auto param : properties_.type_signature.parameters) {
    generate_value(builder, param);
  }
}

void generator::generate_value(call_builder& builder,
                               props::param param)
{
  assert(param.pointer_depth < 2 &&   
         "Nested pointers not supported");

  if(param.pointer_depth == 0) {
    if(param.type == data_type::integer) {
      builder.add(random_int(0, 128));
    } else if(param.type == data_type::floating) {
      builder.add(random_float(-10, 10));
    }
  } else if(param.pointer_depth == 1) {
    if(param.type == data_type::integer) {
      builder.add(random_int_data(16 * 16 * 4, -128, 128));
    } else if(param.type == data_type::floating) {
      builder.add(random_float_data(16 * 16 * 4, -10, 10));
    }
  }
}

int generator::random_int(int min, int max)
{
  auto dis = std::uniform_int_distribution<int>(min, max);
  return dis(random_);
}

float generator::random_float(float min, float max)
{
  auto dis = std::uniform_real_distribution<float>(min, max);
  return dis(random_);
}

std::vector<float>
generator::random_float_data(int length, float min, float max)
{
  auto ret = std::vector<float>(length, 0.0f);
  std::generate(ret.begin(), ret.end(), [&] { return random_float(min, max); });
  return ret;
}

std::vector<int>
generator::random_int_data(int length, int min, int max)
{
  auto ret = std::vector<int>(length, 0);
  std::generate(ret.begin(), ret.end(), [&] { return random_int(min, max); });
  return ret;
}

/*
 *  BLAS-specific generator
 */

blas_generator::blas_generator(props::property_set ps) :
  generator(ps), blas_props_(ps), sizes_()
{
}

void blas_generator::create_next_sizes()
{
  sizes_.clear();

  for(auto [ptr_idx, size_idx] : blas_props_.loop_sizes()) {
    if(sizes_.find(size_idx) == sizes_.end()) {
      auto new_size_val = random_size();
      sizes_.insert({size_idx, new_size_val});
    }

    auto [p_it, p_ins] = sizes_.insert({ptr_idx, sizes_.at(size_idx)});
    if(!p_ins) {
      throw std::runtime_error("Invalid size specification for blas");
    }
  }
}

// TODO: check types more in this function
// TODO: sanity check the sizes_ map to make sure everything generated is OK?
void blas_generator::generate(call_builder& builder)
{
  create_next_sizes();

  auto const& params = properties_.type_signature.parameters;
  for(auto i = 0u; i < params.size(); ++i) {
    if(auto found = sizes_.find(i); found != sizes_.end()) {
      if(params.at(i).pointer_depth == 0) {
        builder.add(found->second);
      } else {
        builder.add(random_float_data(found->second * blas_props_.pack_size(i), -10, 10));
      }
    } else {
      generate_value(builder, params.at(i));
    }
  }
}

int blas_generator::random_size()
{
  auto dis = std::uniform_int_distribution<int>(0, max_size_);
  return dis(random_);
}

}
