#include <props/props.h>

#include <support/assert.h>
#include <support/options.h>
#include <support/tuple.h>

#include <llvm/Support/CommandLine.h>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include <filesystem>
#include <iostream>
#include <queue>
#include <set>
#include <tuple>

using namespace support;
using namespace llvm;
using namespace props;

namespace fs = std::filesystem;

static cl::list<std::string> InputFilenames(
    cl::Positional, cl::desc("<input property files...>"),
    cl::value_desc("filename"), cl::ZeroOrMore);

static cl::opt<std::string> InputDirectory(
    "directory", cl::desc("Root input directory"), cl::value_desc("filename"),
    cl::init(""));

static cl::alias InputDirectoryA(
    "d", cl::desc("Alias for --directory"), cl::aliasopt(InputDirectory));

static cl::opt<bool> ScalarOnly(
    "scalar", cl::desc("Return property sets that only use scalar inputs"),
    cl::init(false));

bool is_props_file(fs::path const& path)
{
  return fs::is_regular_file(path)
         && (path.extension() == ".props"
             || (path.extension().empty() && path.filename() == "props"));
}

std::set<fs::path> get_all_files()
{
  auto ret = std::set<fs::path> {};

  for (auto const& file : InputFilenames) {
    ret.insert(fs::canonical(file));
  }

  if (!InputDirectory.empty()) {
    auto root = fs::canonical(InputDirectory.getValue());

    assertion(
        fs::is_directory(root), "Input directory {} is not a directory!\n",
        root);

    for (auto const& entry : fs::recursive_directory_iterator(root)) {
      if (is_props_file(entry.path())) {
        ret.insert(fs::canonical(entry));
      }
    }
  }

  return ret;
}

bool is_scalar(props::property_set const& ps)
{
  return !ps.type_signature.accepts_pointer();
}

auto validators()
{
  return std::tuple {
      [](auto const& ps) { return ScalarOnly ? is_scalar(ps) : true; }};
}

int main(int argc, char** argv)
{
  hide_llvm_options();

  cl::ParseCommandLineOptions(argc, argv);

  auto all_paths = get_all_files();

  for (auto const& p : all_paths) {
    auto p_set = property_set::load(p.string());
    auto all = true;

    ::support::for_each(
        validators(), [&](auto&& val) { all = all && val(p_set); });

    if (all) {
      fmt::print("{}\n", p.string());
    }
  }
}
