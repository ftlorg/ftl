#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

#define TEST_TAG "[enumerate_iterator]"

TEST_CASE(TEST_TAG "enumerate", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  for (const auto &[index, item] : arr.iter().enumerate()) {
    REQUIRE(arr[index] == item);
    REQUIRE(&arr[index] == &item);
  }
}

TEST_CASE(TEST_TAG "enumerate const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  for (const auto &[index, item] : arr.iter().enumerate()) {
    REQUIRE(arr[index] == item);
    REQUIRE(&arr[index] == &item);
  }
}

TEST_CASE(TEST_TAG "preincrement", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  auto iter = arr.iter().enumerate();
  REQUIRE(*iter == std::make_tuple(0, 1));

  ++iter;
  REQUIRE(*iter == std::make_tuple(1, 2));

  ++iter;
  REQUIRE(*iter == std::make_tuple(2, 3));

  ++iter;
  REQUIRE(*iter == std::make_tuple(3, 4));

  ++iter;
  REQUIRE(*iter == std::make_tuple(4, 5));
}

TEST_CASE(TEST_TAG "preincrement const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  auto iter = arr.iter().enumerate();
  REQUIRE(*iter == std::make_tuple(0, 1));

  ++iter;
  REQUIRE(*iter == std::make_tuple(1, 2));

  ++iter;
  REQUIRE(*iter == std::make_tuple(2, 3));

  ++iter;
  REQUIRE(*iter == std::make_tuple(3, 4));

  ++iter;
  REQUIRE(*iter == std::make_tuple(4, 5));
}

TEST_CASE(TEST_TAG "enumerate with side effects", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  for (auto [index, item] : arr.iter().enumerate()) { item = static_cast<int>(size - index); }

  REQUIRE(arr == ftl::array<int, size>{ 5, 4, 3, 2, 1 });
}

TEST_CASE(TEST_TAG "map enumerate", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  for (const auto &[index, item] : arr.iter().map([](const auto &x) { return 2 * x; }).enumerate()) {
    REQUIRE(2 * arr[index] == item);
  }
}

TEST_CASE(TEST_TAG "map enumerate const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  for (const auto &[index, item] : arr.iter().map([](const auto &x) { return 2 * x; }).enumerate()) {
    REQUIRE(2 * arr[index] == item);
  }
}