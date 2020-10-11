#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>
#include <vector>
#include <list>

#define TEST_TAG "[vector_container_iterator]"

TEST_CASE(TEST_TAG "collect", TEST_TAG) {
  ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  auto mapped_vec = vec.iter().collect<std::vector<int>>();

  ftl::vector<int> vec2 = { 1, 2, 3 };

  auto mapped_vec2 = vec2.iter().collect<std::vector<int>>();

  REQUIRE(mapped_vec == std::vector<int>{ 1, 2, 3, 4, 5 });
  REQUIRE(mapped_vec2 == std::vector<int>{ 1, 2, 3 });
}

TEST_CASE(TEST_TAG "collect const", TEST_TAG) {
  const ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  const auto mapped_vec = vec.iter().collect<std::vector<int>>();

  const ftl::vector<int> vec2 = { 1, 2, 3 };

  const auto mapped_vec2 = vec2.iter().collect<std::vector<int>>();

  REQUIRE(mapped_vec == std::vector<int>{ 1, 2, 3, 4, 5 });
  REQUIRE(mapped_vec2 == std::vector<int>{ 1, 2, 3 });
}

TEST_CASE(TEST_TAG "collect to std::vector", TEST_TAG) {
  ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  auto mapped_vec = vec.iter().collect<ftl::vector<int>>();

  REQUIRE(mapped_vec == std::vector<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect const to std::vector", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().collect<ftl::vector<int>>();

  REQUIRE(mapped_arr == std::vector<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect to std::list", TEST_TAG) {
  ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  auto mapped_arr = vec.iter().collect<std::list<int>>();

  REQUIRE(mapped_arr == std::list<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect const to std::list", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().collect<std::list<int>>();

  REQUIRE(mapped_arr == std::list<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect const to ftl::vector", TEST_TAG) {
  const ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  auto mapped_vec = vec.iter().collect<ftl::vector<int>>();

  const ftl::vector<int> vec2 = { 1, 2, 3 };

  auto mapped_vec2 = vec2.iter().collect<ftl::vector<int>>();

  REQUIRE(mapped_vec == ftl::vector<int>{ 1, 2, 3, 4, 5 });
  REQUIRE(mapped_vec2 == ftl::vector<int>{ 1, 2, 3 });
}

TEST_CASE(TEST_TAG "count", TEST_TAG) {
  ftl::vector<int> arr = { 1, 2, 3, 4, 5 };

  REQUIRE(5 == arr.iter().count());
}

TEST_CASE(TEST_TAG "count const", TEST_TAG) {
  const ftl::vector<int> arr = { 1, 2, 3, 4, 5 };

  REQUIRE(5 == arr.iter().count());
}

TEST_CASE(TEST_TAG "begin", TEST_TAG) {
  ftl::vector<int> arr = { 1, 2, 3, 4, 5 };

  auto iter = arr.iter().begin();

  REQUIRE(arr[0] == *iter);

  ++iter;
  REQUIRE(arr[1] == *iter);
}

TEST_CASE(TEST_TAG "begin const", TEST_TAG) {
  const ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  auto iter = vec.iter().begin();
  REQUIRE(vec[0] == *iter);

  ++iter;
  REQUIRE(vec[1] == *iter);
}

TEST_CASE(TEST_TAG "cbegin", TEST_TAG) {
  ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  auto iter = vec.iter().cbegin();
  REQUIRE(vec[0] == *iter);

  ++iter;
  REQUIRE(vec[1] == *iter);
}

TEST_CASE(TEST_TAG "cbegin const", TEST_TAG) {
  const ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  auto iter = vec.iter().cbegin();
  REQUIRE(vec[0] == *iter);

  ++iter;
  REQUIRE(vec[1] == *iter);
}

TEST_CASE(TEST_TAG "operator++", TEST_TAG) {
  ftl::vector<int> arr = { 1, 2, 3, 4, 5 };

  auto iter = arr.iter();
  REQUIRE(arr[0] == *iter);

  ++iter;
  REQUIRE(arr[1] == *iter);

  ++iter;
  REQUIRE(arr[2] == *iter);

  ++iter;
  REQUIRE(arr[3] == *iter);

  ++iter;
  REQUIRE(arr[4] == *iter);
}

TEST_CASE(TEST_TAG "operator++ const", TEST_TAG) {
  const ftl::vector<int> arr = { 1, 2, 3, 4, 5 };

  auto iter = arr.iter();
  REQUIRE(arr[0] == *iter);

  ++iter;
  REQUIRE(arr[1] == *iter);

  ++iter;
  REQUIRE(arr[2] == *iter);

  ++iter;
  REQUIRE(arr[3] == *iter);

  ++iter;
  REQUIRE(arr[4] == *iter);
}

TEST_CASE(TEST_TAG "collect into ftl::vector", TEST_TAG) {
  ftl::vector<int> vec = { 1, 2, 3, 4, 5 };
  ftl::vector<int> vec_result;
  vec.iter().collect_into(vec_result);

  REQUIRE(vec_result == ftl::vector<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect const into ftl::vector", TEST_TAG) {
  const ftl::vector<int> vec = { 1, 2, 3, 4, 5 };
  ftl::vector<int> vec_result;
  vec.iter().collect_into(vec_result);

  REQUIRE(vec_result == ftl::vector<int>{ 1, 2, 3, 4, 5 });
}
