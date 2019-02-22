#pragma once

#include <llvm/IR/LLVMContext.h>

#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>

namespace support {

class thread_context {
  public:
  thread_context(const thread_context&) = delete;
  void operator=(const thread_context&) = delete;

  static llvm::LLVMContext& get();
  static llvm::LLVMContext& get(std::thread::id id);
  static llvm::LLVMContext& get(const std::thread& t);

  private:
  thread_context()
      : mapping_{}
  {
  }

  static thread_context& instance();

  std::unordered_map<
      std::thread::id,
      std::unique_ptr<llvm::LLVMContext>>
      mapping_;

  std::mutex map_mutex_;
};
}
