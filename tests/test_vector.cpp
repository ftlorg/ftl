#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>
#include <array>

#define TEST_TAG "[vector]"

TEST_CASE(TEST_TAG "to_vector", TEST_TAG) {
  std::vector<int> vec = { 1, 2, 3, 4, 6 };

  const auto ftl_vec = ftl::to_vector(vec);

  REQUIRE(ftl_vec[0] == 1);
  REQUIRE(ftl_vec[1] == 2);
  REQUIRE(ftl_vec[2] == 3);
  REQUIRE(ftl_vec[3] == 4);
  REQUIRE(ftl_vec[4] == 6);
}

TEST_CASE(TEST_TAG "operator[]", TEST_TAG) {
  ftl::vector<int> vec = { 1, 2, 3, 4, 6 };

  REQUIRE(vec.data() != nullptr);
  REQUIRE(vec[0] == 1);
  REQUIRE(vec[1] == 2);
  REQUIRE(vec[2] == 3);
  REQUIRE(vec[3] == 4);
  REQUIRE(vec[4] == 6);
}

TEST_CASE(TEST_TAG "operator[] const", TEST_TAG) {
  const ftl::vector<int> vec = { 1, 2, 3, 4, 6 };

  REQUIRE(vec[0] == 1);
  REQUIRE(vec[1] == 2);
  REQUIRE(vec[2] == 3);
  REQUIRE(vec[3] == 4);
  REQUIRE(vec[4] == 6);
}

TEST_CASE(TEST_TAG "front", TEST_TAG) {
  ftl::vector<int> vec = { 2, 3 };

  REQUIRE(vec.front() == 2);
}

TEST_CASE(TEST_TAG "front const", TEST_TAG) {
  const ftl::vector<int> vec = { 2, 3 };

  REQUIRE(vec.front() == 2);
}

TEST_CASE(TEST_TAG "back", TEST_TAG) {
  ftl::vector<int> vec = { 2, 3 };

  REQUIRE(vec.back() == 3);
}

TEST_CASE(TEST_TAG "back const", TEST_TAG) {
  const ftl::vector<int> vec = { 2, 3 };

  REQUIRE(vec.back() == 3);
}

TEST_CASE(TEST_TAG "data", TEST_TAG) {
  ftl::vector<int> vec = { 2, 3 };

  REQUIRE(vec.data()[0] == 2);
  REQUIRE(vec.data()[1] == 3);
}

TEST_CASE(TEST_TAG "data const", TEST_TAG) {
  const ftl::vector<int> vec = { 2, 3 };

  REQUIRE(vec.data()[0] == 2);
  REQUIRE(vec.data()[1] == 3);
}


TEST_CASE(TEST_TAG "size", TEST_TAG) {
  const ftl::vector<int> vec = {};
  const ftl::vector<int> vec1(2);
  const ftl::vector<int> vec2 = { 1, 2, 3 };
  REQUIRE(vec.size() == 0);
  REQUIRE(vec1.size() == 2);
  REQUIRE(vec2.size() == 3);
}

TEST_CASE(TEST_TAG "resize", TEST_TAG) {
  ftl::vector<int> vec = {};
  vec.resize(20);

  REQUIRE(vec.size() == 20);
}

TEST_CASE(TEST_TAG "empty", TEST_TAG) {
  const ftl::vector<int> vec = {};
  const ftl::vector<int> vec1 = { 1, 2, 3 };

  REQUIRE(vec.empty() == true);
  REQUIRE(vec1.empty() == false);
}

TEST_CASE(TEST_TAG "swap", TEST_TAG) {
  ftl::vector<int> vec1 = { 5, 5, 5, 5, 5 };
  ftl::vector<int> vec2 = { 1337, 1337, 1337, 1337, 1337 };
  vec1.swap(vec2);

  REQUIRE(vec1 == ftl::vector<int>{ 1337, 1337, 1337, 1337, 1337 });
  REQUIRE(vec2 == ftl::vector<int>{ 5, 5, 5, 5, 5 });
}

TEST_CASE(TEST_TAG "push_back", TEST_TAG) {
  ftl::vector<int> vec1 = { 5, 5, 5, 5, 5 };
  vec1.push_back(20);
  REQUIRE(vec1.back() == 20);
}

TEST_CASE(TEST_TAG "emplace_back trivial type", TEST_TAG) {
  ftl::vector<int> vec1 = { 5, 5, 5, 5, 5 };
  vec1.emplace_back(20);
  REQUIRE(vec1.back() == 20);
}

// TODO: test with custom class with non-trivial constructor

