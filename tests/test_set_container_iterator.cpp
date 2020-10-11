#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>
#include <vector>
#include <list>
#include <utility>

#define TEST_TAG "[set_container_iterator]"

TEST_CASE(TEST_TAG "collect to std::vector", TEST_TAG) {
  ftl::set<std::string> set = { { "red", "green", "blue" } };

  auto mapped_set = set.iter().collect<std::vector<std::string>>();

  REQUIRE(mapped_set == std::vector<std::string>{ "blue", "green", "red" });
}

TEST_CASE(TEST_TAG "collect to std::vector const", TEST_TAG) {
  const ftl::set<int> set = { { 1, 2, 3 } };

  auto mapped_set = set.iter().collect<std::vector<int>>();

  REQUIRE(mapped_set == std::vector<int>{ { 1, 2, 3 } });
}

TEST_CASE(TEST_TAG "collect to std::set", TEST_TAG) {
  ftl::set<int> set = { { 1, 2, 3 } };

  auto mapped_set = set.iter().collect<std::set<int>>();

  REQUIRE(mapped_set == std::set<int>{ { 1, 2, 3 } });
}

TEST_CASE(TEST_TAG "collect const to std::set", TEST_TAG) {
  const ftl::set<int> set = { { 1, 2, 3 } };

  auto mapped_set = set.iter().collect<std::set<int>>();

  REQUIRE(mapped_set == std::set<int>{ { 1, 2, 3 } });
}

TEST_CASE(TEST_TAG "map collect", TEST_TAG) {
  ftl::set<std::string> set = { { "red", "green", "blue" } };

  auto mapped_set = set.iter().map([](const auto &entry) { return entry + "abc"; }).collect<ftl::set<std::string>>();

  REQUIRE(mapped_set == ftl::set<std::string>{ { "redabc", "greenabc", "blueabc" } });
}

TEST_CASE(TEST_TAG "map collect const", TEST_TAG) {
  const ftl::set<std::string> set = { { "red", "green", "blue" } };

  auto mapped_set = set.iter().map([](const auto &entry) { return entry + "abc"; }).collect<ftl::set<std::string>>();

  REQUIRE(mapped_set == ftl::set<std::string>{ { "redabc", "greenabc", "blueabc" } });
}

TEST_CASE(TEST_TAG "map map collect", TEST_TAG) {
  ftl::set<std::string> set = { { "red", "green", "blue" } };

  auto mapped_set = set.iter()
                      .map([](const auto &entry) { return entry + "abc"; })
                      .map([](const auto &entry) { return entry + "abc"; })
                      .collect<std::vector<std::string>>();

  REQUIRE(mapped_set == ftl::vector<std::string>{ { "blueabcabc", "greenabcabc", "redabcabc" } });
}

TEST_CASE(TEST_TAG "map map collect const", TEST_TAG) {
  const ftl::set<std::string> set = { { "red", "green", "blue" } };

  auto mapped_set = set.iter()
                      .map([](const auto &entry) { return entry + "abc"; })
                      .map([](const auto &entry) { return entry + "abc"; })
                      .collect<std::vector<std::string>>();

  REQUIRE(mapped_set == ftl::vector<std::string>{ { "blueabcabc", "greenabcabc", "redabcabc" } });
}

TEST_CASE(TEST_TAG "enumerate collect", TEST_TAG) {
  ftl::set<std::string> set = { { "red", "green", "blue" } };

  for (const auto &e : set.iter().enumerate()) { INFO(std::get<0>(e)); }

  auto mapped_set = set.iter().enumerate().collect<ftl::map<std::size_t, std::string>>();

  REQUIRE(mapped_set
          == ftl::map<std::size_t, std::string>{
            { 0, "blue" },
            { 1, "green" },
            { 2, "red" },
          });
}

TEST_CASE(TEST_TAG "enumerate collect const", TEST_TAG) {
  const ftl::set<std::string> set = { { "red", "green", "blue" } };

  for (const auto &e : set.iter().enumerate()) { INFO(std::get<0>(e)); }

  auto mapped_set = set.iter().enumerate().collect<ftl::map<std::size_t, std::string>>();

  REQUIRE(mapped_set
          == ftl::map<std::size_t, std::string>{
            { 0, "blue" },
            { 1, "green" },
            { 2, "red" },
          });
}

TEST_CASE(TEST_TAG "map enumerate collect", TEST_TAG) {
  ftl::set<std::string> set = { { "red", "green", "blue" } };

  for (const auto &e : set.iter().enumerate()) { INFO(std::get<0>(e)); }

  auto mapped_set = set.iter()
                      .map([](const auto &entry) { return entry + "abc"; })
                      .enumerate()
                      .collect<ftl::map<std::size_t, std::string>>();

  REQUIRE(mapped_set
          == ftl::map<std::size_t, std::string>{
            { 0, "blueabc" },
            { 1, "greenabc" },
            { 2, "redabc" },
          });
}

