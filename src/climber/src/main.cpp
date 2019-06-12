#include <fmt/format.h>

#include <llvm/IR/Module.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

#include <props/props.h>
#include <support/call_wrapper.h>
#include <support/similarity.h>
#include <support/thread_context.h>

using namespace props;
using namespace support;
using namespace llvm;

void map_mul(int n, float v, float* xs)
{
  for (int i = 0; i < n; ++i) {
    xs[i] *= v;
  }
}

void map_add(int n, float v, float* xs)
{
  for (int i = 0; i < n; ++i) {
    xs[i] += v;
  }
}

int main()
{
  using namespace props::literals;

  InitializeNativeTarget();
  LLVMInitializeNativeAsmPrinter();
  LLVMInitializeNativeAsmParser();

  auto sig = "void func(int n, float v, float *xs)"_sig;
  auto mod = Module("test_mod", thread_context::get());

  auto mul = call_wrapper(sig, mod, "map_mul", map_mul);
  auto add = call_wrapper(sig, mod, "map_add", map_add);

  auto m_b = mul.get_builder();
  auto a_b = add.get_builder();

  m_b.add(5, 2.0f, std::vector<float>{ 1, 2, 3, 4, 5 });
  a_b.add(5, 2.0f, std::vector<float>{ 1, 2, 3, 4, 5 });

  auto r_m = mul.call(m_b);
  auto r_a = add.call(a_b);

  auto sim = similarity(r_m, m_b, r_a, a_b);
  fmt::print("{}\n", sim);

  /* auto ret = wrap.call(build); */
}
