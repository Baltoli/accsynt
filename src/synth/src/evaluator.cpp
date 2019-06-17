#include "evaluator.h"

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

eval_result evaluator::operator()(support::call_wrapper&)
{
  return eval_result(0.0);
}

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

bool eval_result::operator>(eval_result const& o)
{
  if (all_correct) {
    return !o.all_correct || score > o.score;
  } else {
    return !o.all_correct && score > o.score;
  }
}

bool eval_result::operator>=(eval_result const& o)
{
  return (*this > o) || (*this == o);
}

} // namespace synth
