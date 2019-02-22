#pragma once

#include "accessor.h"
#include "fragment.h"

#include <props/props.h>

#include <support/visitor.h>

#include <map>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace synth {

/**
 * Placeholder type that indicates we don't care about the value bound at this
 * position. It will be ignored when unifying names.
 */
struct ignore_value {
};

class rule;

/**
 * The set of all fragments known by the library. At the moment they need to be
 * registered manually by adding a mapping from string name to something
 * returning a fragment pointer.
 */
class fragment_registry {
  public:
  static std::unique_ptr<fragment> get(
      std::string const& name, std::vector<props::value> args);

  fragment_registry() = delete;
};

/**
 * Similar to the fragment registry, this class stores all the heuristic rules
 * known by the library. They must also be registered manually by adding them to
 * the definition of all().
 */
class rule_registry {
  public:
  static std::vector<rule> all();

  rule_registry() = delete;
};

/**
 * A match result represents the result of matching a single match expression
 * against a property set. A matching line from the property set will yield one
 * of these objects, which store a mapping from variable name to the value in
 * the property set.
 *
 * Unification checks whether the bindings in this result are consistent with
 * anegationher result: that is, where they bind the same name, are the bindings
 * to the same value?
 */
class match_result {
  public:
  match_result(std::map<std::string, props::value>);

  std::optional<match_result> unify_with(match_result const& other);

  template <typename Iterator>
  static std::optional<match_result> unify_all(Iterator begin, Iterator end);

  template <typename Container>
  static std::optional<match_result> unify_all(Container&& c);

  template <typename OStream>
  friend OStream& operator<<(OStream& os, match_result const& mr);

  std::optional<props::value> operator()(std::string) const;

  protected:
  std::map<std::string, props::value> results_;
};

/**
 * A match expression is one match(...) component in a rule. They comprise a
 * property name to match against, and a vector of binding rules to associate
 * variable names with values (or to ignore them).
 */
class match_expression {
  using binding_t = std::variant<std::string, ignore_value>;

  public:
  match_expression(std::string name, std::vector<binding_t> bs);

  template <typename... Args> match_expression(std::string name, Args... args);

  std::vector<match_result> match(props::property_set ps);

  template <typename OStream>
  friend OStream& operator<<(OStream& os, match_expression const& m);

  protected:
  std::string property_name_;
  std::vector<binding_t> bindings_;
};

class distinct {
  public:
  template <typename... Strings> distinct(Strings... vars);

  bool validate(match_result const& unified, props::property_set ps) const;

  private:
  std::set<std::string> vars_{};
};

class negation {
  public:
  template <typename... Args> negation(std::string name, Args... args);

  bool validate(match_result const& unified, props::property_set ps) const;

  private:
  std::string name_;
  std::vector<std::string> args_{};
};

using validator = std::variant<distinct, negation>;

/**
 * A rule has a fragment name and argument list. When unification succeeds, the
 * bound value corresponding to each argument is passed to the named fragment,
 * and a handle to an instantiated fragment is returned.
 */
class rule {
  public:
  rule(std::string fragment, std::vector<std::string> args,
      std::vector<match_expression> es, std::vector<validator> vs);

  std::vector<std::unique_ptr<fragment>> match(props::property_set ps);

  private:
  bool validate(match_result const& mr, props::property_set ps) const;

  std::string fragment_;
  std::vector<std::string> args_;
  std::vector<match_expression> exprs_;
  std::vector<validator> validators_;
};

// Template implementations

template <typename Iterator>
std::optional<match_result> match_result::unify_all(
    Iterator begin, Iterator end)
{
  if (begin == end) {
    return std::nullopt;
  }

  auto accum = std::optional<match_result>{ *begin };
  for (auto it = begin; it != end && accum; ++it) {
    accum = accum->unify_with(*it);
  }

  return accum;
}

template <typename Container>
std::optional<match_result> match_result::unify_all(Container&& c)
{
  using std::begin;
  using std::end;
  return unify_all(begin(c), end(c));
}

template <typename OStream>
OStream& operator<<(OStream& os, match_result const& mr)
{
  os << "{";
  auto comma = "";
  for (auto [name, val] : mr.results_) {
    os << comma << name << ": " << val;
    comma = ", ";
  }
  os << "}";

  return os;
}

template <typename... Args>
match_expression::match_expression(std::string name, Args... args)
    : match_expression(name, { args... })
{
}

template <typename OStream>
OStream& operator<<(OStream& os, match_expression const& m)
{
  auto bind_str = support::visitor{ [](std::string s) { return s; },
    [](ignore_value) { return std::string("_"); } };

  os << "match(" << m.property_name_;
  for (auto b : m.bindings_) {
    os << ", " << std::visit(bind_str, b);
  }
  os << ")";
  return os;
}

template <typename... Strings> distinct::distinct(Strings... vars)
{
  (vars_.insert(vars), ...);
}

template <typename... Args>
negation::negation(std::string name, Args... args)
    : name_(name)
{
  (args_.push_back(args), ...);
}
}
