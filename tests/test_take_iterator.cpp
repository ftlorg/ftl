#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

#define TEST_TAG "[take_iterator]"

TEST_CASE(TEST_TAG "take collect", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().take(5).collect<ftl::array<int, size>>();

  REQUIRE(mapped_arr == ftl::array<int, size>{ { 1, 2, 3, 4, 5 } });
}

TEST_CASE(TEST_TAG "take less collect", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().take(3).collect<ftl::array<int, 3>>();

  REQUIRE(mapped_arr == ftl::array<int, 3>{ { 1, 2, 3 } });
}

TEST_CASE(TEST_TAG "take more collect", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  // TODO: Clamp to container.size() or runtime error? Currently clamping.
  auto mapped_arr = arr.iter().take(6).collect<ftl::array<int, 5>>();

  REQUIRE(mapped_arr == ftl::array<int, 5>{ { 1, 2, 3, 4, 5 } });
}