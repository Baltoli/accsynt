#include "rules.h"

namespace synth {

std::vector<rule> rule_registry::all()
{
  using match = match_expression;

  return {
    {
      "regularLoop", {"ptr", "sz"},
      { match("size", "ptr", "sz") }
    }
  };
}

}
