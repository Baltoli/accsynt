#pragma once

#include <iosfwd>
#include <string>
#include <string_view>
#include <optional>
#include <vector>

namespace props {

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
  std::optional<data_type> return_type;
  std::string name;
  std::vector<param> parameters;

  static signature parse(std::string_view str);
};

class property_set {
};

void test();

std::ostream& operator <<(std::ostream& os, const data_type& dt);
std::ostream& operator <<(std::ostream& os, const param& p);
std::ostream& operator <<(std::ostream& os, const signature& sig);

}
