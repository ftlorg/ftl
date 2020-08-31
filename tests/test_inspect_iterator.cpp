#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>
#include <tuple>

#define TEST_TAG "[inspect_iterator]"

TEST_CASE(TEST_TAG "inspect map", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter()
                       .inspect([](const auto &x) { INFO("Inspecting x = " << x) })
                       .map([](const auto &x) { return x * x; })
                       .collect<ftl::list<int>>();

  // Inspect doesn't allow for side effects. This doesn't compile.
  //[[maybe_unused]] auto mapped_list2
  //  = list.iter().inspect([](auto &x) { x = 3; }).map([](const auto &x) { return x * x; }).collect<ftl::list<int>>();

  REQUIRE(mapped_list == ftl::list<int>{ 1, 4, 9, 16, 25 });
}

TEST_CASE(TEST_TAG "inspect map const", TEST_TAG) {
  const ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter()
                       .inspect([](const auto &x) { INFO("Inspecting x = " << x) })
                       .map([](const auto &x) { return x * x; })
                       .collect<ftl::list<int>>();

  // Inspect doesn't allow for side effects. This doesn't compile.
  // [[maybe_unused]] auto mapped_list2
  //   = list.iter().inspect([](auto &x) { x = 3; }).map([](const auto &x) { return x * x; }).collect<ftl::list<int>>();

  REQUIRE(mapped_list == ftl::list<int>{ 1, 4, 9, 16, 25 });
}

TEST_CASE(TEST_TAG "map inspect map", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter()
                       .map([](const auto &x) { return x; })
                       .inspect([](const auto &x) { INFO("Inspecting x = " << x) })
                       .map([](const auto &x) { return x * x; })
                       .collect<ftl::list<int>>();

  REQUIRE(mapped_list == ftl::list<int>{ 1, 4, 9, 16, 25 });
}

TEST_CASE(TEST_TAG "map inspect map const", TEST_TAG) {
  const ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter()
                       .map([](const auto &x) { return x; })
                       .inspect([](const auto &x) { INFO("Inspecting x = " <<x) })
                       .map([](const auto &x) { return x * x; })
                       .collect<ftl::list<int>>();

  REQUIRE(mapped_list == ftl::list<int>{ 1, 4, 9, 16, 25 });
}

TEST_CASE(TEST_TAG "map enumerate inspect map", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter()
                       .map([](const auto &x) { return x; })
                       .enumerate()
                       .inspect([](const auto &x) { INFO("Inspecting x = " << std::get<0>(x)) })
                       .map([](const auto &x) { return std::get<0>(x) * std::get<0>(x); })
                       .collect<ftl::list<int>>();

  REQUIRE(mapped_list == ftl::list<int>{ 0, 1, 4, 9, 16 });
}

TEST_CASE(TEST_TAG "map enumerate inspect map const", TEST_TAG) {
  const ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter()
                       .map([](const auto &x) { return x; })
                       .enumerate()
                       .inspect([](const auto &x) { INFO("Inspecting x = " << std::get<0>(x)) })
                       .map([](const auto &x) { return std::get<0>(x) * std::get<0>(x); })
                       .collect<ftl::list<int>>();

  REQUIRE(mapped_list == ftl::list<int>{ 0, 1, 4, 9, 16 });
}