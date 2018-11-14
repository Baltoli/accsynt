#include "match.h"

#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/Support/raw_ostream.h>

#include <map>

using namespace llvm;

// Custom compare gets rid of constants if I need to - pass to std::less unless
// they're both constants, in which case make sure they're not the exact same
// value. Maybe don't need that
using indices_t = std::map<Value const*, size_t>;

indices_t get_indices(Function const& fn)
{
  auto inds = indices_t{};
  auto counter = 0u;

  for(auto const& arg : fn.args()) {
    inds[&arg] = counter++;
  }

  for(auto const& BB : fn) {
    for(auto const& I : BB) {
      inds[&I] = counter++;
      for(auto const& o : I.operands()) {
        if(auto cst = dyn_cast<Constant>(&o)) {
          inds[cst] = counter++;
        }
      }
    }
  }

  return inds;
}

::Instruction instr_type(Value const& v)
{
  if(isa<Argument>(&v)) {
    return ::Instruction::param;
  }

  if(isa<Constant>(&v)) {
    return ::Instruction::cnst;
  }

  if(auto inst = dyn_cast<llvm::Instruction>(&v)) {
    switch(inst->getOpcode()) {
    case llvm::Instruction::ICmp:           return ::Instruction::icmp;
    case llvm::Instruction::Br:             return ::Instruction::br;
    case llvm::Instruction::PHI:            return ::Instruction::phi;
    case llvm::Instruction::Add:            return ::Instruction::add;
    case llvm::Instruction::Mul:            return ::Instruction::mul;
    case llvm::Instruction::ZExt:           return ::Instruction::zext;
    case llvm::Instruction::GetElementPtr:  return ::Instruction::gep;
    case llvm::Instruction::Load:           return ::Instruction::load;
    case llvm::Instruction::FMul:           return ::Instruction::fmul;
    case llvm::Instruction::FAdd:           return ::Instruction::fadd;
    case llvm::Instruction::FSub:           return ::Instruction::fsub;
    case llvm::Instruction::Ret:            return ::Instruction::ret;
    }
  }

  assert(false && "Bad instruction type");
}

Graph from_function(Function const& fn)
{
  auto nodes = std::vector<Node>{};
  auto indices = get_indices(fn);

  for(auto i = 0u; i < indices.size(); ++i) {
  }

  return { nodes };
}
