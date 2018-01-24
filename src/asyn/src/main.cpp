#include <synth/generator.h>
#include <synth/oracle.h>
#include <synth/types.h>

#include <iostream>

#include <llvm/Support/raw_ostream.h>

int main()
{
  auto c = llvm::LLVMContext{};

  get_llvm_int<int>(c)->print(llvm::errs());

  Oracle<int, int> o([](auto i) {
    return i + 1;
  });

  auto a = Args{Hint(0)};

  for(int i = 0; i < 10; ++i) {
    std::get<0>(a.gens).set_hint(11 * i);

    auto r = o.positive(a);
    if(r) {
      std::cout << std::get<0>(r->input) << " " << r->output << '\n';
    }
  }
}
