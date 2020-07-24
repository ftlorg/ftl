#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

TEST_CASE("collect", "[iterator]") {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  auto mapped_arr = arr.iter().collect<ftl::array<int, size>>();

  constexpr std::size_t size2 = 3;
  ftl::array<int, size2> arr2 = { 1, 2, 3 };

  auto mapped_arr2 = arr2.iter().collect<ftl::array<int, size2>>();

  REQUIRE(mapped_arr == ftl::array<int, size>{ 1, 2, 3, 4, 5 });
  REQUIRE(mapped_arr2 == ftl::array<int, size2>{ 1, 2, 3 });
}

TEST_CASE("collect const", "[iterator]") {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  auto mapped_arr = arr.iter().collect<ftl::array<int, size>>();

  constexpr std::size_t size2 = 3;
  const ftl::array<int, size2> arr2 = { 1, 2, 3 };

  auto mapped_arr2 = arr2.iter().collect<ftl::array<int, size2>>();

  REQUIRE(mapped_arr == ftl::array<int, size>{ 1, 2, 3, 4, 5 });
  REQUIRE(mapped_arr2 == ftl::array<int, size2>{ 1, 2, 3 });
}
