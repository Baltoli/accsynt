#pragma once

#include <llvm/IR/Value.h>

#include <set>

namespace support {

template <typename Container>
std::set<llvm::Value *> with_type(llvm::Type *type, Container&& c)
{
  auto ret = std::set<llvm::Value *>{};
  for(auto instr : c) {
    if(instr->getType() == type) {
      ret.insert(instr);
    }
  }
  return ret;
}

template <typename Container>
std::set<llvm::Type *> all_types(Container&& c)
{
  auto ret = std::set<llvm::Type *>{};
  for(auto instr : c) {
    ret.insert(instr->getType());
  }
  return ret;
}

}
