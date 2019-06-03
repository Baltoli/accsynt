#include <fmt/format.h>

#include <llvm/IR/Module.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

#include <props/props.h>
#include <support/call_wrapper.h>
#include <support/thread_context.h>

using namespace props;
using namespace support;
using namespace llvm;

int func(int x, int y) { return x * y; }
int func_2(int n, int* vs)
{
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    sum += vs[i];
  }
  return sum;
}

int main()
{
  using namespace props::literals;

  InitializeNativeTarget();
  LLVMInitializeNativeAsmPrinter();
  LLVMInitializeNativeAsmParser();

  auto sig = "int func(int x, int *ys)"_sig;
  auto mod = Module("test_mod", thread_context::get());
  auto wrap = call_wrapper(sig, mod, "func", func_2);

  auto build = wrap.get_builder();
  build.add(5, std::vector{ 1, 2, 3, 4, 5 });

  auto ret = wrap.call(build);
  fmt::print("{}\n", ret);
}
