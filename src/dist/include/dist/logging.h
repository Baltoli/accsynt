#pragma once

#include <dist/utils.h>

#include <llvm/Support/raw_ostream.h>

#include <iostream>
#include <mutex>
#include <thread>

#define as_log(...) \
  do { \
    log_impl(__FILE__, __LINE__, __VA_ARGS__); \
  } while(0);

namespace accsynt {

namespace detail {

bool tag_is_active(std::string_view tag);
std::string get_file_from_path(std::string path);
int readable_id(std::thread::id id);
std::mutex& global_log_mutex();

}

template <typename... Args>
decltype(auto) log_impl(std::string file, int line, std::string tag, Args&&... args)
{
  if(detail::tag_is_active(tag)) {
    auto lock = std::scoped_lock{detail::global_log_mutex()};

    auto id = std::this_thread::get_id();
    auto&& args_tuple = std::forward_as_tuple(args...);

    llvm::errs() << "[" << "T" << detail::readable_id(id) << ""
              << " " << detail::get_file_from_path(file) << ":" << line 
              << "] ";

    accsynt::for_each(args_tuple, [](auto&& arg) {
      llvm::errs() << std::forward<decltype(arg)>(arg) << " ";
    });

    llvm::errs() << '\n';
  }
}

}
