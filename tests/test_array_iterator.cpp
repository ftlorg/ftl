#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

TEST_CASE("next", "[array_iterator]")
{
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  auto iter = arr.iter();
  REQUIRE(arr[1] == *iter.next());
}

TEST_CASE("next const", "[array_iterator]")
{
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  auto iter = arr.iter();
  REQUIRE(arr[1] == *iter.next());
}

TEST_CASE("map", "[array_iterator]")
{
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  auto mapped_arr = arr.iter().map([](const auto &x) {
                                return x * x;
                              })
                      .collect<ftl::array<int, size>>();

  REQUIRE(mapped_arr == ftl::array<int, size>{ 1, 4, 9, 16, 25 });
}

TEST_CASE("chain map", "[array_iterator]")
{
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  auto mapped_arr = arr.iter().map([](const auto &x) {
                                return x * x;
                              })
                      .map([](const auto &x) {
                        return 2 * x;
                      })
                      .collect<ftl::array<int, size>>();

  REQUIRE(mapped_arr == ftl::array<int, size>{ 2, 8, 18, 32, 50 });
}

//TEST_CASE("map const", "[array_iterator]")
//{
//  constexpr std::size_t size = 5;
//  const ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };
//
//  auto mapped_arr = arr.iter().map([](const auto &x) {
//                                return x * x;
//                              })
//                      .collect<ftl::array<int, size>>();
//
//  REQUIRE(mapped_arr == ftl::array<int, size>{ 1, 4, 9, 16, 25 });
//}
