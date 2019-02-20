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
  return all_deps(v, {});
}

std::set<Value *> all_deps(Value *v, std::vector<Value *> const& roots)
{
  auto work = std::queue<Value *>{};
  work.push(v);

  auto ret = std::set<Value *>{};
  while(!work.empty()) {
    auto dep = work.front();
    work.pop();

    if(auto user = dyn_cast<User>(dep)) {
      auto found = std::find(roots.begin(), roots.end(), dep);

      if(found == roots.end()) {
        for(auto& op : user->operands()) {
          work.push(op);
        }
      }
    }

    ret.insert(dep);
  }

  ret.erase(v);
  return ret;
}

namespace {

void visit(Value *v, std::set<Value *> const& vals, std::map<Value *, int>& marks, std::vector<Value *>& ret)
{
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
      if(vals.find(op) != vals.end()) {
        visit(op, vals, marks, ret);
      }
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
    for(auto v : vals) {
      marks.emplace(v, 0);
    }

    bool unmarked = true;
    while(unmarked) {
      unmarked = false;

      for(auto [v, mark] : marks) {
        if(mark == 0) {
          visit(v, vals, marks, ret);
        }
      }

      for(auto [v, mark] : marks) {
        if(mark == 0) {
          unmarked = true;
        }
      }
    }
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
