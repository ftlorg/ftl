#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

#define TEST_TAG "[flatten_iterator]"

TEST_CASE(TEST_TAG "flatten array collect", TEST_TAG) {
  ftl::array<ftl::array<int, 2>, 2> vec = { { ftl::array<int, 2>{ { 1, 2 } }, ftl::array<int, 2>{ { 3, 4 } } } };

  auto f_vec = vec.iter().flatten().collect<std::vector<int>>();

  REQUIRE(f_vec == ftl::vector<int>{ 1, 2, 3, 4 });
}

TEST_CASE(TEST_TAG "flatten const array collect", TEST_TAG) {
  const ftl::array<ftl::array<int, 2>, 2> vec = { { ftl::array<int, 2>{ { 1, 2 } }, ftl::array<int, 2>{ { 3, 4 } } } };

  auto f_vec = vec.iter().flatten().collect<std::vector<int>>();

  REQUIRE(f_vec == ftl::vector<int>{ 1, 2, 3, 4 });
}

TEST_CASE(TEST_TAG "flatten vector collect", TEST_TAG) {
  ftl::vector<ftl::vector<int>> vec = { ftl::vector<int>{ 1, 2 }, ftl::vector<int>{ 3, 4 } };

  auto f_vec = vec.iter().flatten().collect<std::vector<int>>();

  REQUIRE(f_vec == ftl::vector<int>{ 1, 2, 3, 4 });
}

TEST_CASE(TEST_TAG "flatten vector of vectors of vectors collect", TEST_TAG) {
  ftl::vector<ftl::vector<ftl::vector<int>>> vec = { ftl::vector<ftl::vector<int>>{ ftl::vector<int>{ 1, 2 } },
    ftl::vector<ftl::vector<int>>{ ftl::vector<int>{ 3, 4 } } };

  auto f_vec = vec.iter().flatten().collect<std::vector<int>>();

  REQUIRE(f_vec == ftl::vector<int>{ 1, 2, 3, 4 });
}

TEST_CASE(TEST_TAG "flatten const vector of vectors of vectors collect", TEST_TAG) {
  const ftl::vector<ftl::vector<ftl::vector<int>>> vec = { ftl::vector<ftl::vector<int>>{ ftl::vector<int>{ 1, 2 } },
    ftl::vector<ftl::vector<int>>{ ftl::vector<int>{ 3, 4 } } };

  auto f_vec = vec.iter().flatten().collect<std::vector<int>>();

  REQUIRE(f_vec == ftl::vector<int>{ 1, 2, 3, 4 });
}

TEST_CASE(TEST_TAG "flatten const vector of deques of lists collect", TEST_TAG) {
  const ftl::vector<ftl::deque<ftl::list<int>>> vec
    = { ftl::deque<ftl::list<int>>{ ftl::list<int>{ 1, 2 } }, ftl::deque<ftl::list<int>>{ ftl::list<int>{ 3, 4 } } };

  auto f_vec = vec.iter().flatten().collect<std::vector<int>>();

  REQUIRE(f_vec == ftl::vector<int>{ 1, 2, 3, 4 });
}

TEST_CASE(TEST_TAG "flatten vector of deques of lists collect", TEST_TAG) {
  ftl::vector<ftl::deque<ftl::list<int>>> vec
    = { ftl::deque<ftl::list<int>>{ ftl::list<int>{ 1, 2 } }, ftl::deque<ftl::list<int>>{ ftl::list<int>{ 3, 4 } } };

  auto f_vec = vec.iter().flatten().collect<std::vector<int>>();

  REQUIRE(f_vec == ftl::vector<int>{ 1, 2, 3, 4 });
}

TEST_CASE(TEST_TAG "flatten set collect", TEST_TAG) {
  ftl::set<ftl::set<int>> vec = { ftl::set<int>{ 1, 2 }, ftl::set<int>{ 3, 4 } };

  auto f_vec = vec.iter().flatten().collect<std::vector<int>>();

  REQUIRE(f_vec == ftl::vector<int>{ 1, 2, 3, 4 });
}

TEST_CASE(TEST_TAG "flatten const set collect", TEST_TAG) {
  const ftl::set<ftl::set<int>> vec = { ftl::set<int>{ 1, 2, 5 }, ftl::set<int>{ 5, 3, 4 } };

  auto f_vec = vec.iter().flatten().collect<std::set<int>>();

  REQUIRE(f_vec == ftl::set<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "flatten forward_list collect", TEST_TAG) {
  ftl::forward_list<ftl::forward_list<int>> vec = { ftl::forward_list<int>{ 1, 2 }, ftl::forward_list<int>{ 3, 4 } };

  auto f_vec = vec.iter().flatten().collect<std::vector<int>>();

  REQUIRE(f_vec == ftl::vector<int>{ 1, 2, 3, 4 });
}

TEST_CASE(TEST_TAG "flatten const forward_list collect", TEST_TAG) {
  const ftl::forward_list<ftl::forward_list<int>> vec = { ftl::forward_list<int>{ 1, 2 }, ftl::forward_list<int>{ 3, 4 } };

  auto f_vec = vec.iter().flatten().collect<std::forward_list<int>>();

  REQUIRE(f_vec == ftl::forward_list<int>{ 1, 2, 3, 4 });
}

TEST_CASE(TEST_TAG "flatten after map", TEST_TAG) {
  ftl::vector<ftl::vector<int>> vec = { ftl::vector<int>{ 1, 2 }, ftl::vector<int>{ 3, 4 } };

  auto f_vec = vec.iter().map([](const auto &element) { return element; }).flatten().collect<std::vector<int>>();

  REQUIRE(f_vec == ftl::vector<int>{ 1, 2, 3, 4 });
}

TEST_CASE(TEST_TAG "flatten after map vector of vectors", TEST_TAG) {
  ftl::vector<ftl::deque<ftl::list<int>>> vec
    = { ftl::deque<ftl::list<int>>{ ftl::list<int>{ 1, 2 } }, ftl::deque<ftl::list<int>>{ ftl::list<int>{ 3, 4 } } };

  auto f_vec = vec.iter().map([](const auto &element) { return element; }).flatten().collect<std::vector<int>>();

  REQUIRE(f_vec == ftl::vector<int>{ 1, 2, 3, 4 });
}

TEST_CASE(TEST_TAG "flatten after filter", TEST_TAG) {
  ftl::vector<ftl::deque<int>> vec = { ftl::deque<int>{ 1, 2 },
    ftl::deque<int>{ 3, 4 },
    ftl::deque<int>{ 3, 4, 5 },
    ftl::deque<int>{ 3, 4, 5 },
    ftl::deque<int>{ 3, 4, 5 } };

  auto f_vec
    = vec.iter().filter([](const auto &element) { return element.size() <= 2; }).flatten().collect<std::vector<int>>();

  REQUIRE(f_vec == ftl::vector<int>{ 1, 2, 3, 4 });
}

TEST_CASE(TEST_TAG "filter after flatten", TEST_TAG) {
  ftl::vector<ftl::deque<int>> vec = { ftl::deque<int>{ 1, 2 },
    ftl::deque<int>{ 3, 4 },
    ftl::deque<int>{ 3, 4, 5 },
    ftl::deque<int>{ 3, 4, 5 },
    ftl::deque<int>{ 3, 4, 5 } };

  auto f_vec
    = vec.iter().flatten().filter([](const auto &element) { return element < 5; }).collect<std::set<int>>();

  REQUIRE(f_vec == ftl::set<int>{ 1, 2, 3, 4 });
}
