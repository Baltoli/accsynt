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
  properties_.for_each_named("size", [this] (auto const& prop) {
    // TODO: validate before building size map
    auto ptr_name = prop.values.at(0).param_val;
    auto size_name = prop.values.at(1).param_val;
    
    auto const& sig = properties_.type_signature;
    auto ptr_index = sig.param_index(ptr_name);
    auto size_index = sig.param_index(size_name);
  });
}

void blas_generator::generate(call_builder& builder)
{
  throw std::runtime_error("Not yet implemented");
}

size_t blas_generator::random_size()
{
  auto dis = std::uniform_int_distribution<size_t>(0, max_size_);
  return dis(random_);
}

}
