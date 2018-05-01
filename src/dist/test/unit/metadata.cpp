#include "catch.h"

#include <dist/synth_metadata.h>

using namespace accsynt;

#define FAKE_PTR(x) reinterpret_cast<llvm::Value *>((x))
#define UNFAKE(ptr) reinterpret_cast<intptr_t>((ptr))

TEST_CASE("can use entries on their own", "[metadata]") {
  int x = 0;
  int y = 1;

  MetadataEntry<int64_t, int*> entry;
  REQUIRE(!entry(&x));

  entry(&x) = 345;
  REQUIRE(entry(&x));
  REQUIRE(*entry(&x) == 345);

  entry(&y) = 789;
  REQUIRE(entry(&y));
  REQUIRE(*entry(&y) == 789);

  entry.unset(&x);
  REQUIRE(!entry(&x));
}

TEST_CASE("can use the bool specialisation for entries", "[metadata]") {
  auto *v1 = FAKE_PTR(1);
  MetadataEntry<bool> entry;

  REQUIRE(!entry(v1));

  entry(v1) = true;
  REQUIRE(entry(v1));
}

TEST_CASE("can use the synthesis object", "[metadata]") {
  SynthMetadata meta;

  auto *v1 = FAKE_PTR(1);
  auto *v2 = FAKE_PTR(2);

  meta.size(v1) = 10;
  REQUIRE(*meta.size(v1) == 10);

  meta.size.unset(v1);
  REQUIRE(meta.size(v1) == nullptr);
}

TEST_CASE("can use lookup ref objects on their own", "[metadata]") {
  int x;
  std::map<int *, int> m;
  m.insert_or_assign(&x, 2);

  LookupRef<int, int*> lr(m, &x);
  REQUIRE(*lr == 2);

  lr = 4;
  REQUIRE(*lr == 4);
}

TEST_CASE("can iterate over entries", "[metadata]") {
  SECTION("bools") {
    MetadataEntry<bool> entry;

    intptr_t prod = 1;

    auto *p1 = FAKE_PTR(0);
    auto *p2 = FAKE_PTR(2); entry(p2) = true;
    auto *p3 = FAKE_PTR(3); entry(p3) = true;
    auto *p4 = FAKE_PTR(5); entry(p4) = false;

    for(auto *p : entry) {
      prod *= UNFAKE(p);
    }

    REQUIRE(prod == 6);
  }

  SECTION("others") {
    MetadataEntry<int> entry;

    intptr_t prod = 1;

    auto *p1 = FAKE_PTR(0); entry(p1) = 2;
    auto *p2 = FAKE_PTR(1); entry(p2) = 3;
    auto *p3 = FAKE_PTR(2); entry(p3) = 5;

    for(auto [k, v] : entry) {
      prod *= v;
    }

    REQUIRE(prod == 30);
  }
}

TEST_CASE("can copy metadata if we need to", "[metadata]") {
  auto s1 = SynthMetadata{};
  auto* v1 = FAKE_PTR(1);
  s1.size(v1) = 10;
  
  auto s2 = s1;
  REQUIRE(*s1.size(v1) == *s2.size(v1));

  s1.size(v1) = 9;
  REQUIRE(*s1.size(v1) != *s2.size(v1));

  s2.size.unset(v1);
  REQUIRE(*s1.size(v1) == 9);
  REQUIRE(!s2.size(v1));
}
