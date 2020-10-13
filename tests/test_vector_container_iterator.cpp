#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>
#include <vector>
#include <list>

#define TEST_TAG "[vector_container_iterator]"

TEST_CASE(TEST_TAG "collect", TEST_TAG) {
  ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  auto mapped_vec = vec.iter().collect<std::vector<int>>();

  ftl::vector<int> vec2 = { 1, 2, 3 };

  auto mapped_vec2 = vec2.iter().collect<std::vector<int>>();

  REQUIRE(mapped_vec == std::vector<int>{ 1, 2, 3, 4, 5 });
  REQUIRE(mapped_vec2 == std::vector<int>{ 1, 2, 3 });
}

TEST_CASE(TEST_TAG "collect const", TEST_TAG) {
  const ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  const auto mapped_vec = vec.iter().collect<std::vector<int>>();

  const ftl::vector<int> vec2 = { 1, 2, 3 };

  const auto mapped_vec2 = vec2.iter().collect<std::vector<int>>();

  REQUIRE(mapped_vec == std::vector<int>{ 1, 2, 3, 4, 5 });
  REQUIRE(mapped_vec2 == std::vector<int>{ 1, 2, 3 });
}

TEST_CASE(TEST_TAG "collect to std::vector", TEST_TAG) {
  ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  auto mapped_vec = vec.iter().collect<ftl::vector<int>>();

  REQUIRE(mapped_vec == std::vector<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect const to std::vector", TEST_TAG) {
  const ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  auto mapped_vec = vec.iter().collect<ftl::vector<int>>();

  REQUIRE(mapped_vec == std::vector<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect to std::list", TEST_TAG) {
  ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  auto mapped_vec = vec.iter().collect<std::list<int>>();

  REQUIRE(mapped_vec == std::list<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect const to std::list", TEST_TAG) {
  const ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  auto mapped_vec = vec.iter().collect<std::list<int>>();

  REQUIRE(mapped_vec == std::list<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect const to ftl::vector", TEST_TAG) {
  const ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  auto mapped_vec = vec.iter().collect<ftl::vector<int>>();

  const ftl::vector<int> vec2 = { 1, 2, 3 };

  auto mapped_vec2 = vec2.iter().collect<ftl::vector<int>>();

  REQUIRE(mapped_vec == ftl::vector<int>{ 1, 2, 3, 4, 5 });
  REQUIRE(mapped_vec2 == ftl::vector<int>{ 1, 2, 3 });
}

TEST_CASE(TEST_TAG "count", TEST_TAG) {
  ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  REQUIRE(5 == vec.iter().count());
}

TEST_CASE(TEST_TAG "count const", TEST_TAG) {
  const ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  REQUIRE(5 == vec.iter().count());
}

TEST_CASE(TEST_TAG "begin", TEST_TAG) {
  ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  auto iter = vec.iter().begin();

  REQUIRE(vec[0] == *iter);

  ++iter;
  REQUIRE(vec[1] == *iter);
}

TEST_CASE(TEST_TAG "begin const", TEST_TAG) {
  const ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  auto iter = vec.iter().begin();
  REQUIRE(vec[0] == *iter);

  ++iter;
  REQUIRE(vec[1] == *iter);
}

TEST_CASE(TEST_TAG "cbegin", TEST_TAG) {
  ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  auto iter = vec.iter().cbegin();
  REQUIRE(vec[0] == *iter);

  ++iter;
  REQUIRE(vec[1] == *iter);
}

TEST_CASE(TEST_TAG "cbegin const", TEST_TAG) {
  const ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  auto iter = vec.iter().cbegin();
  REQUIRE(vec[0] == *iter);

  ++iter;
  REQUIRE(vec[1] == *iter);
}

TEST_CASE(TEST_TAG "operator++", TEST_TAG) {
  ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  auto iter = vec.iter();
  REQUIRE(vec[0] == *iter);

  ++iter;
  REQUIRE(vec[1] == *iter);

  ++iter;
  REQUIRE(vec[2] == *iter);

  ++iter;
  REQUIRE(vec[3] == *iter);

  ++iter;
  REQUIRE(vec[4] == *iter);
}

TEST_CASE(TEST_TAG "operator++ const", TEST_TAG) {
  const ftl::vector<int> vec = { 1, 2, 3, 4, 5 };

  auto iter = vec.iter();
  REQUIRE(vec[0] == *iter);

  ++iter;
  REQUIRE(vec[1] == *iter);

  ++iter;
  REQUIRE(vec[2] == *iter);

  ++iter;
  REQUIRE(vec[3] == *iter);

  ++iter;
  REQUIRE(vec[4] == *iter);
}

TEST_CASE(TEST_TAG "any", TEST_TAG) {
  ftl::vector<std::string> vec = { { "red", "green", "blue" } };

  REQUIRE(vec.iter().any([](const auto &x) { return x == "red"; }) == true);
  REQUIRE(vec.iter().any([](const auto &x) { return x == "purple"; }) == false);
}

TEST_CASE(TEST_TAG "operator--", TEST_TAG) {
  ftl::vector<int> vec = { { 1, 2, 3, 4, 5 } };

  auto iter = vec.iter() + 4;
  REQUIRE(vec[4] == *iter);
  REQUIRE(vec[3] == *(--iter));
  REQUIRE(vec[2] == *(--iter));
  REQUIRE(vec[1] == *(--iter));
  REQUIRE(vec[0] == *(--iter));
}

TEST_CASE(TEST_TAG "operator-- const", TEST_TAG) {
  const ftl::vector<int> vec = { { 1, 2, 3, 4, 5 } };

  auto iter = vec.iter() + 4;
  REQUIRE(vec[4] == *iter);
  REQUIRE(vec[3] == *(--iter));
  REQUIRE(vec[2] == *(--iter));
  REQUIRE(vec[1] == *(--iter));
  REQUIRE(vec[0] == *(--iter));
}

TEST_CASE(TEST_TAG "min", TEST_TAG) {
  const ftl::vector<int> vec = { { 3, 1, 5, 0, -1, 4, 4, 7 } };

  const auto min = vec.iter().min();
  REQUIRE(min.has_value() == true);
  REQUIRE(min.value() == -1);
}

TEST_CASE(TEST_TAG "min empty", TEST_TAG) {
  const ftl::vector<int> vec = {};

  const auto min = vec.iter().min();
  REQUIRE_FALSE(min.has_value());
}

TEST_CASE(TEST_TAG "max", TEST_TAG) {
  const ftl::vector<int> list = { { 3, 1, 12, 0, -1, 4, 4, 7 } };

  REQUIRE(list.iter().max().value() == 12);
}

TEST_CASE(TEST_TAG "max empty range", TEST_TAG) {
  const ftl::vector<int> list = {};

  REQUIRE(list.iter().max().has_value() == false);
}

TEST_CASE(TEST_TAG "max equal range lower than zero", TEST_TAG) {
  const ftl::vector<int> list = { { -2, -2, -2 } };

  REQUIRE(list.iter().max().value() == -2);
}

TEST_CASE(TEST_TAG "max equal range greater than zero", TEST_TAG) {
  const ftl::vector<int> list = { { 2, 2, 2 } };

  REQUIRE(list.iter().max().value() == 2);
}

TEST_CASE(TEST_TAG "max at the beginning", TEST_TAG) {
  const ftl::vector<int> list = { { 4, 3, -1 } };

  REQUIRE(list.iter().max().value() == 4);
}

TEST_CASE(TEST_TAG "max at the end", TEST_TAG) {
  const ftl::vector<int> list = { { -1, 3, 7 } };

  REQUIRE(list.iter().max().value() == 7);
}

TEST_CASE(TEST_TAG "all elements satisfy predicate", TEST_TAG) {
  const ftl::vector<int> arr = { 2, 4 };

  auto element = arr.iter().all([](const auto &elem) { return elem % 2 == 0; });

  REQUIRE(element);
}

TEST_CASE(TEST_TAG "not all elements satisfy predicate", TEST_TAG) {
  const ftl::vector<int> arr = { 2, 4, 5 };

  auto element = arr.iter().all([](const auto &elem) { return elem % 2 == 0; });

  REQUIRE_FALSE(element);
}