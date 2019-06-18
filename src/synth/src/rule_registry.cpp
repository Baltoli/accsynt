#include "rules.h"

using namespace props;

namespace synth {

std::vector<rule> rule_registry::all()
{
  using match = property_expression;
  using type = type_expression;

  // clang-format off
  return { 
    { "regularLoop", { "sz", "ptr" }, 
      { match("size", "ptr", "sz"),
        type ("sz", data_type::integer) },
      { negation("output", "ptr") } 
    },
    { "outputLoop", { "sz", "ptr" },
      { match("size", "ptr", "sz"), 
        match("output", "ptr"),
        type( "sz", data_type::integer) }, 
      {} 
    },
    { "regularLoop", { "sz", "ptrA", "ptrB" },
      { match("size", "ptrA", "sz"), 
        match("size", "ptrB", "sz"),
        type ("sz", data_type::integer) },
      { distinct("ptrA", "ptrB"), 
        negation("output", "ptrA") } 
    },
    { "outputLoop", { "sz", "ptrA", "ptrB" },
      { match("size", "ptrA", "sz"), 
        match("size", "ptrB", "sz"),
        match("output", "ptrA"),
        type ("sz", data_type::integer) },
      { distinct("ptrA", "ptrB") } 
    },
    { "regularLoop", { "sz", "ptrA", "ptrB", "ptrC" },
      { match("size", "ptrA", "sz"), 
        match("size", "ptrB", "sz"),
        match("size", "ptrC", "sz"),
        type ("sz", data_type::integer) },
      { distinct("ptrA", "ptrB", "ptrC"), 
        negation("output", "ptrA") } 
    },
    { "outputLoop", { "sz", "ptrA", "ptrB", "ptrC" },
      { match("size", "ptrA", "sz"), 
        match("size", "ptrB", "sz"),
        match("size", "ptrC", "sz"), 
        match("output", "ptrA"),
        type ("sz", data_type::integer) },
      { distinct("ptrA", "ptrB", "ptrC") }
    },
    {
      "dataLoop", {"ptr"},
      { match("data_ptr", "ptr") },
      {}
    },
    {
      "dataLoop", {"ptrA", "ptrB"},
      { match("data_ptr", "ptrA"),
        match("data_ptr", "ptrB") },
      { distinct("ptrA", "ptrB") }
    },
    {
      "stringLoop", {"str"},
      { type ("str", data_type::character) },
      {}
    }
  };
  // clang-format on
}
} // namespace synth
