#include "rules.h"

namespace synth {

std::vector<rule> rule_registry::all()
{
  using match = match_expression;

  // clang-format off
  return { 
    { "regularLoop", { "sz", "ptr" }, 
      { match("size", "ptr", "sz") },
      { negation("output", "ptr") } 
    },
    { "outputLoop", { "sz", "ptr" },
      { match("size", "ptr", "sz"), 
        match("output", "ptr") }, 
      {} 
    },
    { "regularLoop", { "sz", "ptrA", "ptrB" },
      { match("size", "ptrA", "sz"), 
        match("size", "ptrB", "sz") },
      { distinct("ptrA", "ptrB"), 
        negation("output", "ptrA") } 
    },
    { "outputLoop", { "sz", "ptrA", "ptrB" },
      { match("size", "ptrA", "sz"), 
        match("size", "ptrB", "sz"),
        match("output", "ptrA") },
      { distinct("ptrA", "ptrB") } 
    },
    { "regularLoop", { "sz", "ptrA", "ptrB", "ptrC" },
      { match("size", "ptrA", "sz"), 
        match("size", "ptrB", "sz"),
        match("size", "ptrC", "sz") },
      { distinct("ptrA", "ptrB", "ptrC"), 
        negation("output", "ptrA") } 
    },
    { "outputLoop", { "sz", "ptrA", "ptrB", "ptrC" },
      { match("size", "ptrA", "sz"), 
        match("size", "ptrB", "sz"),
        match("size", "ptrC", "sz"), 
        match("output", "ptrA") },
      { distinct("ptrA", "ptrB", "ptrC") } 
    } 
  };
  // clang-format on
}
}
