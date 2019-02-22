#pragma once

#include "accessor.h"

#include <props/props.h>

#include <map>
#include <memory>
#include <optional>
#include <string>
#include <utility>

namespace synth {

/**
 * These simpler rules exist to match properties to accessors - they take a
 * single property name and return an accessor.
 */
template <typename Acc> class accessor_rule {
  using optional_entry
      = std::optional<std::pair<std::string, std::unique_ptr<accessor>>>;

  public:
  accessor_rule(std::string property);

  optional_entry operator()(props::property p) const;

  private:
  std::string property_;
};

template <typename Acc>
accessor_rule<Acc>::accessor_rule(std::string property)
    : property_(property)
{
}

template <typename Acc>
typename accessor_rule<Acc>::optional_entry accessor_rule<Acc>::operator()(
    props::property p) const
{
  // TODO: validate that this is actually a parameter reference

  if (p.name == property_ && p.values.size() == 1) {
    return std::pair{ p.values.at(0).param_val, std::make_unique<Acc>() };
  }

  return std::nullopt;
}

accessor_map accessors_from_rules(props::property_set ps);
}
