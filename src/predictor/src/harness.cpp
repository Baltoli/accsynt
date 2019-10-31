#include "internal.h"
#include "prepare_data.h"

#include <model/model.h>

#include <props/props.h>

#include <fmt/format.h>

namespace model {

std::set<std::string> input_keys()
{
  auto ret = std::set<std::string>{};

  for (auto i = 0; i < n_keys; ++i) {
    ret.insert(keys[i]);
  }

  return ret;
}

int prop_category(std::string const& str)
{
  return map_name(str.c_str());
}

props::property_set predict(props::property_set ps)
{
  ps.properties.clear();

  auto in = predict::example(prop_category, ps).model_input();
  fmt::print("{}\n", fmt::join(in, ","));

  auto uses = predict_out_uses_output(in.data());
  auto out_0 = predict_out_output_0_arg(in.data());
  auto out_1 = predict_out_output_1_arg(in.data());

  fmt::print("{}\n", ps);
  fmt::print("Outputs: {}, {}, {}\n", uses, out_0, out_1);

  return ps;
}

}
