#pragma once

#include <string>
#include <optional>
#include <vector>

namespace props {

enum class data_type {
  integer,
  floating
};

struct param {
  std::string name;
  int position;
  data_type type;
  int pointer_depth;
};

struct signature {
  std::optional<data_type> return_type;
  std::vector<param> parameters;
};

class property_set {
};

void test();

}
