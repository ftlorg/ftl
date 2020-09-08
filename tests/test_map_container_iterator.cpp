#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>
#include <vector>
#include <list>
#include <utility>

#define TEST_TAG "[map_container_iterator]"

TEST_CASE(TEST_TAG "next", TEST_TAG) {
  ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto iter = map.iter();
  std::pair<const int, std::string> p{ 2, "green" };
  REQUIRE(p == *iter.next());
}

TEST_CASE(TEST_TAG "next const", TEST_TAG) {
  const ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto iter = map.iter();
  std::pair<const int, std::string> p{ 2, "green" };
  REQUIRE(p == *iter.next());
}

TEST_CASE(TEST_TAG "next nullopt", TEST_TAG) {
  ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" } };

  auto iter = map.iter();
  std::pair<const int, std::string> p{ 2, "green" };

  REQUIRE(p == *iter.next());
  REQUIRE(iter.next().has_value() == false);
}

TEST_CASE(TEST_TAG "next const nullopt", TEST_TAG) {
  const ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" } };

  auto iter = map.iter();
  std::pair<const int, std::string> p{ 2, "green" };

  REQUIRE(p == *iter.next());
  REQUIRE(iter.next().has_value() == false);
}

TEST_CASE(TEST_TAG "collect to std::vector", TEST_TAG) {
  ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter().collect<std::vector<std::pair<const int, std::string>>>();

  REQUIRE(mapped_map == std::vector<std::pair<const int, std::string>>{ { 1, "red" }, { 2, "green" }, { 3, "blue" } });
}

TEST_CASE(TEST_TAG "collect const to std::vector", TEST_TAG) {
  const ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter().collect<std::vector<std::pair<const int, std::string>>>();

  REQUIRE(mapped_map == std::vector<std::pair<const int, std::string>>{ { 1, "red" }, { 2, "green" }, { 3, "blue" } });
}

TEST_CASE(TEST_TAG "collect to std::map", TEST_TAG) {
  ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter().collect<std::map<int, std::string>>();

  REQUIRE(mapped_map == std::map<int, std::string>{ { 1, "red" }, { 2, "green" }, { 3, "blue" } });
}

TEST_CASE(TEST_TAG "collect const to std::map", TEST_TAG) {
  const ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter().collect<std::map<int, std::string>>();

  REQUIRE(mapped_map == std::map<int, std::string>{ { 1, "red" }, { 2, "green" }, { 3, "blue" } });
}

TEST_CASE(TEST_TAG "collect const", TEST_TAG) {
  const ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter().collect<ftl::map<int, std::string>>();

  REQUIRE(mapped_map == ftl::map<int, std::string>{ { 1, "red" }, { 2, "green" }, { 3, "blue" } });
}

TEST_CASE(TEST_TAG "count", TEST_TAG) {
  constexpr std::size_t size = 3;
  ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  REQUIRE(size == map.iter().count());
}

TEST_CASE(TEST_TAG "count const", TEST_TAG) {
  constexpr std::size_t size = 3;
  const ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  REQUIRE(size == map.iter().count());
}

TEST_CASE(TEST_TAG "begin", TEST_TAG) {
  ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto iter = map.iter().begin();
  REQUIRE(std::pair<const int, std::string>{ 1, "red" } == *iter);

  ++iter;
  REQUIRE(std::pair<const int, std::string>{ 2, "green" } == *iter);
}

TEST_CASE(TEST_TAG "begin const", TEST_TAG) {
  const ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto iter = map.iter().begin();
  REQUIRE(std::pair<const int, std::string>{ 1, "red" } == *iter);

  ++iter;
  REQUIRE(std::pair<const int, std::string>{ 2, "green" } == *iter);
}

TEST_CASE(TEST_TAG "cbegin", TEST_TAG) {
  ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto iter = map.iter().cbegin();
  REQUIRE(std::pair<const int, std::string>{ 1, "red" } == *iter);

  ++iter;
  REQUIRE(std::pair<const int, std::string>{ 2, "green" } == *iter);
}

TEST_CASE(TEST_TAG "cbegin const", TEST_TAG) {
  const ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto iter = map.iter().cbegin();
  REQUIRE(std::pair<const int, std::string>{ 1, "red" } == *iter);

  ++iter;
  REQUIRE(std::pair<const int, std::string>{ 2, "green" } == *iter);
}

TEST_CASE(TEST_TAG "operator++", TEST_TAG) {
  ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto iter = map.iter();
  REQUIRE(std::pair<const int, std::string>{ 1, "red" } == *iter);

  ++iter;
  REQUIRE(std::pair<const int, std::string>{ 2, "green" } == *iter);

  ++iter;
  REQUIRE(std::pair<const int, std::string>{ 3, "blue" } == *iter);
}

TEST_CASE(TEST_TAG "operator++ const", TEST_TAG) {
  const ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto iter = map.iter();
  REQUIRE(std::pair<const int, std::string>{ 1, "red" } == *iter);

  ++iter;
  REQUIRE(std::pair<const int, std::string>{ 2, "green" } == *iter);

  ++iter;
  REQUIRE(std::pair<const int, std::string>{ 3, "blue" } == *iter);
}
