#pragma once

#include "fragment.h"

#include <props/props.h>

#include <support/visitor.h>

#include <map>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace synth {

struct ignore_value {};

struct fragment_registry {
  static std::unique_ptr<fragment> get(
      std::string const& name,
      std::vector<props::value> args);
};

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

  std::optional<props::value> operator()(std::string);

protected:
  std::map<std::string, props::value> results_;
};

class match_expression {
  using binding_t = std::variant<
    std::string,
    ignore_value
  >;

public:
  match_expression(std::string name, std::vector<binding_t> bs);

  template <typename... Args>
  match_expression(std::string name, Args... args);

  std::vector<match_result> match(props::property_set ps);

  template <typename OStream>
  friend OStream& operator<<(OStream& os, match_expression const& m);

protected:
  std::string property_name_;
  std::vector<binding_t> bindings_;
};

class rule {
public:
  rule(std::string fragment,
       std::vector<std::string> args,
       std::vector<match_expression> es);

  std::vector<std::unique_ptr<fragment>> match(props::property_set ps);

private:
  std::unique_ptr<fragment> instantiate(std::vector<props::value> args);

  std::string fragment_;
  std::vector<std::string> args_;
  std::vector<match_expression> exprs_;
};

template <typename Iterator>
std::optional<match_result> match_result::unify_all(Iterator begin, Iterator end)
{
  if(begin == end) {
    return std::nullopt;
  }

  auto accum = std::optional<match_result>{*begin};
  for(auto it = begin; it != end && accum; ++it) {
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
  for(auto [name, val] : mr.results_) {
    os << comma << name << ": " << val;
    comma = ", ";
  }
  os << "}";

  return os;
}

template <typename... Args>
match_expression::match_expression(std::string name, Args... args) :
  match_expression(name, {args...})
{
}

template <typename OStream>
OStream& operator<<(OStream& os, match_expression const& m)
{
  auto bind_str = support::visitor{
    [] (std::string s) { return s; },
    [] (ignore_value) { return std::string("_"); }
  };

  os << "match(" << m.property_name_;
  for(auto b : m.bindings_) {
    os << ", " << std::visit(bind_str, b);
  }
  os << ")";
  return os;
}

}
