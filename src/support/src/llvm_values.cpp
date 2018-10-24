#include <support/llvm_values.h>

using namespace llvm;

namespace support {

std::set<Value *> all_uses(Value *v)
{
  auto work = std::queue<Value *>{};
  work.push(v);

  auto ret = std::set<Value *>{};
  while(!work.empty()) {
    auto use = work.front();
    work.pop();
    if(isa<StoreInst>(use)) {
      continue;
    }

    auto [it, inserted] = ret.insert(use);
    if(inserted) {
      for(auto user : use->users()) {
        work.push(user);
      }
    }
  }

  ret.erase(v);
  return ret;
}

}
