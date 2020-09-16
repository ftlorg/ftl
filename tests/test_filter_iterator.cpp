#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>
#include <vector>
#include <list>

#define TEST_TAG "[filter_iterator]"

TEST_CASE(TEST_TAG "filter collect", TEST_TAG) {
  ftl::vector<int> vec = { 1, 2, 3, 4, 5, 6, 12 };

  auto f_vec = vec.iter()
                 .filter([](const auto &x) { return x % 2 == 0; })
                 .filter([](const auto &x) { return x % 3 == 0; })
                 .collect<std::vector<int>>();

  REQUIRE(f_vec == ftl::vector<int>{ 6, 12 });
}

TEST_CASE(TEST_TAG "const filter collect", TEST_TAG) {
  const ftl::vector<int> vec = { 1, 2, 3, 4, 5, 6, 12 };

  auto f_vec = vec.iter()
                 .filter([](const auto &x) { return x % 2 == 0; })
                 .filter([](const auto &x) { return x % 3 == 0; })
                 .collect<std::vector<int>>();

  REQUIRE(f_vec == ftl::vector<int>{ 6, 12 });
}

TEST_CASE(TEST_TAG "const filter collect to empty", TEST_TAG) {
  const ftl::vector<int> vec = { 1, 3, 4, 5 };

  auto f_vec = vec.iter()
                 .filter([](const auto &x) { return x % 2 == 0; })
                 .filter([](const auto &x) { return x % 3 == 0; })
                 .collect<std::vector<int>>();

  REQUIRE(f_vec.empty());
}


TEST_CASE(TEST_TAG "filter after map", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter()
                      .map([](const auto &x) { return x * x; })
                      .filter([](const auto &x) { return x % 2 == 0; })
                      .collect<std::vector<int>>();

  REQUIRE(mapped_arr == std::vector<int>{ 4, 16 });
}

TEST_CASE(TEST_TAG "filter const ftl::list", TEST_TAG) {
  const ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto f_list = list.iter().filter([](const auto &x) { return x % 2 == 0; }).collect<ftl::vector<int>>();

  REQUIRE(f_list == ftl::vector<int>{ 2, 4 });
}

TEST_CASE(TEST_TAG "filter ftl::list", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto f_list = list.iter().filter([](const auto &x) { return x % 2 == 0; }).collect<ftl::list<int>>();

  REQUIRE(f_list == ftl::list<int>{ 2, 4 });
}

TEST_CASE(TEST_TAG "filter const ftl::array", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().filter([](const auto &x) { return x > 3; }).collect<std::list<int>>();

  REQUIRE(mapped_arr == std::list<int>{ 4, 5 });
}

TEST_CASE(TEST_TAG "filter ftl::array", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().filter([](const auto &x) { return x > 3; }).collect<std::list<int>>();

  REQUIRE(mapped_arr == std::list<int>{ 4, 5 });
}

TEST_CASE(TEST_TAG "chain inspect and filter", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter()
                      .inspect([](const auto &x) { INFO("Inspecting x = " << x) })
                      .filter([](const auto &x) { return x % 2; })
                      .collect<ftl::vector<int>>();

  REQUIRE(mapped_arr == ftl::vector<int>{ 1, 3, 5 });
}

TEST_CASE(TEST_TAG "chain enumerate and filter", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter()
                      .enumerate()
                      .filter([](const auto &x) { return std::get<0>(x) > 2; })
                      .map([](const auto &x) { return std::get<1>(x); })
                      .collect<ftl::vector<int>>();

  REQUIRE(mapped_arr == ftl::vector<int>{ 4, 5 });
}