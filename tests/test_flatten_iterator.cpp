#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

#define TEST_TAG "[flatten_iterator]"

TEST_CASE(TEST_TAG "flatten array collect", TEST_TAG) {
  ftl::array<ftl::array<int, 2>, 2> vec = { { ftl::array<int, 2>{ { 1, 2 } }, ftl::array<int, 2>{ { 3, 4 } } } };

  auto f_vec = vec.iter().flatten().collect<std::vector<int>>();

  REQUIRE(f_vec == ftl::vector<int>{ 1, 2, 3, 4 });
}

TEST_CASE(TEST_TAG "flatten vector collect", TEST_TAG) {
  ftl::vector<ftl::vector<int>> vec = { ftl::vector<int>{ 1, 2 }, ftl::vector<int>{ 3, 4 } };

  auto f_vec = vec.iter().flatten().collect<std::vector<int>>();

  REQUIRE(f_vec == ftl::vector<int>{ 1, 2, 3, 4 });
}

TEST_CASE(TEST_TAG "flatten vector of vectors of vectors collect", TEST_TAG) {
  ftl::vector<ftl::vector<ftl::vector<int>>> vec = { 
    ftl::vector<ftl::vector<int>>{ ftl::vector<int>{ 1, 2 } },
    ftl::vector<ftl::vector<int>>{ ftl::vector<int>{ 3, 4 } } 
  };

  auto f_vec = vec.iter().flatten().collect<std::vector<int>>();

  REQUIRE(f_vec == ftl::vector<int>{ 1, 2, 3, 4 });
}