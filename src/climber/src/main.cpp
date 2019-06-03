#include <fmt/format.h>

#include <props/props.h>
#include <support/call_wrapper.h>

int func(int x, int y) { return x + y; }

int main()
{
  using namespace props::literals;
  auto sig = "int func(int x, int y)"_sig;

  auto wrap = support::call_wrapper(sig, func);
}
