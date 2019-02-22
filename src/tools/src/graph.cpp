#include "match.h"

#include <iostream>

std::string Graph::opcode_string(Instruction op)
{
  switch (op) {
  case Instruction::cnst:
    return "cnst";
  case Instruction::param:
    return "param";
  case Instruction::icmp:
    return "icmp";
  case Instruction::br:
    return "br";
  case Instruction::phi:
    return "phi";
  case Instruction::add:
    return "add";
  case Instruction::zext:
    return "zext";
  case Instruction::gep:
    return "gep";
  case Instruction::load:
    return "load";
  case Instruction::fmul:
    return "fmul";
  case Instruction::fsub:
    return "fsub";
  case Instruction::fadd:
    return "fadd";
  case Instruction::store:
    return "store";
  case Instruction::ret:
    return "ret";
  default:
    return "";
  }
}

void Graph::print(std::ostream& ostr) const
{
  ostr << "function( ";
  for (auto n : nodes)
    if (n.op == Instruction::param)
      ostr << n.name << " ";
  ostr << ") {\n";

  for (auto n : nodes) {
    if (n.op != Instruction::param && n.op != Instruction::cnst) {
      if (n.name == "")
        ostr << opcode_string(n.op);
      else
        ostr << n.name << " = " << opcode_string(n.op);

      for (auto idx : n.edges)
        ostr << " " << nodes[idx].name;
      ostr << "\n";
    }
  }

  ostr << "}";
}

std::vector<Instruction> Graph::get_opcodes(std::vector<size_t> idx) const
{
  std::vector<Instruction> result;
  for (size_t i = 0; i < idx.size(); i++)
    result.push_back(nodes[idx[i]].op);
  return result;
}

std::vector<std::vector<size_t>> Graph::get_arguments(std::vector<size_t> idx) const
{
  std::vector<std::vector<size_t>> result;
  for (auto i : idx)
    for (size_t k = 0; k < nodes[i].edges.size(); k++) {
      if (k >= result.size())
        result.resize(k + 1);
      result[k].push_back(nodes[i].edges[k]);
    }
  return result;
}

void Graph::add(Graph& g)
{
  size_t old_size = nodes.size();

  for (auto n : g.nodes) {
    for (auto& e : n.edges)
      e += old_size;
    nodes.push_back(n);
  }
}
