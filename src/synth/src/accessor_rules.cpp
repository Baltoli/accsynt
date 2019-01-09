#include "accessor_rules.h"

#include <support/tuple.h>

namespace synth {

auto rule_table()
{
  return std::tuple{
    accessor_rule<offset_accessor>("offset")
  };
}

accessor_map accessors_from_rules(props::property_set ps)
{
  auto rules = rule_table();
  auto map = std::map<std::string, std::unique_ptr<accessor>>{};

  support::for_each(rules, [&] (auto rule) {
    for(auto prop : ps.properties) {
      if(auto opt_entry = rule(prop)) {
        map.insert(std::move(opt_entry.value()));
      }
    }
  });

  return map;
}

}
