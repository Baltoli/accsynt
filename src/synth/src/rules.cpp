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
  auto ret = std::vector<match_result>{};
  for(auto prop : ps.properties) {
    if(prop.name == property_name_) {
      auto mapping = std::map<std::string, props::value>{};
      if(prop.values.size() != bindings_.size()) {
        throw 2; // TODO: a real exception
      }

      for(auto i = 0u; i < prop.values.size(); ++i) {
        auto bind = bindings_.at(i);
        if(std::holds_alternative<std::string>(bind)) {
          mapping.emplace(std::get<std::string>(bind), prop.values.at(i));
        }
      }

      ret.push_back(match_result{mapping});
    }
  }

  return ret;
}

}
