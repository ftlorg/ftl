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
                       .inspect([](const auto &x) { INFO("Inspecting x = " << x) })
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
                       .map([](const auto &x) { return static_cast<int>(std::get<0>(x) * std::get<0>(x)); })
                       .collect<ftl::list<int>>();

  REQUIRE(mapped_list == ftl::list<int>{ 0, 1, 4, 9, 16 });
}

TEST_CASE(TEST_TAG "map enumerate inspect map const", TEST_TAG) {
  const ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter()
                       .map([](const auto &x) { return x; })
                       .enumerate()
                       .inspect([](const auto &x) { INFO("Inspecting x = " << std::get<0>(x)) })
                       .map([](const auto &x) { return static_cast<int>(std::get<0>(x) * std::get<0>(x)); })
                       .collect<ftl::list<int>>();

  REQUIRE(mapped_list == ftl::list<int>{ 0, 1, 4, 9, 16 });
}

TEST_CASE(TEST_TAG "inspect count", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  const auto size = list.iter().inspect([](const auto &x) { INFO("Inspecting x = " << std::get<0>(x)) }).count();

  REQUIRE(size == 5);
}

TEST_CASE(TEST_TAG "inspect count const", TEST_TAG) {
  const ftl::list<int> list = { 1, 2, 3, 4, 5 };

  const auto size = list.iter().inspect([](const auto &x) { INFO("Inspecting x = " << std::get<0>(x)) }).count();

  REQUIRE(size == 5);
}

TEST_CASE(TEST_TAG "preincrement", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto iter = list.iter().inspect([]([[maybe_unused]] const auto &x) {});
  REQUIRE(*iter == 1);

  ++iter;
  REQUIRE(*iter == 2);

  ++iter;
  REQUIRE(*iter == 3);

  ++iter;
  REQUIRE(*iter == 4);

  ++iter;
  REQUIRE(*iter == 5);
}

TEST_CASE(TEST_TAG "preincrement const", TEST_TAG) {
  const ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto iter = list.iter().inspect([]([[maybe_unused]] const auto &x) {});
  REQUIRE(*iter == 1);

  ++iter;
  REQUIRE(*iter == 2);

  ++iter;
  REQUIRE(*iter == 3);

  ++iter;
  REQUIRE(*iter == 4);

  ++iter;
  REQUIRE(*iter == 5);
}

TEST_CASE(TEST_TAG "inspect collect to std::vector", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter().inspect([]([[maybe_unused]] const auto &x) {}).collect<std::vector<int>>();

  REQUIRE(mapped_list == std::vector<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "inspect collect to std::vector const", TEST_TAG) {
  const ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter().inspect([]([[maybe_unused]] const auto &x) {}).collect<std::vector<int>>();

  REQUIRE(mapped_list == std::vector<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "inspect any", TEST_TAG) {
  ftl::list<std::string> arr = { { "red", "green", "blue" } };

  REQUIRE(arr.iter().inspect([](const auto &x) { INFO(x); }).any([](const auto &x) { return x == "red"; }) == true);
  REQUIRE(arr.iter().inspect([](const auto &x) { INFO(x); }).any([](const auto &x) { return x == "green"; }) == true);
  REQUIRE(arr.iter().inspect([](const auto &x) { INFO(x); }).any([](const auto &x) { return x == "blue"; }) == true);
}

TEST_CASE(TEST_TAG "inspect filter any", TEST_TAG) {
  ftl::list<std::string> arr = { { "red", "green", "blue" } };

  REQUIRE(arr.iter()
            .inspect([](const auto &x) { INFO(x); })
            .filter([](const auto &x) { return x != "green"; })
            .any([](const auto &x) { return x == "red"; })
          == true);
  REQUIRE(arr.iter()
            .inspect([](const auto &x) { INFO(x); })
            .filter([](const auto &x) { return x != "green"; })
            .any([](const auto &x) { return x == "green"; })
          == false);
  REQUIRE(arr.iter()
            .inspect([](const auto &x) { INFO(x); })
            .filter([](const auto &x) { return x != "green"; })
            .any([](const auto &x) { return x == "blue"; })
          == true);
}