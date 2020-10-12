#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>
#include <vector>
#include <list>

#define TEST_TAG "[list_container_iterator]"

TEST_CASE(TEST_TAG "collect to std::vector", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter().collect<std::vector<int>>();

  REQUIRE(mapped_list == std::vector<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect const to std::vector", TEST_TAG) {
  const ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter().collect<std::vector<int>>();

  REQUIRE(mapped_list == std::vector<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect to std::list", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter().collect<std::list<int>>();

  REQUIRE(mapped_list == std::list<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect const to std::list", TEST_TAG) {
  const ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter().collect<std::list<int>>();

  REQUIRE(mapped_list == std::list<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect const", TEST_TAG) {
  const ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter().collect<ftl::list<int>>();

  const ftl::list<int> list2 = { 1, 2, 3 };

  auto mapped_list2 = list2.iter().collect<ftl::list<int>>();

  REQUIRE(mapped_list == ftl::list<int>{ 1, 2, 3, 4, 5 });
  REQUIRE(mapped_list2 == ftl::list<int>{ 1, 2, 3 });
}

TEST_CASE(TEST_TAG "count", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  REQUIRE(size == list.iter().count());
}

TEST_CASE(TEST_TAG "count const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::list<int> list = { 1, 2, 3, 4, 5 };

  REQUIRE(size == list.iter().count());
}

TEST_CASE(TEST_TAG "begin", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto iter = list.iter().begin();
  REQUIRE(1 == *iter);

  ++iter;
  REQUIRE(2 == *iter);
}

TEST_CASE(TEST_TAG "begin const", TEST_TAG) {
  const ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto iter = list.iter().begin();
  REQUIRE(1 == *iter);

  ++iter;
  REQUIRE(2 == *iter);
}

TEST_CASE(TEST_TAG "cbegin", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto iter = list.iter().cbegin();
  REQUIRE(1 == *iter);

  ++iter;
  REQUIRE(2 == *iter);
}

TEST_CASE(TEST_TAG "cbegin const", TEST_TAG) {
  const ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto iter = list.iter().cbegin();
  REQUIRE(1 == *iter);

  ++iter;
  REQUIRE(2 == *iter);
}

TEST_CASE(TEST_TAG "operator++", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto iter = list.iter();
  REQUIRE(1 == *iter);

  ++iter;
  REQUIRE(2 == *iter);

  ++iter;
  REQUIRE(3 == *iter);

  ++iter;
  REQUIRE(4 == *iter);

  ++iter;
  REQUIRE(5 == *iter);
}

TEST_CASE(TEST_TAG "operator++ const", TEST_TAG) {
  const ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto iter = list.iter();
  REQUIRE(1 == *iter);

  ++iter;
  REQUIRE(2 == *iter);

  ++iter;
  REQUIRE(3 == *iter);

  ++iter;
  REQUIRE(4 == *iter);

  ++iter;
  REQUIRE(5 == *iter);
}

TEST_CASE(TEST_TAG "any", TEST_TAG) {
  ftl::list<std::string> list = { { "red", "green", "blue" } };

  REQUIRE(list.iter().any([](const auto &x) { return x == "red"; }) == true);
  REQUIRE(list.iter().any([](const auto &x) { return x == "purple"; }) == false);
}

TEST_CASE(TEST_TAG "operator--", TEST_TAG) {
  ftl::list<int> list = { { 1, 2, 3, 4, 5 } };

  auto iter = --list.iter().end();
  REQUIRE(5 == *iter);
  REQUIRE(4 == *(--iter));
  REQUIRE(3 == *(--iter));
  REQUIRE(2 == *(--iter));
  REQUIRE(1 == *(--iter));
}

TEST_CASE(TEST_TAG "operator-- const", TEST_TAG) {
  const ftl::list<int> list = { { 1, 2, 3, 4, 5 } };

  auto iter = --list.iter().end();
  REQUIRE(5 == *iter);
  REQUIRE(4 == *(--iter));
  REQUIRE(3 == *(--iter));
  REQUIRE(2 == *(--iter));
  REQUIRE(1 == *(--iter));
}

TEST_CASE(TEST_TAG "min", TEST_TAG) {
  const ftl::list<int> list = { { 3, 1, 5, 0, -1, 4, 4, 7 } };

  const auto min = list.iter().min();
  REQUIRE(min.has_value() == true);
  REQUIRE(min.value() == -1);
}

TEST_CASE(TEST_TAG "min empty", TEST_TAG) {
  const ftl::list<int> list = {};

  const auto min = list.iter().min();
  REQUIRE_FALSE(min.has_value());
}

TEST_CASE(TEST_TAG "all elements satisfy predicate", TEST_TAG) {
  const ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto element = list.iter().all([](const auto &number) { return number < 10; });

  REQUIRE(element);
}

TEST_CASE(TEST_TAG "not all elements satisfy predicate", TEST_TAG) {
  const ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto element = list.iter().all([](const auto &number) { return number == 3; });

  REQUIRE_FALSE(element);
}

TEST_CASE(TEST_TAG "all elements satisfy predicate", TEST_TAG) {
  const ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto element = list.iter().all([](const auto &number) { return number < 10; });

  REQUIRE(element);
}

TEST_CASE(TEST_TAG "not all elements satisfy predicate", TEST_TAG) {
  const ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto element = list.iter().all([](const auto &number) { return number == 3; });

  REQUIRE_FALSE(element);
}