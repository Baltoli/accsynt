#include <dist/contexts.h>

#include <iostream>

using llvm::LLVMContext;

ThreadContext& ThreadContext::instance()
{
  static ThreadContext instance;
  return instance;
}

LLVMContext& ThreadContext::get()
{
  return get(std::this_thread::get_id());
}

LLVMContext& ThreadContext::get(std::thread::id id)
{
  std::lock_guard l{instance().map_mutex_};

  auto& m = instance().mapping_;

  if(m.find(id) == std::end(m)) {
    m[id] = std::make_unique<LLVMContext>();
  }

  return *m[id];
}

LLVMContext& ThreadContext::get(const std::thread& t)
{
  return get(t.get_id());
}
