#pragma once

#include <iostream>
#include <mutex>

#define as_log(...) \
  do { \
    log_impl(__FILE__, __LINE__)(); \
  } while(0);

std::mutex& global_log_mutex();

namespace accsynt {

std::string get_file_from_path(std::string path);

template <typename... Args>
decltype(auto) log_impl(std::string file, int line)
{
  return [file,line] (auto&&... args) {
    std::cerr << "[" << get_file_from_path(file) << ":" << line << "]" << '\n';
  };
}

}
