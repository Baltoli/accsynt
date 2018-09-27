#include <catch2/catch.hpp>

#include <dist/output_collector.h>
#include <dist/types.h>

using namespace accsynt;

TEST_CASE( "can collect output parameters" ) {
  SECTION( "with a simple callable" ) {
    auto fn = [](auto& vec) {
      vec.at(0) = 1;
      return vec.at(1);
    };

    auto ret_t = Integer{64};
    auto arg_t = Output{Array{ret_t, 2}};

    auto cc = CollectCallable(fn, ret_t, arg_t);

    auto arg_v = std::vector<long>{4, 9};
    auto ret = cc(arg_v);

    REQUIRE(arg_v.at(0) == 4);
    REQUIRE(arg_v.at(1) == 9);

    REQUIRE(std::get<0>(ret) == 9);
    REQUIRE(std::get<1>(ret).at(0) == 1);
    REQUIRE(std::get<1>(ret).at(1) == 9);
  }

  SECTION( "with void return" ) {
    auto fn = [](auto& vec) {
      vec.at(0) = 1;
    };

    auto cc = CollectCallable(fn, Void{}, Output{Array{Integer{64}, 1}});

    auto arg_v = std::vector<long>{4};
    auto ret = cc(arg_v);

    REQUIRE(std::get<0>(ret).at(0) == 1);
  }
}
