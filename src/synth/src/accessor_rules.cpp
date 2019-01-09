#include "accessor_rules.h"

#include <support/tuple.h>

namespace synth {

accessor_map accessors_from_rules(props::property_set ps)
{
  auto rules = std::tuple{
    accessor_rule<offset_accessor>("offset")
  };

  auto map = std::map<std::string, std::unique_ptr<accessor>>{};

  support::for_each(rules, [&] (auto rule) {
    for(auto prop : ps.properties) {
      if(auto opt_entry = rule(prop)) {
        __builtin_trap();
        map.insert(std::move(opt_entry.value()));
      }
    }
  });

  return map;
}

}
