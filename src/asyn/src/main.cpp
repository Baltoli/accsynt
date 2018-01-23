#include <synth/generator.h>
#include <synth/oracle.h>

#include <iostream>

int main()
{
  Oracle<int, int> o([](auto i) {
    return i + 1;
  });

  auto a = Args{Sequential{}};

  for(int i = 0; i < 10; ++i) {
    auto r = o.positive(a);
    std::cout << std::get<0>(r.input) << " " << r.output << '\n';
  }
}
