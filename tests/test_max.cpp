#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

#define TEST_TAG "[max]"

TEST_CASE(TEST_TAG "max", TEST_TAG) {
  ftl::vector<int> vec = { { 3, 1, 12, 0, -1, 4, 4, 7 } };

  REQUIRE(vec.iter().max().value() == 12);
}

TEST_CASE(TEST_TAG "max empty range", TEST_TAG) {
  ftl::vector<int> vec = {};

  REQUIRE(vec.iter().max().has_value() == false);
}

TEST_CASE(TEST_TAG "max equal range lower than zero", TEST_TAG) {
  ftl::vector<int> vec = { { -2, -2, -2 } };

  REQUIRE(vec.iter().max().value() == -2);
}

TEST_CASE(TEST_TAG "max equal range greater than zero", TEST_TAG) {
  ftl::vector<int> vec = { { 2, 2, 2 } };

  REQUIRE(vec.iter().max().value() == 2);
}

TEST_CASE(TEST_TAG "max at the beginning", TEST_TAG) {
  ftl::vector<int> vec = { { 4, 3, -1 } };

  REQUIRE(vec.iter().max().value() == 4);
}

TEST_CASE(TEST_TAG "max at the end", TEST_TAG) {
  ftl::vector<int> vec = { { -1, 3, 7 } };

  REQUIRE(vec.iter().max().value() == 7);
}