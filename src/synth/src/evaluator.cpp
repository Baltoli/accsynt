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

} // namespace synth
