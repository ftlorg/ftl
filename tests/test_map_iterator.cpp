#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>
#include <vector>
#include <list>

#define TEST_TAG "[map_iterator]"

TEST_CASE(TEST_TAG "map collect", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().map([](const auto &x) { return x * x; }).collect<ftl::array<int, size>>();

  REQUIRE(mapped_arr == ftl::array<int, size>{ { 1, 4, 9, 16, 25 } });
}

TEST_CASE(TEST_TAG "map collect const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().map([](const auto &x) { return x * x; }).collect<ftl::array<int, size>>();

  REQUIRE(mapped_arr == ftl::array<int, size>{ { 1, 4, 9, 16, 25 } });
}

TEST_CASE(TEST_TAG "collect to std::vector", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().map([](const auto &x) { return x * x; }).collect<std::vector<int>>();

  REQUIRE(mapped_arr == std::vector<int>{ 1, 4, 9, 16, 25 });
}

TEST_CASE(TEST_TAG "collect const to std::vector", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().map([](const auto &x) { return x * x; }).collect<std::vector<int>>();

  REQUIRE(mapped_arr == std::vector<int>{ 1, 4, 9, 16, 25 });
}

TEST_CASE(TEST_TAG "collect to std::list", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().map([](const auto &x) { return x * x; }).collect<std::list<int>>();

  REQUIRE(mapped_arr == std::list<int>{ 1, 4, 9, 16, 25 });
}

TEST_CASE(TEST_TAG "collect const to std::list", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().map([](const auto &x) { return x * x; }).collect<std::list<int>>();

  REQUIRE(mapped_arr == std::list<int>{ 1, 4, 9, 16, 25 });
}

TEST_CASE(TEST_TAG "chain map", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter()
                      .map([](const auto &x) { return x * x; })
                      .map([](const auto &x) { return 2 * x; })
                      .collect<ftl::array<int, size>>();

  REQUIRE(mapped_arr == ftl::array<int, size>{ { 2, 8, 18, 32, 50 } });
}

TEST_CASE(TEST_TAG "chain map const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter()
                      .map([](const auto &x) { return x * x; })
                      .map([](const auto &x) { return 2 * x; })
                      .collect<ftl::array<int, size>>();

  REQUIRE(mapped_arr == ftl::array<int, size>{ { 2, 8, 18, 32, 50 } });
}

TEST_CASE(TEST_TAG "sum", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto sum = arr.iter().map([](const auto &x) { return x * x; }).map([](const auto &x) { return 2 * x; }).sum();

  REQUIRE(sum == 110);
}