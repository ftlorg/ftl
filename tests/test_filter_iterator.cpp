#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>
#include <vector>
#include <list>

#define TEST_TAG "[filter_iterator]"

TEST_CASE(TEST_TAG "map collect", TEST_TAG) {
  ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  auto mapped_vec = vec.iter().filter([](const auto &x) { return x % 2 == 0; }).collect<std::vector<int>>();

  REQUIRE(mapped_vec == ftl::vector<int>{ 2, 4 });
}

//TEST_CASE(TEST_TAG "map collect const", TEST_TAG) {
//  constexpr std::size_t size = 5;
//  const ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };
//
//  auto mapped_arr = arr.iter().map([](const auto &x) { return x * x; }).collect<ftl::array<int, size>>();
//
//  REQUIRE(mapped_arr == ftl::array<int, size>{ 1, 4, 9, 16, 25 });
//}
//
//TEST_CASE(TEST_TAG "collect to std::vector", TEST_TAG) {
//  constexpr std::size_t size = 5;
//  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };
//
//  auto mapped_arr = arr.iter().map([](const auto &x) { return x * x; }).collect<std::vector<int>>();
//
//  REQUIRE(mapped_arr == std::vector<int>{ 1, 4, 9, 16, 25 });
//}
//
//TEST_CASE(TEST_TAG "collect const to std::vector", TEST_TAG) {
//  constexpr std::size_t size = 5;
//  const ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };
//
//  auto mapped_arr = arr.iter().map([](const auto &x) { return x * x; }).collect<std::vector<int>>();
//
//  REQUIRE(mapped_arr == std::vector<int>{ 1, 4, 9, 16, 25 });
//}
//
//TEST_CASE(TEST_TAG "collect to std::list", TEST_TAG) {
//  constexpr std::size_t size = 5;
//  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };
//
//  auto mapped_arr = arr.iter().map([](const auto &x) { return x * x; }).collect<std::list<int>>();
//
//  REQUIRE(mapped_arr == std::list<int>{ 1, 4, 9, 16, 25 });
//}
//
//TEST_CASE(TEST_TAG "collect const to std::list", TEST_TAG) {
//  constexpr std::size_t size = 5;
//  const ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };
//
//  auto mapped_arr = arr.iter().map([](const auto &x) { return x * x; }).collect<std::list<int>>();
//
//  REQUIRE(mapped_arr == std::list<int>{ 1, 4, 9, 16, 25 });
//}
//
//TEST_CASE(TEST_TAG "chain map", TEST_TAG) {
//  constexpr std::size_t size = 5;
//  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };
//
//  auto mapped_arr = arr.iter()
//                      .map([](const auto &x) { return x * x; })
//                      .map([](const auto &x) { return 2 * x; })
//                      .collect<ftl::array<int, size>>();
//
//  REQUIRE(mapped_arr == ftl::array<int, size>{ 2, 8, 18, 32, 50 });
//}
//
//TEST_CASE(TEST_TAG "chain map const", TEST_TAG) {
//  constexpr std::size_t size = 5;
//  const ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };
//
//  auto mapped_arr = arr.iter()
//                      .map([](const auto &x) { return x * x; })
//                      .map([](const auto &x) { return 2 * x; })
//                      .collect<ftl::array<int, size>>();
//
//  REQUIRE(mapped_arr == ftl::array<int, size>{ 2, 8, 18, 32, 50 });
//}
