#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>
#include <vector>
#include <list>

#define TEST_TAG "[array_container_iterator]"

TEST_CASE(TEST_TAG "collect", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().collect<ftl::array<int, size>>();

  constexpr std::size_t size2 = 3;
  ftl::array<int, size2> arr2 = { { 1, 2, 3 } };

  auto mapped_arr2 = arr2.iter().collect<ftl::array<int, size2>>();

  REQUIRE(mapped_arr == ftl::array<int, size>{ { 1, 2, 3, 4, 5 } });
  REQUIRE(mapped_arr2 == ftl::array<int, size2>{ { 1, 2, 3 } });
}

TEST_CASE(TEST_TAG "collect to std::vector", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().collect<std::vector<int>>();

  REQUIRE(mapped_arr == std::vector<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect const to std::vector", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().collect<std::vector<int>>();

  REQUIRE(mapped_arr == std::vector<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect to std::list", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().collect<std::list<int>>();

  REQUIRE(mapped_arr == std::list<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect const to std::list", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().collect<std::list<int>>();

  REQUIRE(mapped_arr == std::list<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().collect<ftl::array<int, size>>();

  constexpr std::size_t size2 = 3;
  const ftl::array<int, size2> arr2 = { { 1, 2, 3 } };

  auto mapped_arr2 = arr2.iter().collect<ftl::array<int, size2>>();

  REQUIRE(mapped_arr == ftl::array<int, size>{ { 1, 2, 3, 4, 5 } });
  REQUIRE(mapped_arr2 == ftl::array<int, size2>{ { 1, 2, 3 } });
}

TEST_CASE(TEST_TAG "count", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  REQUIRE(5 == arr.iter().count());
}

TEST_CASE(TEST_TAG "count const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  REQUIRE(5 == arr.iter().count());
}

TEST_CASE(TEST_TAG "begin", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto iter = arr.iter().begin();
  REQUIRE(arr[0] == *iter);

  ++iter;
  REQUIRE(arr[1] == *iter);
}

TEST_CASE(TEST_TAG "begin const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto iter = arr.iter().begin();
  REQUIRE(arr[0] == *iter);

  ++iter;
  REQUIRE(arr[1] == *iter);
}

TEST_CASE(TEST_TAG "cbegin", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto iter = arr.iter().cbegin();
  REQUIRE(arr[0] == *iter);

  ++iter;
  REQUIRE(arr[1] == *iter);
}

TEST_CASE(TEST_TAG "cbegin const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto iter = arr.iter().cbegin();
  REQUIRE(arr[0] == *iter);

  ++iter;
  REQUIRE(arr[1] == *iter);
}

TEST_CASE(TEST_TAG "operator++", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

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

  ++iter;
  REQUIRE(iter == iter.end());
}

TEST_CASE(TEST_TAG "operator++ const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

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

TEST_CASE(TEST_TAG "operator+=", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto iter = arr.iter();
  iter += 4;
  REQUIRE(arr[4] == *iter);
}


TEST_CASE(TEST_TAG "all elements satisfy predicate", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 2, 4, 6, 8, 10 } };

  auto elem = arr.iter().all([](const auto &element) { return element % 2 == 0; });

  REQUIRE(elem);
}

TEST_CASE(TEST_TAG "not all elements satisfy predicate", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 7, 3, 11, 5 } };

  auto elem = arr.iter().all([](const auto &element) { return element % 2 == 0; });

  REQUIRE_FALSE(elem);
}