#include "match.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <sstream>
#include <unordered_set>
#include <vector>

Match::Match(size_t s)
    : first_member(s)
    , next_member(s)
{
  for (size_t i = 0; i < s; i++) {
    first_member[i] = i;
    next_member[i] = 0;
  }
}

void Match::merge(size_t a, size_t b)
{
  if (first_member[a] > first_member[b]) {
    size_t c = a;
    a = b;
    b = c;
  }

  if (first_member[a] < first_member[b]) {
    size_t it = first_member[a];
    size_t jt = first_member[b];

    while (next_member[it])
      it = next_member[it];

    next_member[it] = jt;
    first_member[jt] = first_member[a];

    while (next_member[jt]) {
      jt = next_member[jt];
      first_member[jt] = first_member[a];
    }
  }
}

void Match::separate(size_t a)
{
  if (first_member[a] == a) {
    size_t new_first = next_member[a];
    next_member[a] = 0;

    if (new_first) {
      first_member[new_first] = new_first;

      size_t it = new_first;
      while (next_member[it]) {
        it = next_member[it];
        first_member[it] = new_first;
      }
    }
  } else {
    for (auto i = 0u; i < next_member.size(); i++) {
      if (next_member[i] == a) {
        next_member[i] = next_member[a];
        first_member[a] = a;
        next_member[a] = 0;
        return;
      }
    }
  }
}

void Match::sort()
{
  bool repeat = true;

  while (repeat) {
    repeat = false;
    for (auto i = 0u; i < next_member.size(); i++) {
      size_t j = next_member[i];
      size_t k = next_member[j];
      if (j && k && k < j) {
        next_member[j] = next_member[k];
        next_member[k] = j;
        next_member[i] = k;
        if (i > k)
          repeat = true;
      }
    }
  }
}

std::vector<size_t> Match::get_closure(size_t a) const
{
  std::vector<size_t> result = { first_member[a] };

  while (next_member[result.back()])
    result.push_back(next_member[result.back()]);

  return result;
}

bool Match::is_closed(std::vector<size_t> vec) const
{
  std::vector<size_t> histo(first_member.size(), 0);

  for (auto v : vec)
    histo[v]++;

  for (size_t i = 0; i < histo.size(); i++) {
    if (histo[i] && first_member[i] != i)
      return false;

    while (histo[i]) {
      histo[i] -= 1;

      size_t it = i;
      while (next_member[it]) {
        it = next_member[it];
        if (histo[it] == 0)
          return false;
        histo[it] -= 1;
      }
    }
  }

  return true;
}

double Match::evaluate(const Graph& g, bool print) const
{
  size_t distinct_groups = 0;
  size_t opcode_mismatches = 0;
  size_t param_mismatches = 0;
  size_t overlapped_params = 0;

  for (size_t i = 0; i < first_member.size(); i++) {
    if (first_member[i] == i) {
      std::vector<size_t> members = get_closure(i);

      distinct_groups++;
      if (members.size() > 2)
        distinct_groups++;

      std::vector<Instruction> opcodes = g.get_opcodes(members);

      std::sort(opcodes.begin(), opcodes.end());
      size_t dist = std::distance(
          opcodes.begin(), std::unique(opcodes.begin(), opcodes.end()));

      opcode_mismatches += dist - 1;

      // Score opcode match

      std::vector<std::vector<size_t>> args = g.get_arguments(members);

      std::vector<size_t> used_groups(first_member.size(), 0);
      used_groups[i] = 1;

      for (size_t j = 0; j < args.size(); j++) {
        if (args[j].size() != members.size() || !is_closed(args[j]))
          param_mismatches += members.size();

        for (size_t k = 0; k < args[j].size(); k++)
          if (used_groups[first_member[args[j][k]]]) {
            overlapped_params += members.size();
            break;
          }

        for (size_t k = 0; k < args[j].size(); k++)
          used_groups[first_member[args[j][k]]] = 1;
      }
    }
  }

  double p1 = 1.0;
  double p2 = 0.5;
  double p3 = 0.5;
  double p4 = 0.5;

  if (print) {
    std::cout << distinct_groups << "\t" << opcode_mismatches << "\t"
              << param_mismatches << "\t" << overlapped_params << "\n";
  }

  return 1000000000.0
      / pow(p1 * distinct_groups + p2 * opcode_mismatches
              + p3 * param_mismatches + p4 * overlapped_params,
          3);
}