TEST_CASE(TEST_TAG "map enumerate collect const", TEST_TAG) {
  const ftl::set<std::string> set = { { "red", "green", "blue" } };

  for (const auto &e : set.iter().enumerate()) { INFO(std::get<0>(e)); }

  auto mapped_set = set.iter()
                      .map([](const auto &entry) { return entry + "abc"; })
                      .enumerate()
                      .collect<ftl::map<std::size_t, std::string>>();

  REQUIRE(mapped_set
          == ftl::map<std::size_t, std::string>{
            { 0, "blueabc" },
            { 1, "greenabc" },
            { 2, "redabc" },
          });
}

TEST_CASE(TEST_TAG "map inspect map collect", TEST_TAG) {
  ftl::set<std::string> set = { { "red", "green", "blue" } };

  auto mapped_set = set.iter()
                      .map([](const auto &entry) { return std::string{ entry + "abc" }; })
                      .inspect([](const auto &entry) { INFO(entry); })
                      .map([](const auto &entry) { return std::string{ entry + "abc" }; })
                      .collect<ftl::set<std::string>>();

  REQUIRE(mapped_set == ftl::set<std::string>{ { "blueabcabc", "greenabcabc", "redabcabc" } });
}

TEST_CASE(TEST_TAG "map inspect map collect const", TEST_TAG) {
  const ftl::set<std::string> set = { { "red", "green", "blue" } };

  auto mapped_set = set.iter()
                      .map([](const auto &entry) { return std::string{ entry + "abc" }; })
                      .inspect([](const auto &entry) { INFO(entry); })
                      .map([](const auto &entry) { return std::string{ entry + "abc" }; })
                      .collect<ftl::set<std::string>>();

  REQUIRE(mapped_set == ftl::set<std::string>{ { "blueabcabc", "greenabcabc", "redabcabc" } });
}

TEST_CASE(TEST_TAG "count", TEST_TAG) {
  constexpr std::size_t size = 3;
  ftl::set<std::string> set = { { "red", "green", "blue" } };

  REQUIRE(size == set.iter().count());
}

TEST_CASE(TEST_TAG "count const", TEST_TAG) {
  constexpr std::size_t size = 3;
  const ftl::set<std::string> set = { { "red", "green", "blue" } };

  REQUIRE(size == set.iter().count());
}

TEST_CASE(TEST_TAG "begin", TEST_TAG) {
  ftl::set<std::string> set = { { "red", "green", "blue" } };

  auto iter = set.iter().begin();
  REQUIRE(std::string("blue") == *iter);

  ++iter;
  REQUIRE(std::string("green") == *iter);
}

TEST_CASE(TEST_TAG "begin const", TEST_TAG) {
  const ftl::set<std::string> set = { { "red", "green", "blue" } };

  auto iter = set.iter().begin();
  REQUIRE(std::string{ "blue" } == *iter);

  ++iter;
  REQUIRE(std::string{ "green" } == *iter);
}

TEST_CASE(TEST_TAG "cbegin", TEST_TAG) {
  ftl::set<std::string> set = { { "red", "green", "blue" } };

  auto iter = set.iter().cbegin();
  REQUIRE(std::string{ "blue" } == *iter);

  ++iter;
  REQUIRE(std::string{ "green" } == *iter);
}

TEST_CASE(TEST_TAG "cbegin const", TEST_TAG) {
  const ftl::set<std::string> set = { { "red", "green", "blue" } };

  auto iter = set.iter().cbegin();
  REQUIRE(std::string{ "blue" } == *iter);

  ++iter;
  REQUIRE(std::string{ "green" } == *iter);
}

TEST_CASE(TEST_TAG "operator++", TEST_TAG) {
  ftl::set<std::string> set = { { "red", "green", "blue" } };

  auto iter = set.iter();
  REQUIRE(std::string{ "blue" } == *iter);

  ++iter;
  REQUIRE(std::string{ "green" } == *iter);

  ++iter;
  REQUIRE(std::string{ "red" } == *iter);
}

TEST_CASE(TEST_TAG "operator++ const", TEST_TAG) {
  const ftl::set<std::string> set = { { "red", "green", "blue" } };

  auto iter = set.iter();
  REQUIRE(std::string{ "blue" } == *iter);

  ++iter;
  REQUIRE(std::string{ "green" } == *iter);

  ++iter;
  REQUIRE(std::string{ "red" } == *iter);
}

TEST_CASE(TEST_TAG "product", TEST_TAG) {
  const ftl::set<float> set = { { 1.5f, 2.5f, 3.5f } };

  auto product = set.iter().product();

  REQUIRE(product == 13.125f);
}