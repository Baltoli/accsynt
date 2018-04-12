#pragma once

#include <dist/synth.h>

namespace accsynt {

template <typename R, typename... Args>
class Loop : public Synthesizer<R, Args...> {
public:
  Loop(R r, Args... args) : Synthesizer<R, Args...>(r, args...) {}
  using Synthesizer<R, Args...>::operator();

private:
  std::unique_ptr<llvm::Module> generate_candidate(bool&) override;
};

template <typename R, typename... Args>
std::unique_ptr<llvm::Module> Loop<R, Args...>::generate_candidate(bool&)
{
  return nullptr;
}

}
