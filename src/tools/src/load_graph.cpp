#include "match.h"

#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/Support/raw_ostream.h>

#include <map>

using namespace llvm;

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
    case llvm::Instruction::Store:          return ::Instruction::store;
    }
  }

  assert(false && "Bad instruction type");
}

std::string instr_name(Value const& v)
{
  static int counter = 0;

  if(auto int_const = dyn_cast<ConstantInt>(&v)) {
    return std::to_string(int_const->getSExtValue());
  } else if(auto flt_const = dyn_cast<ConstantFP>(&v)) {
    return std::to_string(flt_const->getValueAPF().convertToDouble());
  } else {
    if(v.getType()->isVoidTy()) {
      return "";
    } else {
      if(v.hasName()) { 
        return v.getName().str() + std::to_string(counter++);
      } else {
        return "v" + std::to_string(counter++);
      }
    }
  }
}

std::vector<Node> get_nodes(Function const& fn)
{
  auto nodes = std::vector<Node>{};
  auto idxs = std::map<Value const*, int>{};
  int counter = 0;

  // Build indexes
  for(auto const& arg : fn.args()) {
    idxs[&arg] = counter++;
  }

  for(auto const& BB : fn) {
    for(auto const& I : BB) {
      idxs[&I] = counter++;
    }
  }

  for(auto const& BB : fn) {
    for(auto const& I : BB) {
      for(auto const& o : I.operands()) {
        if(isa<Constant>(&o)) {
          idxs[o] = counter++;
        }
      }
    }
  }

  // Build nodes
  for(auto const& arg : fn.args()) {
    nodes.emplace_back(instr_type(arg), instr_name(arg));
  }

  for(auto const& BB : fn) {
    for(auto const& I : BB) {
      auto edges = std::vector<int>{};

      for(auto const& o : I.operands()) {
        edges.push_back(idxs[o]);
      }

      nodes.emplace_back(instr_type(I), instr_name(I), edges);
    }
  }

  for(auto const& BB : fn) {
    for(auto const& I : BB) {
      for(auto const& o : I.operands()) {
        if(isa<Constant>(&o)) {
          nodes.emplace_back(instr_type(I), instr_name(I));
        }
      }
    }
  }

  return nodes;
}

Graph from_function(Function const& fn)
{
  return { get_nodes(fn) };
}
