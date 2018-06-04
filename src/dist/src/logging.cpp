#include <dist/logging.h>

std::mutex& global_log_mutex()
{
  static auto mut = std::mutex{};
  return mut;
}

namespace accsynt {

std::string get_file_from_path(std::string path)
{
  auto idx = path.find_last_of("/");
  return path.substr(idx+1);
}

}
