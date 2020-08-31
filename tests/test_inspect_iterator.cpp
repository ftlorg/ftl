#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

#define TEST_TAG "[inspect_iterator]"

TEST_CASE(TEST_TAG "inspect map", TEST_TAG) {
  ftl::list<int> arr = { 1, 2, 3, 4, 5 };

  auto mapped_arr = arr.iter()
                      .inspect([](const auto &x) { INFO("Inspecting x = " << x); })
                      .map([](const auto &x) { return x * x; })
                      .collect<ftl::list<int>>();

  // Inspect doesn't allow for side effects. This doesn't compile.
  // [[maybe_unused]] auto mapped_arr2
  //   = arr.iter().inspect([](auto &x) { x = 3; }).map([](const auto &x) { return x * x; }).collect<ftl::array<int,
  //   size>>();

  REQUIRE(mapped_arr == ftl::list<int>{ 1, 4, 9, 16, 25 });
}

TEST_CASE(TEST_TAG "inspect map const", TEST_TAG) {
  const ftl::list<int> arr = { 1, 2, 3, 4, 5 };

  auto mapped_arr = arr.iter()
                      .inspect([](const auto &x) { INFO("Inspecting x = " << x); })
                      .map([](const auto &x) { return x * x; })
                      .collect<ftl::list<int>>();

  // Inspect doesn't allow for side effects. This doesn't compile.
  // [[maybe_unused]] auto mapped_arr2
  //   = arr.iter().inspect([](auto &x) { x = 3; }).map([](const auto &x) { return x * x; }).collect<ftl::array<int,
  //   size>>();

  REQUIRE(mapped_arr == ftl::list<int>{ 1, 4, 9, 16, 25 });
}