#pragma once

#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

#include <queue>
#include <set>

namespace support {

template <typename Container>
std::set<llvm::Value*> with_type(llvm::Type* type, Container&& c)
{
  auto ret = std::set<llvm::Value*>{};
  for (auto instr : c) {
    if (instr->getType() == type) {
      ret.insert(instr);
    }
  }
  return ret;
}

template <typename Container>
std::set<llvm::Type*> all_types(Container&& c)
{
  auto ret = std::set<llvm::Type*>{};
  for (auto instr : c) {
    ret.insert(instr->getType());
  }
  return ret;
}

std::set<llvm::Value*> all_uses(llvm::Value* v);

std::set<llvm::Value*> all_deps(llvm::Value* v);
std::set<llvm::Value*> all_deps(
    llvm::Value* v, std::vector<llvm::Value*> const& roots);

std::vector<llvm::Value*> topo_sort(std::set<llvm::Value*> const& vals);

llvm::Value* get_by_name(llvm::Function& fn, std::string name);
}
