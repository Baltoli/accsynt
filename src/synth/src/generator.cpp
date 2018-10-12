#include "generator.h"

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

void blas_generator::generate(call_builder& builder)
{
}

size_t blas_generator::random_size()
{
  auto dis = std::uniform_int_distribution<size_t>(0, max_size_);
  return dis(random_);
}

}
