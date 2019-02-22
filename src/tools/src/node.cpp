#include "match.h"

#include <iostream>

/* cnst, */
/* param, */
/* icmp, */
/* br, */
/* phi, */
/* add, */
/* mul, */
/* zext, */
/* gep, */
/* load, */
/* fmul, */
/* fadd, */
/* fsub, */
/* ret, */
/* store */

void Node::print(std::ostream& os) const
{
  os << "{ " << Graph::opcode_string(op) << " " << name << " ";

  auto comma = "";
  for (auto e : edges) {
    os << comma << e;
    comma = ", ";
  }

  os << "}\n";
}
