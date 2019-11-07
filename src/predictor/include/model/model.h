#include <props/props.h>

#include <set>
#include <string>

namespace model {

int prop_category(std::string const& str);

std::set<std::string> input_keys();

props::property_set predict(props::property_set ps);

}
