#include <support/argument_generator.h>
#include <support/random.h>

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

void uniform_generator::gen_args(call_builder& build)
{
  auto const& sig = build.signature();
  for (auto p : sig.parameters) {
    if (p.pointer_depth > 1) {
      throw std::runtime_error("No nested pointers");
    }

    if (p.pointer_depth == 0) {
      if (p.type == data_type::integer) {
        build.add(gen_single<int>());
      } else if (p.type == data_type::floating) {
        build.add(gen_single<float>());
      } else {
        throw std::runtime_error("Unknown data_type");
      }
    } else {
      if (p.type == data_type::integer) {
        build.add(gen_array<int>());
      } else if (p.type == data_type::floating) {
        build.add(gen_array<float>());
      } else {
        throw std::runtime_error("Unknown data_type");
      }
    }
  }
}

template <>
int uniform_generator::gen_single<int>()
{
  return std::uniform_int_distribution<int>()(engine_);
}

template <>
float uniform_generator::gen_single<float>()
{
  return std::uniform_real_distribution<float>()(engine_);
}

// CSR Generator Implementation
csr_generator::csr_generator()
{
}

void csr_generator::gen_args(call_builder&)
{
  throw std::runtime_error("Not implemented");
}

int csr_generator::gen_rows()
{
  throw std::runtime_error("Not implemented");
}

std::vector<int> csr_generator::gen_rowstr(int rows)
{
  throw std::runtime_error("Not implemented");
}

std::vector<int> csr_generator::gen_colidx(int nnz)
{
  throw std::runtime_error("Not implemented");
}

std::vector<float> csr_generator::gen_data(int nnz)
{
  throw std::runtime_error("Not implemented");
}

std::vector<float> csr_generator::gen_input(std::vector<int> const& colidx)
{
  throw std::runtime_error("Not implemented");
}

std::vector<float> csr_generator::gen_output(int rows)
{
  throw std::runtime_error("Not implemented");
}
}
