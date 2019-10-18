#include "rules.h"

using namespace props;

namespace synth {

std::vector<rule> rule_registry::all()
{
  using match = property_expression;
  using type = type_expression;
  using wildcard = wildcard_expression;

  // clang-format off
  return { 
    { "regularLoop", { "sz", "ptr" }, 
      { match("size", "ptr", "sz"),
        type ("sz", data_type::integer) },
      { negation("output", "ptr"),
        is_pointer("ptr") } 
    },
    { "outputLoop", { "sz", "ptr" },
      { match("size", "ptr", "sz"), 
        match("output", "ptr"),
        type( "sz", data_type::integer) }, 
      { is_pointer("ptr") } 
    },
    { "regularLoop", { "sz", "ptrA", "ptrB" },
      { match("size", "ptrA", "sz"), 
        match("size", "ptrB", "sz"),
        type ("sz", data_type::integer) },
      { distinct("ptrA", "ptrB"), 
        negation("output", "ptrA"),
        is_pointer("ptrA", "ptrB") }
    },
    { "outputLoop", { "sz", "ptrA", "ptrB" },
      { match("size", "ptrA", "sz"), 
        match("size", "ptrB", "sz"),
        match("output", "ptrA"),
        type ("sz", data_type::integer) },
      { distinct("ptrA", "ptrB"),
        is_pointer("ptrA", "ptrB") } 
    },
    { "regularLoop", { "sz", "ptrA", "ptrB", "ptrC" },
      { match("size", "ptrA", "sz"), 
        match("size", "ptrB", "sz"),
        match("size", "ptrC", "sz"),
        type ("sz", data_type::integer) },
      { distinct("ptrA", "ptrB", "ptrC"), 
        is_pointer("ptrA", "ptrB", "ptrC"),
        negation("output", "ptrA") } 
    },
    { "outputLoop", { "sz", "ptrA", "ptrB", "ptrC" },
      { match("size", "ptrA", "sz"), 
        match("size", "ptrB", "sz"),
        match("size", "ptrC", "sz"), 
        match("output", "ptrA"),
        type ("sz", data_type::integer) },
      { distinct("ptrA", "ptrB", "ptrC"),
        is_pointer("ptrA", "ptrB", "ptrC") }
    },
    {
      "dataLoop", {"ptr"},
      { match("data_ptr", "ptr") },
      { is_pointer("ptr") }
    },
    {
      "dataLoop", {"ptrA", "ptrB"},
      { match("data_ptr", "ptrA"),
        match("data_ptr", "ptrB") },
      { distinct("ptrA", "ptrB"),
        is_pointer("ptrA", "ptrB") }
    },
    {
      "stringLoop", {"str"},
      { type ("str", data_type::character) },
      { is_pointer("str") }
    },
    {
      "affineAccess", {"ptr"},
      { wildcard("ptr") },
      { is_pointer("ptr") }
    },
    {
      "loopToN", {"val"},
      { type("val", data_type::integer),
        wildcard("ptr") },
      { negation("size", "ptr", "val") }
    }
  };
  // clang-format on
}

} // namespace synth
