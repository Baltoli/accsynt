#include "generator.h"

using namespace props;

namespace synth {

generator::generator(property_set ps) :
  properties_(ps)
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

}
