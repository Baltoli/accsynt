#include <synth/generator.h>
#include <synth/oracle.h>

#include <iostream>

int main()
{
  Oracle<int, int, int> o([](auto i, auto j) {
    return i + j;
  });

  auto a = Args{Sequential{}, Sequential{}};

  for(int i = 0; i < 10; ++i) {
    auto r = o.positive(a);
    std::cout << r << '\n';
  }
}
