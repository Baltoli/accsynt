#include <support/thread_context.h>

using namespace llvm;

namespace support {

thread_context& thread_context::instance()
{
  static thread_context instance;
  return instance;
}

LLVMContext& thread_context::get(std::thread::id id)
{
  std::lock_guard l{ instance().map_mutex_ };

  auto& m = instance().mapping_;

  if (m.find(id) == std::end(m)) {
    m[id] = std::make_unique<LLVMContext>();
  }

  return *m[id];
}

LLVMContext& thread_context::get()
{
  return get(std::this_thread::get_id());
}

LLVMContext& thread_context::get(const std::thread& t)
{
  return get(t.get_id());
}
}
