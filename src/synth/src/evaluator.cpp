#include "evaluator.h"

#include <support/call_wrapper.h>
#include <support/similarity.h>

namespace synth {

eval_result::eval_result(double s)
    : eval_result(s, false)
{
}

eval_result::eval_result(double s, bool c)
    : score(s)
    , all_correct(c)
{
}

evaluator::evaluator(example_set es)
    : examples_(es)
{
}

eval_result evaluator::operator()(support::call_wrapper& func)
{
  double total_score = 0;
  bool all = true;

  for (auto const& [in, out] : examples_) {
    auto call_in = in;
    auto call_ret = func.call(call_in);

    auto score = support::similarity(
        call_ret, call_in, out.return_value, out.output_args);

    total_score += score;
    if (score < 1.0) {
      all = false;
    }
  }

  total_score /= examples_.size();
  return eval_result(total_score, all);
}

// Comparison operator overloads for evaluation results.

bool eval_result::operator==(eval_result const& o)
{
  return all_correct == o.all_correct && score == o.score;
}

bool eval_result::operator!=(eval_result const& o) { return !(*this == o); }

bool eval_result::operator<(eval_result const& o)
{
  if (all_correct) {
    return o.all_correct && score < o.score;
  } else {
    return o.all_correct || score < o.score;
  }
}

bool eval_result::operator<=(eval_result const& o)
{
  return (*this < o) || (*this == o);
}

bool eval_result::operator>(eval_result const& o) { return !(*this <= o); }

bool eval_result::operator>=(eval_result const& o)
{
  return (*this > o) || (*this == o);
}

} // namespace synth
