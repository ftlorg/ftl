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

  const auto size = list.iter().inspect([](const auto &x) { INFO("Inspecting x = " << x) }).count();

  REQUIRE(size == 5);
}

TEST_CASE(TEST_TAG "inspect count const", TEST_TAG) {
  const ftl::list<int> list = { 1, 2, 3, 4, 5 };

  const auto size = list.iter().inspect([](const auto &x) { INFO("Inspecting x = " << x) }).count();

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
TEST_CASE(TEST_TAG "inspect min", TEST_TAG) {
  ftl::list<int> list = { { 3, 1, 5, 0, -1, 4, 4, 7 } };

  const auto min = list.iter().inspect([](const auto &x) { INFO(x); }).min();
  REQUIRE(min.has_value() == true);
  REQUIRE(min.value() == -1);
}

TEST_CASE(TEST_TAG "inspect max", TEST_TAG) {
  const ftl::forward_list<int> list = { { 3, 1, 12, 0, -1, 4, 4, 7 } };

  REQUIRE(list.iter().inspect([](const auto &x) { INFO(x); }).max().value() == 12);
}

TEST_CASE(TEST_TAG "inspect max empty range", TEST_TAG) {
  const ftl::forward_list<int> list = {};

  REQUIRE_FALSE(list.iter().inspect([](const auto &x) { INFO(x); }).max().has_value());
}

TEST_CASE(TEST_TAG "inspect max equal range lower than zero", TEST_TAG) {
  const ftl::forward_list<int> list = { { -2, -2, -2 } };

  REQUIRE(list.iter().inspect([](const auto &x) { INFO(x); }).max().value() == -2);
}

TEST_CASE(TEST_TAG "inspect max equal range greater than zero", TEST_TAG) {
  const ftl::forward_list<int> list = { { 2, 2, 2 } };

  REQUIRE(list.iter().inspect([](const auto &x) { INFO(x); }).max().value() == 2);
}

TEST_CASE(TEST_TAG "inspect max at the beginning", TEST_TAG) {
  const ftl::forward_list<int> list = { { 4, 3, -1 } };

  REQUIRE(list.iter().inspect([](const auto &x) { INFO(x); }).max().value() == 4);
}

TEST_CASE(TEST_TAG "inspect max at the end", TEST_TAG) {
  const ftl::forward_list<int> list = { { -1, 3, 7 } };

  REQUIRE(list.iter().inspect([](const auto &x) { INFO(x); }).max().value() == 7);
}
