#include "internal.h"
#include "prepare_data.h"

#include <model/model.h>

#include <props/props.h>

#include <fmt/format.h>

namespace model {

int prop_category(std::string const& str)
{
  return map_name(str.c_str());
}

props::property_set predict(props::property_set ps)
{
  ps.properties.clear();

  auto in = predict::example(prop_category, ps).model_input();
  fmt::print("{}\n", fmt::join(in, ","));

  auto out_0 = predict_out_output_0_arg(in.data());
  auto out_1 = predict_out_output_1_arg(in.data());

  fmt::print("{}\n", ps);
  fmt::print("Outputs: {}, {}\n", out_0, out_1);

  return ps;
}

}
