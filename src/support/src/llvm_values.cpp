#include <support/llvm_values.h>

#include <stack>

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

std::set<Value *> all_deps(Value *v)
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

namespace {

void visit(Value *v, std::map<Value *, int>& marks, std::vector<Value *>& ret)
{
  marks.try_emplace(v, 0);

  // Permanently marked
  if(marks.at(v) == 1) {
    return;
  }

  // Temp. marked
  if(marks.at(v) == 2) {
    throw std::runtime_error("Graph is not a DAG");
  }

  marks.at(v) = 2;
  if(auto user_v = dyn_cast<User>(v)) {
    for(auto& op : user_v->operands()) {
      visit(op, marks, ret);
    }
  }
  marks.at(v) = 1;
  ret.push_back(v);
}

}

std::vector<Value *> topo_sort(std::set<Value *> const& vals)
{
  auto ret = std::vector<Value *>{};

  if(!vals.empty()) {
    auto marks = std::map<Value *, int>{};
    auto node = *vals.begin();

    visit(node, marks, ret);
  }

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
