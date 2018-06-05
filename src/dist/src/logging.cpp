#include <dist/logging.h>

#include <unordered_map>

int readable_id(std::thread::id id)
{
  static std::unordered_map<std::thread::id, int> mapping = {};
  static int i = 0;

  if(mapping.find(id) == mapping.end()) {
    mapping.insert({id, i++});
  }

  return mapping.at(id);
}

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

bool prefix_match(std::string_view env_tag, std::string_view tag)
{
  return tag.find(env_tag) == 0;
}

bool tag_is_active(std::string_view tag)
{
  static bool set_up = false;
  static auto tags = std::vector<std::string>{};
  static bool wildcard = false;

  if(!set_up) {
    auto lock = std::scoped_lock{global_log_mutex()};

    auto env_var = std::getenv("ACCSYNT_LOG");
    if(env_var) {
      auto env_var_str = std::string(env_var);

      auto start = 0u;
      while(true) {
        auto end = env_var_str.find(",", start);
        auto substr = env_var_str.substr(start, end - start);

        if(!substr.empty()) {
          tags.push_back(substr);
        }

        if(substr == "*") {
          wildcard = true;
        }

        start = end + 1;

        if(end == std::string::npos) { break; }
      }
    }

    set_up = true;
  }

  return std::any_of(tags.begin(), tags.end(), [tag] (auto const& env_tag) {
    return wildcard || prefix_match(env_tag, tag);
  });
}

}
