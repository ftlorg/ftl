#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

#define TEST_TAG "[min]"

TEST_CASE(TEST_TAG "min", TEST_TAG) {
  ftl::vector<int> vec = { { 3, 1, 5, 0, -1, 4, 4, 7 } };

  REQUIRE(vec.iter().min().value() == -1);
}

TEST_CASE(TEST_TAG "min empty range", TEST_TAG) {
  ftl::vector<int> vec = { };

  REQUIRE(vec.iter().min().has_value() == false);
}

TEST_CASE(TEST_TAG "min equal range lower than zero", TEST_TAG) {
  ftl::vector<int> vec = { { -2, -2, -2 } };

  REQUIRE(vec.iter().min().value() == -2);
}

TEST_CASE(TEST_TAG "min equal range greater than zero", TEST_TAG) {
  ftl::vector<int> vec = { { 2, 2, 2 } };

  REQUIRE(vec.iter().min().value() == 2);
}

TEST_CASE(TEST_TAG "min at the beginning", TEST_TAG) {
  ftl::vector<int> vec = { { -1, 3, 2 } };

  REQUIRE(vec.iter().min().value() == -1);
}

TEST_CASE(TEST_TAG "min at the end", TEST_TAG) {
  ftl::vector<int> vec = { { -1, 3, -3 } };

  REQUIRE(vec.iter().min().value() == -3);
}
