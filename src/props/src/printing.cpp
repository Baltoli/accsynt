#include <props/props.h>

#include <iostream>

using namespace props;

std::ostream& operator <<(std::ostream& os, const data_type& dt)
{
  switch(dt) {
    case data_type::integer:
      os << "int";
      break;
    case data_type::floating:
      os << "float";
      break;
  }
  return os;
}

std::ostream& operator <<(std::ostream& os, const param& p)
{
  os << p.type << " ";
  for(auto i = 0; i < p.pointer_depth; ++i) {
    os << '*';
  }
  os << p.name;
  return os;
}

std::ostream& operator <<(std::ostream& os, const signature& sig)
{
  if(auto rt = sig.return_type) {
    os << rt.value();
  } else {
    os << "void";
  }

  os << " " << sig.name << "(";

  for(auto it = sig.parameters.begin(); 
      it != sig.parameters.end(); 
      ++it)
  {
    os << *it;
    if(std::next(it) != sig.parameters.end()) {
      os << ", ";
    }
  }

  os << ")";
  return os;
}
