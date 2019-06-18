#pragma once

#include <support/call_builder.h>
#include <support/call_wrapper.h>

#include <variant>

namespace synth {

using example_set
    = std::vector<std::pair<support::call_builder, support::output_example>>;

struct eval_result {
  explicit eval_result(double);
  eval_result(double, bool);

  double score;
  bool all_correct;

  bool operator==(eval_result const&);
  bool operator!=(eval_result const&);
  bool operator<(eval_result const&);
  bool operator<=(eval_result const&);
  bool operator>(eval_result const&);
  bool operator>=(eval_result const&);
};

class evaluator {
public:
  evaluator(example_set);

  eval_result operator()(support::call_wrapper&) const;

private:
  example_set examples_;
};

} // namespace synth
