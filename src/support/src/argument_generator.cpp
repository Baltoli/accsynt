#include <support/argument_generator.h>
#include <support/random.h>
#include <support/visitor.h>

#include <optional>

using namespace props;

namespace support {

// Wrapper methods
argument_generator::argument_generator(argument_generator& other)
    : strategy_(other.strategy_->clone())
{
}

argument_generator& argument_generator::operator=(argument_generator other)
{
  using std::swap;
  swap(*this, other);
  return *this;
}

void swap(argument_generator& a, argument_generator& b)
{
  using std::swap;
  swap(a.strategy_, b.strategy_);
}

void argument_generator::gen_args(call_builder& build)
{
  strategy_->gen_args(build);
}

// Uniform generator implementation

uniform_generator::uniform_generator(size_t sz)
    : engine_(get_random_device()())
    , size_(sz)
{
}

uniform_generator::uniform_generator()
    : uniform_generator(max_size)
{
}

void uniform_generator::seed(std::random_device::result_type seed)
{
  engine_.seed(seed);
}

template <>
int uniform_generator::gen_single<int>()
{
  return std::uniform_int_distribution<int>(0, size_ - 1)(engine_);
}

template <>
char uniform_generator::gen_single<char>()
{
  return std::uniform_int_distribution<char>()(engine_);
}

template <>
float uniform_generator::gen_single<float>()
{
  return std::uniform_real_distribution<float>()(engine_);
}

void uniform_generator::gen_args(call_builder& build)
{
  // clang-format off
  sig_visitor {
    on(data_type::integer, [&] (auto const&) { build.add(gen_single<int>()); }),
    on(data_type::character, [&] (auto const&) { build.add(gen_single<char>()); }),
    on(data_type::floating, [&] (auto const&) { build.add(gen_single<float>()); }),
    on(data_type::integer, 1, [&] (auto const&) { build.add(gen_array<int>()); }),
    on(data_type::character, 1, [&] (auto const&) { build.add(gen_array<char>()); }),
    on(data_type::floating, 1, [&] (auto const&) { build.add(gen_array<float>()); })
  }.visit(build.signature());
  // clang-format on
}

// CSR Generator Implementation
csr_generator::csr_generator()
    : max_size_(128)
    , engine_(get_random_device()())
{
}

void csr_generator::gen_args(call_builder& build)
{
  auto rows = gen_rows();
  auto rowstr = gen_rowstr(rows);
  auto colidx = gen_colidx(rowstr);
  auto data = gen_data(rowstr);
  auto iv = gen_input(colidx);
  auto ov = gen_output(rows);

  auto const& sig = build.signature();
  for (auto const& p : sig.parameters) {
    if (p.name == "rows") {
      build.add(rows);
    } else if (p.name == "rowstr") {
      build.add(rowstr);
    } else if (p.name == "colidx") {
      build.add(colidx);
    } else if (p.name == "a") {
      build.add(data);
    } else if (p.name == "iv") {
      build.add(iv);
    } else if (p.name == "ov") {
      build.add(ov);
    } else {
      throw std::runtime_error("Unknown parameter name");
    }
  }
}

int csr_generator::gen_rows()
{
  return std::uniform_int_distribution<int>(1, max_size_)(engine_);
}

std::vector<int> csr_generator::gen_rowstr(int rows)
{
  auto rowstr = std::vector<int>(rows + 1);
  auto b = rowstr.begin();
  auto e = rowstr.end();

  std::generate(b, e, [&] {
    return std::uniform_int_distribution<int>(0, max_size_)(engine_);
  });

  std::sort(b, e);
  rowstr.at(0) = 0;

  return rowstr;
}

std::vector<int> csr_generator::gen_colidx(std::vector<int> const& rowstr)
{
  auto nnz = rowstr.back();

  auto rows = rowstr.size() - 1;
  auto indexes = std::vector<int>(max_size_);
  std::iota(indexes.begin(), indexes.end(), 0);

  auto colidx = std::vector<int>(nnz);
  auto offset = colidx.begin();

  for (auto i = 0u; i < rows; ++i) {
    auto n_row = rowstr[i + 1] - rowstr[i];
    std::shuffle(indexes.begin(), indexes.end(), engine_);
    std::sort(indexes.begin(), indexes.begin() + n_row + 1);

    offset = std::copy_n(indexes.begin(), n_row, offset);
  }

  return colidx;
}

std::vector<float> csr_generator::gen_data(std::vector<int> const& rowstr)
{
  auto nnz = rowstr.back();
  auto data = std::vector<float>(nnz);

  std::generate(data.begin(), data.end(), [&] {
    return std::uniform_real_distribution<float>(-1.0, 1.0)(engine_);
  });

  return data;
}

std::vector<float> csr_generator::gen_input(std::vector<int> const& colidx)
{
  auto cols = (*std::max_element(colidx.begin(), colidx.end())) + 1;
  auto iv = std::vector<float>(cols);

  std::generate(iv.begin(), iv.end(), [&] {
    return std::uniform_real_distribution<float>(-1.0, 1.0)(engine_);
  });

  return iv;
}

std::vector<float> csr_generator::gen_output(int rows)
{
  return std::vector<float>(rows);
}
} // namespace support
