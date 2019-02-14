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

std::set<llvm::Value *> all_deps(llvm::Value *v)
{
  auto work = std::queue<Value *>{};
  work.push(v);

  auto ret = std::set<Value *>{};
  while(!work.empty()) {
    auto dep = work.front();
    work.pop();

    if(auto user = dyn_cast<User>(dep)) {
      for(auto& op : user->operands()) {
        work.push(op);
      }
    }

    ret.insert(dep);
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