void Match::print_constraints_line(
    std::ostream& ostr, std::string name, Instruction op) const
{
  ostr << "{" << name << "} is ";
  switch (op) {
  case Instruction::cnst:
    ostr << "constant";
    break;
  case Instruction::param:
    ostr << "an argument";
    break;
  case Instruction::icmp:
    ostr << "icmp instruction";
    break;
  case Instruction::fcmp:
    ostr << "fcmp instruction";
    break;
  case Instruction::br:
    ostr << "branch instruction";
    break;
  case Instruction::phi:
    ostr << "phi instruction";
    break;
  case Instruction::add:
    ostr << "add instruction";
    break;
  case Instruction::sub:
    ostr << "sub instruction";
    break;
  case Instruction::mul:
    ostr << "mul instruction";
    break;
  case Instruction::zext:
    ostr << "zext instruction";
    break;
  case Instruction::sext:
    ostr << "sext instruction";
    break;
  case Instruction::gep:
    ostr << "gep instruction";
    break;
  case Instruction::load:
    ostr << "load instruction";
    break;
  case Instruction::store:
    ostr << "store instruction";
    break;
  case Instruction::fmul:
    ostr << "fmul instruction";
    break;
  case Instruction::fadd:
    ostr << "fadd instruction";
    break;
  case Instruction::fsub:
    ostr << "fsub instruction";
    break;
  case Instruction::ret:
    ostr << "parameter";
    break;
  case Instruction::select:
    ostr << "select instruction";
    break;
  case Instruction::trunc:
    ostr << "trunc instruction";
    break;
  case Instruction::call:
    ostr << "call instruction";
    break;
  case Instruction::fdiv:
    ostr << "fdiv instruction";
    break;
  case Instruction::and_:
    ostr << "and instruction";
    break;
  }
}

void Match::print_constraints(const Graph& g, std::ostream& ostr) const
{
  std::map<size_t, std::string> group_names;

  for (size_t i = 0; i < first_member.size(); i++) {
    if (first_member[i] == i) {
      std::string name;
      std::stringstream sstr(name);

      sstr << (char)('A' + (i / 10)) << (char)('A' + (i % 10));

      for (auto c : g.nodes[i].name)
        if (isalnum(c))
          sstr << c;

      group_names[i] = sstr.str();
    }
  }

  for (size_t i = 0; i < first_member.size(); i++) {
    if (first_member[i] == i) {
      std::vector<size_t> members = get_closure(i);

      if (members.size() == 1)
        continue;

      std::vector<Instruction> opcodes = g.get_opcodes(members);
      size_t uniques = std::distance(
          opcodes.begin(), std::unique(opcodes.begin(), opcodes.end()));

      bool skip = false;
      for (auto op : opcodes)
        if (op == Instruction::param || op == Instruction::br
            || op == Instruction::cnst || op == Instruction::ret)
          skip = true;
      if (skip)
        continue;

      ostr << ((uniques > 1) ? "  ( " : "  ");
      for (size_t j = 0; j < uniques; j++) {
        print_constraints_line(ostr, group_names[i], opcodes[j]);
        ostr << ((j + 1 == uniques) ? ((j == 0) ? "" : ")") : " or\n    ");
      }
      ostr << " and\n";

      std::vector<std::vector<size_t>> args = g.get_arguments(members);

      if (uniques == 1
          && (opcodes[0] == Instruction::fadd || opcodes[0] == Instruction::fmul
              || opcodes[0] == Instruction::add
              || opcodes[0] == Instruction::mul
              || opcodes[0] == Instruction::phi
              || opcodes[0] == Instruction::icmp)) {
        ostr << "  ( (";
        bool first = true;
        for (size_t j = 0; j < args.size(); j++) {
          if (args[j].size() == members.size() && is_closed(args[j])) {
            ostr << (first ? " " : " and\n      ");
            ostr << "{" << group_names[first_member[args[j][0]]] << "} is ";
            switch (j) {
            case 0:
              ostr << "first";
              break;
            case 1:
              ostr << "second";
              break;
            case 2:
              ostr << "third";
              break;
            case 3:
              ostr << "fourth";
              break;
            }
            ostr << " argument of {" << group_names[i] << "}";
            first = false;
          }
        }
        ostr << ") or\n    (";
        first = true;
        for (size_t j = 0; j < args.size(); j++) {
          if (args[j].size() == members.size() && is_closed(args[j])) {
            ostr << (first ? " " : " and\n      ");
            ostr << "{" << group_names[first_member[args[j][0]]] << "} is ";
            switch (1 - j) {
            case 0:
              ostr << "first";
              break;
            case 1:
              ostr << "second";
              break;
            case 2:
              ostr << "third";
              break;
            case 3:
              ostr << "fourth";
              break;
            }
            ostr << " argument of {" << group_names[i] << "}";
            first = false;
          }
        }
        ostr << ")) and\n";
      } else {
        for (size_t j = 0; j < args.size(); j++) {
          if (args[j].size() == members.size() && is_closed(args[j])) {
            ostr << "  {" << group_names[first_member[args[j][0]]] << "} is ";
            switch (j) {
            case 0:
              ostr << "first";
              break;
            case 1:
              ostr << "second";
              break;
            case 2:
              ostr << "third";
              break;
            case 3:
              ostr << "fourth";
              break;
            }
            ostr << " argument of {" << group_names[i] << "} and\n";
          }
        }
      }
    }
  }
}
