#include <support/llvm_values.h>

using namespace llvm;

namespace support {

std::set<Value *> all_uses(Value *v, bool ignore_stores)
{
  auto work = std::queue<Value *>{};
  work.push(v);

  auto ret = std::set<Value *>{};
  while(!work.empty()) {
    auto use = work.front();
    work.pop();

    if(ignore_stores && isa<StoreInst>(use)) {
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

llvm::Value *get_by_name(Function& fn, std::string name)
{
  for(auto& arg : fn.args()) {
    if(arg.getName() == name) {
      return &arg;
    }
  }

  for(auto& bb : fn) {
    for(auto& inst : bb) {
      if(inst.getName() == name) {
        return &inst;
      }
    }
  }

  return nullptr;
}

}
