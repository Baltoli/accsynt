#include <holes/holes.h>

#include <support/thread_context.h>

#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Type.h>

#include <unordered_map>

using namespace llvm;

namespace holes {

Type* get_hole_type(LLVMContext& ctx)
{
  static auto holes = std::unordered_map<LLVMContext*, Type*> {};
  if (holes.find(&ctx) == holes.end()) {
    holes[&ctx] = StructType::create(ctx, "hole");
  }

  return holes.at(&ctx);
}

Type* get_hole_type() { return get_hole_type(support::thread_context::get()); }

} // namespace holes
