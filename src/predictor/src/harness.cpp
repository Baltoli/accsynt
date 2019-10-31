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

  auto sizes = predict_out_num_sizes(in.data());
  auto outs = predict_out_num_outputs(in.data());

  fmt::print("{}\n", ps);
  fmt::print("Predicted: {} size, {} out\n", sizes, outs);

  return ps;
}

}
