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

TEST_CASE(TEST_TAG "map take collect", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter().map([](const auto &x) { return x * x; }).take(3).collect<ftl::list<int>>();
  auto mapped_vec = list.iter().map([](const auto &x) { return x * x; }).take(3).collect<ftl::vector<int>>();

  REQUIRE(mapped_list == ftl::list<int>{ 1, 4, 9 });
  REQUIRE(mapped_vec == ftl::vector<int>{ 1, 4, 9 });
}

TEST_CASE(TEST_TAG "take map collect", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter().take(3).map([](const auto &x) { return x * x; }).collect<ftl::list<int>>();
  auto mapped_vec = list.iter().take(3).map([](const auto &x) { return x * x; }).collect<ftl::vector<int>>();

  REQUIRE(mapped_list == ftl::list<int>{ 1, 4, 9 });
  REQUIRE(mapped_vec == ftl::vector<int>{ 1, 4, 9 });
}

TEST_CASE(TEST_TAG "take take collect", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter().take(3).take(2).collect<ftl::list<int>>();
  auto mapped_vec = list.iter().take(3).take(2).collect<ftl::vector<int>>();

  REQUIRE(mapped_list == ftl::list<int>{ 1, 2 });
  REQUIRE(mapped_vec == ftl::vector<int>{ 1, 2 });
}

TEST_CASE(TEST_TAG "take map take collect", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter().take(3).map([](const auto &x) { return x * x; }).take(2).collect<ftl::list<int>>();
  auto mapped_vec = list.iter().take(3).map([](const auto &x) { return x * x; }).take(2).collect<ftl::vector<int>>();

  REQUIRE(mapped_list == ftl::list<int>{ 1, 4 });
  REQUIRE(mapped_vec == ftl::vector<int>{ 1, 4 });
}

TEST_CASE(TEST_TAG "take filter take collect", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter().take(4).filter([](const auto &x) { return x % 2 == 0; }).take(2).collect<ftl::list<int>>();
  auto mapped_vec = list.iter().take(4).filter([](const auto &x) { return x % 2 == 0; }).take(2).collect<ftl::vector<int>>();

  REQUIRE(mapped_list == ftl::list<int>{ 2, 4 });
  REQUIRE(mapped_vec == ftl::vector<int>{ 2, 4 });
}

TEST_CASE(TEST_TAG "take filter take less collect", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter().take(4).filter([](const auto &x) { return x % 2 == 0; }).take(1).collect<ftl::list<int>>();
  auto mapped_vec = list.iter().take(4).filter([](const auto &x) { return x % 2 == 0; }).take(1).collect<ftl::vector<int>>();

  REQUIRE(mapped_list == ftl::list<int>{ 2 });
  REQUIRE(mapped_vec == ftl::vector<int>{ 2 });
}

TEST_CASE(TEST_TAG "take filter take more collect", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter().take(4).filter([](const auto &x) { return x % 2 == 0; }).take(10).collect<ftl::list<int>>();
  auto mapped_vec
    = list.iter().take(4).filter([](const auto &x) { return x % 2 == 0; }).take(10).collect<ftl::vector<int>>();

  REQUIRE(mapped_list == ftl::list<int>{ 2, 4 });
  REQUIRE(mapped_vec == ftl::vector<int>{ 2, 4 });
}

 TEST_CASE(TEST_TAG "all elements satisfy predicate", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto element = list.iter().take(4).all([](const auto &x) { return x < 5; });

  REQUIRE(element);
}

TEST_CASE(TEST_TAG "not all elements satisfy predicate", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto element = list.iter().take(5).all([](const auto &x) { return x < 5; });

  REQUIRE_FALSE(element);
}

TEST_CASE(TEST_TAG "any", TEST_TAG) {
  const ftl::list<std::string> list = { { "red", "green", "blue" } };

  REQUIRE(list.iter().take(2).any([](const auto &x) { return x == "red"; }) == true);
  REQUIRE(list.iter().take(2).any([](const auto &x) { return x == "purple"; }) == false);
}

TEST_CASE(TEST_TAG "take min", TEST_TAG) {
  ftl::list<int> list = { { 3, 1, 5, 0, -1, 4, 4, 7 } };

  const auto min1 = list.iter().take(3).min();
  REQUIRE(min1.has_value() == true);
  REQUIRE(min1.value() == 1);

  const auto min2 = list.iter().take(0).min();
  REQUIRE_FALSE(min2.has_value());
}

TEST_CASE(TEST_TAG "take max", TEST_TAG) {
  const ftl::forward_list<int> list = { { 3, 1, 12, 0, -1, 4, 4, 7 } };

  REQUIRE(list.iter().take(5).max().value() == 12);
}

TEST_CASE(TEST_TAG "take max empty range", TEST_TAG) {
  const ftl::forward_list<int> list1 = {};
  const ftl::forward_list<int> list2 = {1, 2, 3};

  REQUIRE(list1.iter().take(0).max().has_value() == false);
  REQUIRE(list2.iter().take(0).max().has_value() == false);
}

TEST_CASE(TEST_TAG "take max equal range lower than zero", TEST_TAG) {
  const ftl::forward_list<int> list = { { -2, -2, -2 } };

  REQUIRE(list.iter().take(5).max().value() == -2);
}

TEST_CASE(TEST_TAG "take max equal range greater than zero", TEST_TAG) {
  const ftl::forward_list<int> list = { { 2, 2, 2 } };

  REQUIRE(list.iter().take(5).max().value() == 2);
}

TEST_CASE(TEST_TAG "take max at the beginning", TEST_TAG) {
  const ftl::forward_list<int> list = { { 4, 3, -1 } };

  REQUIRE(list.iter().take(5).max().value() == 4);
}

TEST_CASE(TEST_TAG "take max at the end", TEST_TAG) {
  const ftl::forward_list<int> list = { { -1, 3, 7 } };

  REQUIRE(list.iter().take(5).max().value() == 7);
}
