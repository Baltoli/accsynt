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
    : int_min(-4)
    , int_max(sz - 1)
    , float_min(-5.0)
    , float_max(5.0)
    , engine_(get_random_device()())
    , size_(sz)
    , reuse_(false)
    , int_arrays_ {}
    , float_arrays_ {}
    , char_arrays_ {}
    , prealloc_idx_(0)
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

void uniform_generator::preallocate(size_t n)
{
  reuse_ = true;

  for (auto i = 0u; i < n; ++i) {
    int_arrays_.push_back(gen_array_internal<int64_t>());
    float_arrays_.push_back(gen_array_internal<float>());
    char_arrays_.push_back(gen_array_internal<char>());
  }
}

void uniform_generator::reset() { prealloc_idx_ = 0; }

template <>
int64_t uniform_generator::gen_single<int64_t>()
{
  return std::uniform_int_distribution<int64_t>(int_min, int_max)(engine_);
}

template <>
char uniform_generator::gen_single<char>()
{
  return std::uniform_int_distribution<char>()(engine_);
}

template <>
float uniform_generator::gen_single<float>()
{
  return std::uniform_real_distribution<float>(float_min, float_max)(engine_);
}

void uniform_generator::gen_args(call_builder& build)
{
  reset();

  // clang-format off
  sig_visitor {
    on(base_type::integer,      [&] { build.add(gen_single<int64_t>()); }),
    on(base_type::character,    [&] { build.add(gen_single<char>()); }),
    on(base_type::floating,     [&] { build.add(gen_single<float>()); }),
    on(base_type::integer,   1, [&] { build.add(gen_array<int64_t>()); }),
    on(base_type::character, 1, [&] { build.add(gen_array<char>()); }),
    on(base_type::floating,  1, [&] { build.add(gen_array<float>()); })
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

int64_t csr_generator::gen_rows()
{
  return std::uniform_int_distribution<int64_t>(1, max_size_)(engine_);
}

std::vector<int64_t> csr_generator::gen_rowstr(int64_t rows)
{
  auto rowstr = std::vector<int64_t>(rows + 1);
  auto b = rowstr.begin();
  auto e = rowstr.end();

  std::generate(b, e, [&] {
    return std::uniform_int_distribution<int64_t>(0, max_size_)(engine_);
  });

  std::sort(b, e);
  rowstr.at(0) = 0;

  return rowstr;
}

std::vector<int64_t>
csr_generator::gen_colidx(std::vector<int64_t> const& rowstr)
{
  auto nnz = rowstr.back();

  auto rows = rowstr.size() - 1;
  auto indexes = std::vector<int64_t>(max_size_);
  std::iota(indexes.begin(), indexes.end(), 0);

  auto colidx = std::vector<int64_t>(nnz);
  auto offset = colidx.begin();

  for (auto i = 0u; i < rows; ++i) {
    auto n_row = rowstr[i + 1] - rowstr[i];
    std::shuffle(indexes.begin(), indexes.end(), engine_);
    std::sort(indexes.begin(), indexes.begin() + n_row + 1);

    offset = std::copy_n(indexes.begin(), n_row, offset);
  }

  return colidx;
}

std::vector<float> csr_generator::gen_data(std::vector<int64_t> const& rowstr)
{
  auto nnz = rowstr.back();
  auto data = std::vector<float>(nnz);

  std::generate(data.begin(), data.end(), [&] {
    return std::uniform_real_distribution<float>(-1.0, 1.0)(engine_);
  });

  return data;
}

std::vector<float> csr_generator::gen_input(std::vector<int64_t> const& colidx)
{
  auto cols = (*std::max_element(colidx.begin(), colidx.end())) + 1;
  auto iv = std::vector<float>(cols);

  std::generate(iv.begin(), iv.end(), [&] {
    return std::uniform_real_distribution<float>(-1.0, 1.0)(engine_);
  });

  return iv;
}

std::vector<float> csr_generator::gen_output(int64_t rows)
{
  return std::vector<float>(rows);
}
} // namespace support
