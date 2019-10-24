#include <props/props.h>

#include <iostream>

using namespace props;

std::ostream& operator<<(std::ostream& os, const base_type& dt)
{
  switch (dt) {
  case base_type::character:
    os << "char";
    break;
  case base_type::integer:
    os << "int";
    break;
  case base_type::floating:
    os << "float";
    break;
  case base_type::boolean:
    os << "bool";
    break;
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const param& p)
{
  os << p.type << " ";
  for (auto i = 0; i < p.pointer_depth; ++i) {
    os << '*';
  }
  os << p.name;
  return os;
}

std::ostream& operator<<(std::ostream& os, const signature& sig)
{
  // FIXME: does any code actually call this or can the entire stream bit be
  // removed?

  /* if (auto rt = sig.return_type) { */
  /*   os << rt.value(); */
  /* } else { */
  /*   os << "void"; */
  /* } */

  os << " " << sig.name << "(";

  for (auto it = sig.parameters.begin(); it != sig.parameters.end(); ++it) {
    os << *it;
    if (std::next(it) != sig.parameters.end()) {
      os << ", ";
    }
  }

  os << ")";
  return os;
}
