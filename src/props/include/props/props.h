#pragma once

#include <iosfwd>
#include <string>
#include <string_view>
#include <optional>
#include <vector>

// TODO: abstract parser state from PODs used for domain

namespace props {

struct property_set;

enum class data_type {
  integer,
  floating
};

struct param {
  std::string name;
  data_type type;
  int pointer_depth;
};

struct signature {
  signature() = default;

  std::optional<data_type> return_type;
  std::string name;
  std::vector<param> parameters;

  static signature parse(std::string_view str);

  template <typename Input>
  void success(Input const& in, property_set& parent);

  template <typename Input>
  signature(Input const& in, property_set& parent) {}
};

struct property_set {
  signature sig;

  static property_set parse(std::string_view str);
};

std::ostream& operator <<(std::ostream& os, const data_type& dt);
std::ostream& operator <<(std::ostream& os, const param& p);
std::ostream& operator <<(std::ostream& os, const signature& sig);

template <typename Input>
void signature::success(Input const& in, property_set& parent)
{
  parent.sig = *this;
}

}
