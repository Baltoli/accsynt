#pragma once

#include <llvm/IR/LLVMContext.h>

#include <unordered_map>
#include <memory>
#include <mutex>
#include <thread>

class ThreadContext {
public:
  ThreadContext(const ThreadContext&) = delete;
  void operator=(const ThreadContext&) = delete;

  static llvm::LLVMContext& get();
  static llvm::LLVMContext& get(std::thread::id id);
  static llvm::LLVMContext& get(const std::thread& t);

private:
  ThreadContext() : 
    mapping_{}
  {}

  static ThreadContext& instance();

  std::unordered_map<
    std::thread::id, 
    std::unique_ptr<llvm::LLVMContext>
  > mapping_;

  std::mutex map_mutex_;
};
