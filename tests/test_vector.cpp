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

TEST_CASE(TEST_TAG "fill", TEST_TAG) {
  ftl::vector<int> vec1(5);
  ftl::vector<int> vec2 = { 1337, 1337, 1337, 1337, 1337 };
  vec1.fill(1337);

  REQUIRE(vec1 == vec2);
}

TEST_CASE(TEST_TAG "swap", TEST_TAG) {
  ftl::vector<int> arr1 = { 5, 5, 5, 5, 5 };
  ftl::vector<int> arr2 = { 1337, 1337, 1337, 1337, 1337 };
  arr1.swap(arr2);

  REQUIRE(arr1 == ftl::vector<int>{ 1337, 1337, 1337, 1337, 1337 });
  REQUIRE(arr2 == ftl::vector<int>{ 5, 5, 5, 5, 5 });
}
//
// TEST_CASE(TEST_TAG "iter", TEST_TAG) {
//  constexpr std::size_t size = 5;
//  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };
//
//  [[maybe_unused]] auto iter = arr.iter();
//}
//
// TEST_CASE(TEST_TAG "iter const", TEST_TAG) {
//  constexpr std::size_t size = 5;
//  const ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };
//
//  [[maybe_unused]] auto iter = arr.iter();
//}
//
// TEST_CASE(TEST_TAG "range-based for loop", TEST_TAG) {
//  constexpr std::size_t size = 5;
//  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };
//
//  for (auto &x : arr) { x = 7; }
//
//  REQUIRE(arr == ftl::array<int, size>{ 7, 7, 7, 7, 7 });
//}
//
// TEST_CASE(TEST_TAG "range-based for loop const", TEST_TAG) {
//  constexpr std::size_t size = 5;
//  const ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };
//
//  for ([[maybe_unused]] const auto &x : arr) {}
//}
//
// TEST_CASE(TEST_TAG "operator==", TEST_TAG) {
//  constexpr std::size_t size = 5;
//  ftl::array<int, size> arr1 = { 1, 2, 3, 4, 5 };
//  ftl::array<int, size> arr2 = { 1, 2, 3, 4, 5 };
//
//  REQUIRE(arr1 == arr2);
//}
//
// TEST_CASE(TEST_TAG "operator!=", TEST_TAG) {
//  constexpr std::size_t size = 5;
//  ftl::array<int, size> arr1 = { 1, 2, 3, 4, 5 };
//  ftl::array<int, size> arr2 = { 5, 2, 3, 4, 5 };
//
//  REQUIRE(arr1 != arr2);
//}
//
// TEST_CASE(TEST_TAG "operator<", TEST_TAG) {
//  constexpr std::size_t size = 5;
//  ftl::array<int, size> arr1 = { 1, 2, 3, 4, 5 };
//  ftl::array<int, size> arr2 = { 5, 2, 3, 4, 5 };
//
//  REQUIRE(arr1 < arr2);
//}
//
// TEST_CASE(TEST_TAG "operator<=", TEST_TAG) {
//  constexpr std::size_t size = 5;
//  ftl::array<int, size> arr1 = { 1, 2, 3, 4, 5 };
//  ftl::array<int, size> arr2 = { 5, 2, 3, 4, 5 };
//
//  REQUIRE(arr1 <= arr2);
//}
//
// TEST_CASE(TEST_TAG "operator>", TEST_TAG) {
//  constexpr std::size_t size = 5;
//  ftl::array<int, size> arr1 = { 6, 2, 3, 4, 5 };
//  ftl::array<int, size> arr2 = { 5, 2, 3, 4, 5 };
//
//  REQUIRE(arr1 > arr2);
//}
//
// TEST_CASE(TEST_TAG "operator>=", TEST_TAG) {
//  constexpr std::size_t size = 5;
//  ftl::array<int, size> arr1 = { 5, 2, 3, 4, 5 };
//  ftl::array<int, size> arr2 = { 5, 2, 3, 4, 5 };
//
//  REQUIRE(arr1 >= arr2);
//}