TEST_CASE(TEST_TAG "operator= const reference", TEST_TAG) {
  ftl::vector<int> vec1 = { 5, 5, 5, 5, 5 };
  ftl::vector<int> vec2;
  vec2 = vec1;
  REQUIRE(vec1 == vec2);
}

TEST_CASE(TEST_TAG "operator= rvalue reference", TEST_TAG) {
  ftl::vector<int> vec1;
  vec1 = ftl::vector<int>{ 5, 5, 5, 5, 5 };
  REQUIRE(vec1 == ftl::vector<int>{ 5, 5, 5, 5, 5 });
}

TEST_CASE(TEST_TAG "assign value", TEST_TAG) {
  ftl::vector<int> vec1;
  vec1.assign(static_cast<std::size_t>(5), 5);
  REQUIRE(vec1 == ftl::vector<int>{ 5, 5, 5, 5, 5 });
}

TEST_CASE(TEST_TAG "assign initializer_list", TEST_TAG) {
  ftl::vector<int> vec1;
  vec1.assign({ 5, 5, 5, 5, 5 });
  REQUIRE(vec1 == ftl::vector<int>{ 5, 5, 5, 5, 5 });
}

TEST_CASE(TEST_TAG "assign iterators", TEST_TAG) {
  ftl::vector<int> vec1;
  ftl::array<int, 5> arr = { 1, 2, 3, 4, 5 };
  vec1.assign(arr.begin(), arr.end());
  REQUIRE(vec1 == ftl::vector<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "at", TEST_TAG) {
  ftl::vector<int> vec1 = { 1, 2, 3, 4, 5 };
  REQUIRE(vec1.at(3) == 4);
}

TEST_CASE(TEST_TAG "at const", TEST_TAG) {
  const ftl::vector<int> vec1 = { 1, 2, 3, 4, 5 };
  REQUIRE(vec1.at(3) == 4);
}

TEST_CASE(TEST_TAG "at out of range", TEST_TAG) {
  const ftl::vector<int> vec1 = { 1, 2, 3, 4, 5 };
  REQUIRE_THROWS(vec1.at(120));
  REQUIRE(vec1.at(3) == 4);
}


TEST_CASE(TEST_TAG "iter", TEST_TAG) {
  ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  [[maybe_unused]] auto iter = vec.iter();
}

TEST_CASE(TEST_TAG "iter const", TEST_TAG) {
  const ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  [[maybe_unused]] auto iter = vec.iter();
}

TEST_CASE(TEST_TAG "range-based for loop", TEST_TAG) {
  ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  for (auto &x : vec) { x = 7; }

  REQUIRE(vec == ftl::vector<int>{ 7, 7, 7, 7, 7 });
}

TEST_CASE(TEST_TAG "range-based for loop const", TEST_TAG) {
  ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  for ([[maybe_unused]] const auto &x : vec) {}
}

TEST_CASE(TEST_TAG "operator==", TEST_TAG) {
  const ftl::vector<int> vec1 = { 1, 2, 3, 4, 5 };
  const ftl::vector<int> vec2 = { 1, 2, 3, 4, 5 };

  REQUIRE(vec1 == vec2);
}

TEST_CASE(TEST_TAG "operator!=", TEST_TAG) {
  const ftl::vector<int> vec1 = { 1, 2, 3, 4, 5 };
  const ftl::vector<int> vec2 = { 1, 2, 3, 4, 5 };

  REQUIRE_FALSE(vec1 != vec2);
}

TEST_CASE(TEST_TAG "operator<", TEST_TAG) {
  const ftl::vector<int> vec1 = { 1, 2, 3, 4, 5 };
  const ftl::vector<int> vec2 = { 5, 2, 3, 4, 5 };

  REQUIRE(vec1 < vec2);
}

TEST_CASE(TEST_TAG "operator<=", TEST_TAG) {
  const ftl::vector<int> vec1 = { 1, 2, 3, 4, 5 };
  const ftl::vector<int> vec2 = { 5, 2, 3, 4, 5 };

  REQUIRE(vec1 <= vec2);
}

TEST_CASE(TEST_TAG "operator>", TEST_TAG) {
  const ftl::vector<int> vec1 = { 6, 2, 3, 4, 5 };
  const ftl::vector<int> vec2 = { 5, 2, 3, 4, 5 };

  REQUIRE(vec1 > vec2);
}

TEST_CASE(TEST_TAG "operator>=", TEST_TAG) {
  const ftl::vector<int> vec1 = { 5, 2, 3, 4, 5 };
  const ftl::vector<int> vec2 = { 5, 2, 3, 4, 5 };

  REQUIRE(vec1 >= vec2);
}

