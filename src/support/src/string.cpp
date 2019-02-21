#include <support/string.h>

#include <algorithm>

namespace support {

std::string left_trim(std::string s)
{
  auto not_space = std::find_if(s.begin(), s.end(), [] (auto c) {
    return !std::isspace(c);
  });

  s.erase(s.begin(), not_space);
  return s;
}

}
