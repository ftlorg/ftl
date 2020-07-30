#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>
#include <array>

#define TEST_TAG "[array]"

TEST_CASE(TEST_TAG "to_array", TEST_TAG) {
  constexpr std::size_t size = 5;
  std::array<int, size> arr = { 1, 2, 3, 4, 6 };

  const auto converted_arr = ftl::to_array(arr);

  REQUIRE(converted_arr[0] == 1);
  REQUIRE(converted_arr[1] == 2);
  REQUIRE(converted_arr[2] == 3);
  REQUIRE(converted_arr[3] == 4);
  REQUIRE(converted_arr[4] == 6);
}

TEST_CASE(TEST_TAG "operator[]", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { 1, 2, 3, 4, 6 };

  REQUIRE(arr[0] == 1);
  REQUIRE(arr[1] == 2);
  REQUIRE(arr[2] == 3);
  REQUIRE(arr[3] == 4);
  REQUIRE(arr[4] == 6);
}

TEST_CASE(TEST_TAG "operator[] const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { 1, 2, 3, 4, 6 };

  REQUIRE(arr[0] == 1);
  REQUIRE(arr[1] == 2);
  REQUIRE(arr[2] == 3);
  REQUIRE(arr[3] == 4);
  REQUIRE(arr[4] == 6);
}

TEST_CASE(TEST_TAG "front", TEST_TAG) {
  constexpr std::size_t size = 2;
  ftl::array<int, size> arr = { 2, 3 };

  REQUIRE(arr.front() == 2);
}

TEST_CASE(TEST_TAG "front const", TEST_TAG) {
  constexpr std::size_t size = 2;
  const ftl::array<int, size> arr = { 2, 3 };

  REQUIRE(arr.front() == 2);
}

TEST_CASE(TEST_TAG "back", TEST_TAG) {
  constexpr std::size_t size = 2;
  ftl::array<int, size> arr = { 2, 3 };

  REQUIRE(arr.back() == 3);
}

TEST_CASE(TEST_TAG "back const", TEST_TAG) {
  constexpr std::size_t size = 2;
  const ftl::array<int, size> arr = { 2, 3 };

  REQUIRE(arr.back() == 3);
}

TEST_CASE(TEST_TAG "data", TEST_TAG) {
  constexpr std::size_t size = 2;
  ftl::array<int, size> arr = { 2, 3 };

  REQUIRE(arr.data()[0] == 2);
  REQUIRE(arr.data()[1] == 3);
}

TEST_CASE(TEST_TAG "data const", TEST_TAG) {
  constexpr std::size_t size = 2;
  const ftl::array<int, size> arr = { 2, 3 };

  REQUIRE(arr.data()[0] == 2);
  REQUIRE(arr.data()[1] == 3);
}

TEST_CASE(TEST_TAG "size", TEST_TAG) {
  constexpr std::size_t size = 2;
  const ftl::array<int, size> arr = {};

  REQUIRE(arr.size() == 2);
}

TEST_CASE(TEST_TAG "max_size", TEST_TAG) {
  constexpr std::size_t size = 2;
  const ftl::array<int, size> arr = {};

  REQUIRE(arr.max_size() == 2);
}

TEST_CASE(TEST_TAG "empty", TEST_TAG) {
  constexpr std::size_t size = 1;
  const ftl::array<int, size> arr = {};

  REQUIRE(arr.empty() == false);
}

TEST_CASE(TEST_TAG "fill", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr1 = {};
  ftl::array<int, size> arr2 = { 1337, 1337, 1337, 1337, 1337 };
  arr1.fill(1337);

  REQUIRE(arr1 == arr2);
}

TEST_CASE(TEST_TAG "swap", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr1 = { 5, 5, 5, 5, 5 };
  ftl::array<int, size> arr2 = { 1337, 1337, 1337, 1337, 1337 };
  arr1.swap(arr2);

  REQUIRE(arr1 == ftl::array<int, size>{ 1337, 1337, 1337, 1337, 1337 });
  REQUIRE(arr2 == ftl::array<int, size>{ 5, 5, 5, 5, 5 });
}

TEST_CASE(TEST_TAG "iter", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  [[maybe_unused]] auto iter = arr.iter();
}

TEST_CASE(TEST_TAG "iter const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  [[maybe_unused]] auto iter = arr.iter();
}

TEST_CASE(TEST_TAG "range-based for loop", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  for (auto &x : arr) { x = 7; }

  REQUIRE(arr == ftl::array<int, size>{ 7, 7, 7, 7, 7 });
}

TEST_CASE(TEST_TAG "range-based for loop const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  for ([[maybe_unused]] const auto &x : arr) {}
}

TEST_CASE(TEST_TAG "operator==", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr1 = { 1, 2, 3, 4, 5 };
  ftl::array<int, size> arr2 = { 1, 2, 3, 4, 5 };

  REQUIRE(arr1 == arr2);
}

TEST_CASE(TEST_TAG "operator!=", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr1 = { 1, 2, 3, 4, 5 };
  ftl::array<int, size> arr2 = { 5, 2, 3, 4, 5 };

  REQUIRE(arr1 != arr2);
}

TEST_CASE(TEST_TAG "operator<", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr1 = { 1, 2, 3, 4, 5 };
  ftl::array<int, size> arr2 = { 5, 2, 3, 4, 5 };

  REQUIRE(arr1 < arr2);
}

TEST_CASE(TEST_TAG "operator<=", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr1 = { 1, 2, 3, 4, 5 };
  ftl::array<int, size> arr2 = { 5, 2, 3, 4, 5 };

  REQUIRE(arr1 <= arr2);
}

TEST_CASE(TEST_TAG "operator>", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr1 = { 6, 2, 3, 4, 5 };
  ftl::array<int, size> arr2 = { 5, 2, 3, 4, 5 };

  REQUIRE(arr1 > arr2);
}

TEST_CASE(TEST_TAG "operator>=", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr1 = { 5, 2, 3, 4, 5 };
  ftl::array<int, size> arr2 = { 5, 2, 3, 4, 5 };

  REQUIRE(arr1 >= arr2);
}