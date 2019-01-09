#pragma once

#include "accessor.h"

#include <props/props.h>

#include <map>
#include <memory>
#include <string>

namespace synth {

/**
 * These simpler rules exist to match properties to accessors - they take a
 * single property name and return an accessor.
 */
template <typename Acc>
class accessor_rule {
public:
  accessor_rule(std::string property);

  std::unique_ptr<accessor> operator()(props::property p) const;

private:
  std::string property_;
};

template <typename Acc>
accessor_rule<Acc>::accessor_rule(std::string property) :
  property_(property)
{
}

template <typename Acc>
std::unique_ptr<accessor> accessor_rule<Acc>::operator()(props::property p) const
{
  if(p.name == property_ && p.values.empty()) {
    return std::make_unique<Acc>();
  }

  return nullptr;
}

accessor_map accessors_from_rules(props::property_set ps);

}
