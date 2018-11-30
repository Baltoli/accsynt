#include "rules.h"

namespace synth {

match_result::match_result(std::map<std::string, props::value> rs) :
  results_(rs)
{
}

match_expression::match_expression(std::string name, std::vector<binding_t> bs) :
    property_name_(name), bindings_(bs)
{
}

std::vector<match_result> match_expression::match(props::property_set ps)
{
  return {{
    {
      {"a", props::value::with_param("hello")},
      {"b", props::value::with_int(10)}
    }
  }};
}

}
