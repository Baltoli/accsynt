#pragma once

#include <dist/utils.h>

#include <iostream>
#include <mutex>
#include <thread>

#define as_log(...) \
  do { \
    log_impl(__FILE__, __LINE__, __VA_ARGS__); \
  } while(0);

int readable_id(std::thread::id id);
std::mutex& global_log_mutex();

namespace accsynt {

bool tag_is_active(std::string_view tag);
std::string get_file_from_path(std::string path);

template <typename... Args>
decltype(auto) log_impl(std::string file, int line, std::string tag, Args... args)
{
  if(tag_is_active(tag)) {
    auto lock = std::scoped_lock{global_log_mutex()};

    auto id = std::this_thread::get_id();
    auto args_tuple = std::make_tuple(args...);

    std::cerr << "[" << "T" << readable_id(id) << ""
              << " " << get_file_from_path(file) << ":" << line 
              << "] ";

    for_each(args_tuple, [](auto&& arg) {
      std::cerr << arg << " ";
    });

    std::cerr << '\n';
  }
}

}
