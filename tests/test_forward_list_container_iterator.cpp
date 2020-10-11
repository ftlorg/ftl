#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>
#include <vector>
#include <list>

#define TEST_TAG "[forward_list_container_iterator]"

TEST_CASE(TEST_TAG "collect to std::vector", TEST_TAG) {
  ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter().collect<std::vector<int>>();

  REQUIRE(mapped_list == std::vector<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect const to std::vector", TEST_TAG) {
  const ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter().collect<std::vector<int>>();

  REQUIRE(mapped_list == std::vector<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect to std::list", TEST_TAG) {
  ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter().collect<std::list<int>>();

  REQUIRE(mapped_list == std::list<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect const to std::list", TEST_TAG) {
  const ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter().collect<std::list<int>>();

  REQUIRE(mapped_list == std::list<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect const", TEST_TAG) {
  const ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };

  auto mapped_list = list.iter().collect<ftl::forward_list<int>>();

  const ftl::forward_list<int> list2 = { 1, 2, 3 };

  auto mapped_list2 = list2.iter().collect<ftl::forward_list<int>>();

  REQUIRE(mapped_list == ftl::forward_list<int>{ 1, 2, 3, 4, 5 });
  REQUIRE(mapped_list2 == ftl::forward_list<int>{ 1, 2, 3 });
}

TEST_CASE(TEST_TAG "map collect", TEST_TAG) {
  ftl::forward_list<std::string> forward_list = { { "red", "green", "blue" } };

  auto mapped_forward_list
    = forward_list.iter().map([](const auto &entry) { return entry + "abc"; }).collect<ftl::forward_list<std::string>>();

  REQUIRE(mapped_forward_list == ftl::forward_list<std::string>{ { "redabc", "greenabc", "blueabc" } });
}

TEST_CASE(TEST_TAG "map collect const", TEST_TAG) {
  const ftl::forward_list<std::string> forward_list = { { "red", "green", "blue" } };

  auto mapped_forward_list
    = forward_list.iter().map([](const auto &entry) { return entry + "abc"; }).collect<ftl::forward_list<std::string>>();

  REQUIRE(mapped_forward_list == ftl::forward_list<std::string>{ { "redabc", "greenabc", "blueabc" } });
}

TEST_CASE(TEST_TAG "map map collect", TEST_TAG) {
  ftl::forward_list<std::string> forward_list = { { "red", "green", "blue" } };

  auto mapped_forward_list = forward_list.iter()
                               .map([](const auto &entry) { return entry + "abc"; })
                               .map([](const auto &entry) { return entry + "abc"; })
                               .collect<std::vector<std::string>>();

  REQUIRE(mapped_forward_list == ftl::vector<std::string>{ { "redabcabc", "greenabcabc", "blueabcabc" } });
}

TEST_CASE(TEST_TAG "map map collect const", TEST_TAG) {
  const ftl::forward_list<std::string> forward_list = { { "red", "green", "blue" } };

  auto mapped_forward_list = forward_list.iter()
                               .map([](const auto &entry) { return entry + "abc"; })
                               .map([](const auto &entry) { return entry + "abc"; })
                               .collect<std::vector<std::string>>();

  REQUIRE(mapped_forward_list == ftl::vector<std::string>{ { "redabcabc", "greenabcabc", "blueabcabc" } });
}

TEST_CASE(TEST_TAG "enumerate collect", TEST_TAG) {
  ftl::forward_list<int> forward_list = { { 1, 2, 3 } };

  auto mapped_forward_list = forward_list.iter().enumerate().collect<std::vector<std::tuple<std::size_t, int>>>();

  REQUIRE(mapped_forward_list
          == std::vector<std::tuple<std::size_t, int>>{
            { 0, 1 },
            { 1, 2 },
            { 2, 3 },
          });
}

TEST_CASE(TEST_TAG "enumerate collect const", TEST_TAG) {
  const ftl::forward_list<int> forward_list = { { 1, 2, 3 } };

  auto mapped_forward_list = forward_list.iter().enumerate().collect<std::vector<std::tuple<std::size_t, int>>>();

  REQUIRE(mapped_forward_list
          == std::vector<std::tuple<std::size_t, int>>{
            { 0, 1 },
            { 1, 2 },
            { 2, 3 },
          });
}

TEST_CASE(TEST_TAG "map enumerate collect", TEST_TAG) {
  ftl::forward_list<std::string> forward_list = { { "red", "green", "blue" } };

  auto mapped_forward_list = forward_list.iter()
                               .map([](const auto &entry) { return entry + "abc"; })
                               .enumerate()
                               .collect<ftl::map<std::size_t, std::string>>();

  REQUIRE(mapped_forward_list
          == ftl::map<std::size_t, std::string>{
            { 0, "redabc" },
            { 1, "greenabc" },
            { 2, "blueabc" },
          });
}

TEST_CASE(TEST_TAG "map enumerate collect const", TEST_TAG) {
  const ftl::forward_list<std::string> forward_list = { { "red", "green", "blue" } };

  auto mapped_forward_list = forward_list.iter()
                               .map([](const auto &entry) { return entry + "abc"; })
                               .enumerate()
                               .collect<ftl::map<std::size_t, std::string>>();

  REQUIRE(mapped_forward_list
          == ftl::map<std::size_t, std::string>{
            { 0, "redabc" },
            { 1, "greenabc" },
            { 2, "blueabc" },
          });
}

TEST_CASE(TEST_TAG "map inspect map collect", TEST_TAG) {
  ftl::forward_list<std::string> forward_list = { { "red", "green", "blue" } };

  auto mapped_forward_list = forward_list.iter()
                               .map([](const auto &entry) { return std::string{ entry + "abc" }; })
                               .inspect([](const auto &entry) { INFO(entry); })
                               .map([](const auto &entry) { return std::string{ entry + "abc" }; })
                               .collect<ftl::forward_list<std::string>>();

  REQUIRE(mapped_forward_list == ftl::forward_list<std::string>{ { "redabcabc", "greenabcabc", "blueabcabc" } });
}

TEST_CASE(TEST_TAG "map inspect map collect const", TEST_TAG) {
  const ftl::forward_list<std::string> forward_list = { { "red", "green", "blue" } };

  auto mapped_forward_list = forward_list.iter()
                               .map([](const auto &entry) { return std::string{ entry + "abc" }; })
                               .inspect([](const auto &entry) { INFO(entry); })
                               .map([](const auto &entry) { return std::string{ entry + "abc" }; })
                               .collect<ftl::forward_list<std::string>>();

  REQUIRE(mapped_forward_list == ftl::forward_list<std::string>{ { "redabcabc", "greenabcabc", "blueabcabc" } });
}

TEST_CASE(TEST_TAG "count", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };

  REQUIRE(size == list.iter().count());
}

TEST_CASE(TEST_TAG "count const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };

  REQUIRE(size == list.iter().count());
}

TEST_CASE(TEST_TAG "begin", TEST_TAG) {
  ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };

  auto iter = list.iter().begin();
  REQUIRE(1 == *iter);

  ++iter;
  REQUIRE(2 == *iter);
}

TEST_CASE(TEST_TAG "begin const", TEST_TAG) {
  const ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };

  auto iter = list.iter().begin();
  REQUIRE(1 == *iter);

  ++iter;
  REQUIRE(2 == *iter);
}

TEST_CASE(TEST_TAG "cbegin", TEST_TAG) {
  ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };

  auto iter = list.iter().cbegin();
  REQUIRE(1 == *iter);

  ++iter;
  REQUIRE(2 == *iter);
}

TEST_CASE(TEST_TAG "cbegin const", TEST_TAG) {
  const ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };

  auto iter = list.iter().cbegin();
  REQUIRE(1 == *iter);

  ++iter;
  REQUIRE(2 == *iter);
}

TEST_CASE(TEST_TAG "operator++", TEST_TAG) {
  ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };

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
  const ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };

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

TEST_CASE(TEST_TAG "min", TEST_TAG) {
  const ftl::forward_list<int> list = { { 3, 1, 5, 0, -1, 4, 4, 7 } };

  const auto min = list.iter().min();
  REQUIRE(min.has_value() == true);
  REQUIRE(min.value() == -1);
}