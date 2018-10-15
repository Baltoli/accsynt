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
      builder.add(34);
    } else if(param.type == data_type::floating) {
      builder.add(0.0f);
    }
  } else if(param.pointer_depth == 1) {
    if(param.type == data_type::integer) {
      builder.add(std::vector<int>{1});
    } else if(param.type == data_type::floating) {
      builder.add(std::vector<float>{1.0f});
    }
  }
}

int generator::random_int(int min, int max)
{
  auto dis = std::uniform_int_distribution<int>(min, max);
  return dis(random_);
}


/*
 *  BLAS-specific generator
 */

blas_generator::blas_generator(props::property_set ps) :
  generator(ps), sizes_()
{
}

// This design can probably be made a lot more efficient - if it turns out to be
// a performance killer then the best idea is probably to cache some size pairs
// in the constructor then regenerate from that rather than from the properties
// directly. For now it seems to work so leaving it as is.
void blas_generator::create_next_sizes()
{
  sizes_.clear();

  properties_.for_each_named("size", [this] (auto const& prop) {
    // TODO: validate before building size map
    auto ptr_name = prop.values.at(0).param_val;
    auto size_name = prop.values.at(1).param_val;
    
    auto const& sig = properties_.type_signature;
    auto ptr_index = sig.param_index(ptr_name);
    auto size_index = sig.param_index(size_name);

    auto size = random_size();
    auto [p_it, p_ins] = sizes_.insert({ptr_index, size});
    auto [s_it, s_ins] = sizes_.insert({size_index, size});

    if(!p_ins || !s_ins) {
      throw std::runtime_error("Invalid size specification for blas");
    }
  });
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
        builder.add(random_float_data(found->second, -100, 100));
      }
    }
  }
}

int blas_generator::random_size()
{
  auto dis = std::uniform_int_distribution<int>(0, max_size_);
  return dis(random_);
}

std::vector<float> 
blas_generator::random_float_data(int length, float min, float max)
{
  auto ret = std::vector<float>(length, 0.0f);
  auto dis = std::uniform_real_distribution<float>(min, max);
  std::generate(ret.begin(), ret.end(), [&] { return dis(random_); });
  return ret;
}

}
