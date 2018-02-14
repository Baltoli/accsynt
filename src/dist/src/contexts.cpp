#include <dist/contexts.h>

using llvm::LLVMContext;

ThreadContext& ThreadContext::instance()
{
  static ThreadContext instance;
  return instance;
}

LLVMContext& ThreadContext::get(std::thread::id id)
{
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
