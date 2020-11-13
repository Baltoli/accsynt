#include <passes/passes.h>

using namespace llvm;

Count::Count()
    : FunctionPass(ID)
    , count_(0)
{
}

bool Count::runOnFunction(Function& F)
{
  count_ = 0;

  for (auto& bb : F) {
    for (auto& inst : bb) {
      ++count_;
    }
  }

  return false;
}

int Count::getCount() const { return count_; }

char Count::ID = 0;

static RegisterPass<Count>
    X("count", "Count the number of instructions in a function", true, true);

std::unique_ptr<Count> createCountPass() { return std::make_unique<Count>(); }
