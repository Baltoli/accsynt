#include "match.h"

#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Support/raw_ostream.h>

#include <map>
#include <set>

using namespace llvm;

::Instruction instr_type(Value const& v)
{
  if (isa<Argument>(&v)) {
    return ::Instruction::param;
  }

  if (isa<Constant>(&v)) {
    return ::Instruction::cnst;
  }

  if (auto inst = dyn_cast<llvm::Instruction>(&v)) {
    switch (inst->getOpcode()) {
    case llvm::Instruction::ICmp:
      return ::Instruction::icmp;
    case llvm::Instruction::FCmp:
      return ::Instruction::fcmp;
    case llvm::Instruction::Br:
      return ::Instruction::br;
    case llvm::Instruction::PHI:
      return ::Instruction::phi;
    case llvm::Instruction::Add:
      return ::Instruction::add;
    case llvm::Instruction::Sub:
      return ::Instruction::sub;
    case llvm::Instruction::Mul:
      return ::Instruction::mul;
    case llvm::Instruction::ZExt:
      return ::Instruction::zext;
    case llvm::Instruction::SExt:
      return ::Instruction::sext;
    case llvm::Instruction::GetElementPtr:
      return ::Instruction::gep;
    case llvm::Instruction::Load:
      return ::Instruction::load;
    case llvm::Instruction::FMul:
      return ::Instruction::fmul;
    case llvm::Instruction::FAdd:
      return ::Instruction::fadd;
    case llvm::Instruction::FSub:
      return ::Instruction::fsub;
    case llvm::Instruction::Ret:
      return ::Instruction::ret;
    case llvm::Instruction::Store:
      return ::Instruction::store;
    case llvm::Instruction::Select:
      return ::Instruction::select;
    case llvm::Instruction::Trunc:
      return ::Instruction::trunc;
    case llvm::Instruction::Call:
      return ::Instruction::call;
    case llvm::Instruction::FDiv:
      return ::Instruction::fdiv;
    }
  }

  errs() << v << '\n';
  assert(false && "Bad instruction type");
  __builtin_unreachable();
}

std::string instr_name(Value const& v)
{
  static int counter = 0;

  if (auto int_const = dyn_cast<ConstantInt>(&v)) {
    return std::to_string(int_const->getSExtValue());
  } else if (auto flt_const = dyn_cast<ConstantFP>(&v)) {
    return std::to_string(flt_const->getValueAPF().convertToDouble());
  } else {
    if (v.getType()->isVoidTy()) {
      return "";
    } else {
      if (v.hasName()) {
        return v.getName().str() + std::to_string(counter++);
      } else {
        return "v" + std::to_string(counter++);
      }
    }
  }
}

std::vector<Node> get_nodes(Function const& fn)
{
  auto vals = std::map<std::string, int> {};

  auto const_idx = [&vals](Constant const* c, int& count) {
    auto name = instr_name(*c);

    if (vals.find(name) == vals.end()) {
      vals.insert({ name, count++ });
    }

    return vals[name];
  };

  auto nodes = std::vector<Node> {};
  auto idxs = std::map<Value const*, int> {};
  int counter = 0;

  // Build indexes
  for (auto const& arg : fn.args()) {
    idxs[&arg] = counter++;
  }

  for (auto const& BB : fn) {
    for (auto const& I : BB) {
      for (auto const& o : I.operands()) {
        if (!isa<BasicBlock>(o)) {
          idxs[&I] = counter++;
          break;
        }
      }
    }
  }

  for (auto const& BB : fn) {
    for (auto const& I : BB) {
      for (auto const& o : I.operands()) {
        if (auto cst = dyn_cast<Constant>(&o)) {
          idxs[o] = const_idx(cst, counter);
        }
      }
    }
  }

  // Build nodes
  for (auto const& arg : fn.args()) {
    nodes.emplace_back(instr_type(arg), instr_name(arg));
  }

  for (auto const& BB : fn) {
    for (auto const& I : BB) {
      auto edges = std::vector<int> {};

      for (auto const& o : I.operands()) {
        if (auto cst = dyn_cast<Constant>(&o)) {
          int i = 0;
          edges.push_back(const_idx(cst, i));
        } else {
          if (!isa<BasicBlock>(o)) {
            edges.push_back(idxs[o]);
          }
        }
      }

      if (!edges.empty()) {
        nodes.emplace_back(instr_type(I), instr_name(I), edges);
      }
    }
  }

  auto names = std::set<std::string> {};
  for (auto const& BB : fn) {
    for (auto const& I : BB) {
      for (auto const& o : I.operands()) {
        if (auto cst = dyn_cast<Constant>(&o)) {
          auto name = instr_name(*cst);
          if (names.find(name) == names.end()) {
            nodes.emplace_back(instr_type(*cst), name);
            names.insert(name);
          }
        }
      }
    }
  }

  return nodes;
}

Graph from_function(Function const& fn)
{
  auto nodes = get_nodes(fn);
  int i = 0;
  for (auto n : nodes) {
    std::cout << i++ << ": ";
    n.print(std::cout);
  }
  return { nodes };
}
