#include <passes/passes.h>

#include <iterator>
#include <numeric>

using namespace llvm;

Count::Count()
    : FunctionPass(ID)
    , count_(0)
{
}

bool Count::runOnFunction(Function& F)
{
  count_ = std::accumulate(
      F.begin(), F.end(), 0, [](auto const& acc, auto const& bb) {
        return acc + std::distance(bb.begin(), bb.end());
      });

  return false;
}

int Count::getCount() const { return count_; }

char Count::ID = 0;

static RegisterPass<Count>
    X("count", "Count the number of instructions in a function", true, true);

std::unique_ptr<Count> createCountPass() { return std::make_unique<Count>(); }
