#include "rules.h"
#include "regular_loop_fragment.h"

#include <support/cartesian_product.h>

#include <iostream>

using namespace support;

namespace synth {

match_result::match_result(std::map<std::string, props::value> rs)
    : results_(rs)
{
}

std::optional<match_result> match_result::unify_with(match_result const& other)
{
  auto map = results_;
  for (auto [name, val] : other.results_) {
    if (map.find(name) != map.end()) {
      if (map.at(name) != val) {
        return std::nullopt;
      }
    } else {
      map.emplace(name, val);
    }
  }

  return match_result{ map };
}

std::optional<props::value> match_result::operator()(std::string name) const
{
  if (results_.find(name) != results_.end()) {
    return results_.at(name);
  } else {
    return std::nullopt;
  }
}

match_expression::match_expression(std::string name, std::vector<binding_t> bs)
    : property_name_(name)
    , bindings_(bs)
{
}

std::vector<match_result> match_expression::match(props::property_set ps)
{
  auto ret = std::vector<match_result>{};
  for (auto prop : ps.properties) {
    if (prop.name == property_name_) {
      auto mapping = std::map<std::string, props::value>{};
      if (prop.values.size() != bindings_.size()) {
        throw 2; // TODO: a real exception
      }

      for (auto i = 0u; i < prop.values.size(); ++i) {
        auto bind = bindings_.at(i);
        if (std::holds_alternative<std::string>(bind)) {
          mapping.emplace(std::get<std::string>(bind), prop.values.at(i));
        }
      }

      ret.push_back(match_result{ mapping });
    }
  }

  return ret;
}

bool distinct::validate(
    match_result const& unified, props::property_set ps) const
{
  for (auto v1 : vars_) {
    for (auto v2 : vars_) {
      if (v1 != v2 && unified(v1) == unified(v2)) {
        return false;
      }
    }
  }

  return true;
}

bool negation::validate(
    match_result const& unified, props::property_set ps) const
{
  auto vals = std::vector<props::value>{};

  for (auto arg : args_) {
    if (auto val = unified(arg)) {
      vals.push_back(*val);
    } else {
      return true;
    }
  }

  for (auto prop : ps.properties) {
    if (prop.name == name_ && prop.values == vals) {
      return false;
    }
  }

  return true;
}

rule::rule(std::string frag, std::vector<std::string> args,
    std::vector<match_expression> es, std::vector<validator> vs)
    : fragment_(frag)
    , args_(args)
    , exprs_(es)
    , validators_(vs)
{
}

std::vector<value_ptr<fragment>> rule::match(props::property_set ps)
{
  auto ret = std::vector<value_ptr<fragment>>{};

  auto elements = std::vector<std::vector<match_result>>{};
  for (auto expr : exprs_) {
    elements.push_back(expr.match(ps));
  }

  for (auto prod : support::cartesian_product(elements)) {
    auto unified = match_result::unify_all(prod);
    if (unified) {
      if (validate(*unified, ps)) {
        auto call_args = std::vector<props::value>{};

        for (auto arg_name : args_) {
          if (auto val = (*unified)(arg_name)) {
            call_args.push_back(*val);
          } else {
            throw 3; // TODO: a real exception
          }
        }

        auto frag = fragment_registry::get(fragment_, call_args);
        ret.push_back(frag);
      }
    }
  }

  return ret;
}

bool rule::validate(match_result const& mr, props::property_set ps) const
{
  auto call_valid = [&](auto v) { return v.validate(mr, ps); };

  return std::all_of(validators_.begin(), validators_.end(),
      [&](auto v) { return std::visit(call_valid, v); });
}
}
