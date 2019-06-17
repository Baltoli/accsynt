#pragma once

#include <support/call_builder.h>
#include <support/call_wrapper.h>

#include <variant>

namespace synth {

using example_set
    = std::vector<std::pair<support::call_builder, support::output_example>>;

struct eval_result {
  eval_result(double);
  eval_result(double, bool);

  double score;
  bool all_correct;
};

class evaluator {
public:
  evaluator(example_set);

  eval_result operator()(support::call_wrapper&);

private:
  example_set examples_;
};

} // namespace synth
