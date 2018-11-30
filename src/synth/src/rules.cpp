#include "rules.h"

namespace synth {

match_result::match_result(std::map<std::string, props::value> rs) :
  results_(rs)
{
}

std::optional<match_result> match_result::unify_with(match_result const& other)
{
  auto map = results_;
  for(auto [name, val] : other.results_) {
    if(map.find(name) != map.end()) {
      if(map.at(name) != val) {
        return std::nullopt;
      }
    } else {
      map.emplace(name, val);
    }
  }

  return match_result{map};
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
