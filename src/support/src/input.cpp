#include <support/input.h>

#include <readline/history.h>
#include <readline/readline.h>

#include <memory>

namespace support {

std::string get_line(std::string const& prompt)
{
  auto buf = std::unique_ptr<char, void (*)(void*)>(
      readline(prompt.c_str()), std::free);

  if (!buf) {
    return "";
  }

  auto str = std::string(buf.get());

  if (str.size() > 0) {
    add_history(str.c_str());
  }

  return str;
}

} // namespace support
