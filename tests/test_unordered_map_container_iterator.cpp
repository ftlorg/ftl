#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>
#include <vector>
#include <list>
#include <utility>

#define TEST_TAG "[unordered_map_container_iterator]"

TEST_CASE(TEST_TAG "collect to std::vector", TEST_TAG) {
  ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter().collect<std::vector<std::pair<const int, std::string>>>();

  auto it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 1, "red" });
  REQUIRE(it != mapped_map.end());
  it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 2, "green" });
  REQUIRE(it != mapped_map.end());
  it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 3, "blue" });
  REQUIRE(it != mapped_map.end());
}

TEST_CASE(TEST_TAG "collect const to std::vector", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter().collect<std::vector<std::pair<const int, std::string>>>();

  auto it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 1, "red" });
  REQUIRE(it != mapped_map.end());
  it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 2, "green" });
  REQUIRE(it != mapped_map.end());
  it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 3, "blue" });
  REQUIRE(it != mapped_map.end());
}

TEST_CASE(TEST_TAG "collect to std::map", TEST_TAG) {
  ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter().collect<std::map<int, std::string>>();

  auto it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 1, "red" });
  REQUIRE(it != mapped_map.end());
  it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 2, "green" });
  REQUIRE(it != mapped_map.end());
  it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 3, "blue" });
  REQUIRE(it != mapped_map.end());
}

TEST_CASE(TEST_TAG "collect const to std::map", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter().collect<std::map<int, std::string>>();

  auto it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 1, "red" });
  REQUIRE(it != mapped_map.end());
  it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 2, "green" });
  REQUIRE(it != mapped_map.end());
  it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 3, "blue" });
  REQUIRE(it != mapped_map.end());
}

TEST_CASE(TEST_TAG "collect const", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter().collect<ftl::unordered_map<int, std::string>>();

  auto it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 1, "red" });
  REQUIRE(it != mapped_map.end());
  it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 2, "green" });
  REQUIRE(it != mapped_map.end());
  it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 3, "blue" });
  REQUIRE(it != mapped_map.end());
}

TEST_CASE(TEST_TAG "map collect", TEST_TAG) {
  ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter()
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .collect<ftl::unordered_map<int, std::string>>();

  auto it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 1, "redabc" });
  REQUIRE(it != mapped_map.end());
  it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 2, "greenabc" });
  REQUIRE(it != mapped_map.end());
  it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 3, "blueabc" });
  REQUIRE(it != mapped_map.end());
}

TEST_CASE(TEST_TAG "map collect const", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter()
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .collect<ftl::unordered_map<int, std::string>>();

  auto it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 1, "redabc" });
  REQUIRE(it != mapped_map.end());
  it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 2, "greenabc" });
  REQUIRE(it != mapped_map.end());
  it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 3, "blueabc" });
  REQUIRE(it != mapped_map.end());
}

TEST_CASE(TEST_TAG "map map collect", TEST_TAG) {
  ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter()
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .collect<ftl::unordered_map<int, std::string>>();

  auto it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 1, "redabcabc" });
  REQUIRE(it != mapped_map.end());
  it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 2, "greenabcabc" });
  REQUIRE(it != mapped_map.end());
  it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 3, "blueabcabc" });
  REQUIRE(it != mapped_map.end());
}

TEST_CASE(TEST_TAG "map map collect const", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter()
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .collect<ftl::unordered_map<int, std::string>>();

  auto it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 1, "redabcabc" });
  REQUIRE(it != mapped_map.end());
  it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 2, "greenabcabc" });
  REQUIRE(it != mapped_map.end());
  it = std::find(std::begin(mapped_map), std::end(mapped_map), std::pair<const int, std::string>{ 3, "blueabcabc" });
  REQUIRE(it != mapped_map.end());
}

TEST_CASE(TEST_TAG "enumerate collect", TEST_TAG) {
  ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter().enumerate().collect<ftl::unordered_map<std::size_t, std::pair<const int, std::string>>>();

  auto it = mapped_map.find(0);
  REQUIRE(it != mapped_map.end());
  it = mapped_map.find(1);
  REQUIRE(it != mapped_map.end());
  it = mapped_map.find(2);
  REQUIRE(it != mapped_map.end());
}

TEST_CASE(TEST_TAG "enumerate collect const", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter().enumerate().collect<ftl::unordered_map<std::size_t, std::tuple<const int, std::string>>>();

  auto it = mapped_map.find(0);
  REQUIRE(it != mapped_map.end());
  it = mapped_map.find(1);
  REQUIRE(it != mapped_map.end());
  it = mapped_map.find(2);
  REQUIRE(it != mapped_map.end());
}

TEST_CASE(TEST_TAG "map enumerate collect", TEST_TAG) {
  ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  for (const auto &e : map.iter().enumerate()) { INFO(std::get<0>(e)); }

  auto mapped_map = map.iter()
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .enumerate()
                      .collect<ftl::unordered_map<std::size_t, std::pair<const int, std::string>>>();

  auto it = mapped_map.find(0);
  REQUIRE(it != mapped_map.end());
  it = mapped_map.find(1);
  REQUIRE(it != mapped_map.end());
  it = mapped_map.find(2);
  REQUIRE(it != mapped_map.end());
}

TEST_CASE(TEST_TAG "map enumerate collect const", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  for (const auto &e : map.iter().enumerate()) { INFO(std::get<0>(e)); }

  auto mapped_map = map.iter()
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .enumerate()
                      .collect<ftl::unordered_map<std::size_t, std::tuple<const int, std::string>>>();

  auto it = mapped_map.find(0);
  REQUIRE(it != mapped_map.end());
  it = mapped_map.find(1);
  REQUIRE(it != mapped_map.end());
  it = mapped_map.find(2);
  REQUIRE(it != mapped_map.end());
}

TEST_CASE(TEST_TAG "map inspect map collect", TEST_TAG) {
  ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter()
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .inspect([](const auto &entry) { INFO(entry.second); })
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .collect<ftl::unordered_map<int, std::string>>();

  auto it = mapped_map.find(1);
  REQUIRE(it != mapped_map.end());
  it = mapped_map.find(2);
  REQUIRE(it != mapped_map.end());
  it = mapped_map.find(3);
  REQUIRE(it != mapped_map.end());
}

TEST_CASE(TEST_TAG "map inspect map collect const", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter()
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .inspect([](const auto &entry) { INFO(entry.second); })
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .collect<ftl::unordered_map<int, std::string>>();

  auto it = mapped_map.find(1);
  REQUIRE(it != mapped_map.end());
  it = mapped_map.find(2);
  REQUIRE(it != mapped_map.end());
  it = mapped_map.find(3);
  REQUIRE(it != mapped_map.end());
}

TEST_CASE(TEST_TAG "count", TEST_TAG) {
  constexpr std::size_t size = 3;
  ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  REQUIRE(size == map.iter().count());
}

TEST_CASE(TEST_TAG "count const", TEST_TAG) {
  constexpr std::size_t size = 3;
  const ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  REQUIRE(size == map.iter().count());
}

TEST_CASE(TEST_TAG "begin", TEST_TAG) {
  ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto iter = map.iter().begin();
  REQUIRE(iter != map.iter().end());

  ++iter;
  REQUIRE(iter != map.iter().end());
}

TEST_CASE(TEST_TAG "begin const", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto iter = map.iter().begin();
  REQUIRE(iter != map.iter().end());

  ++iter;
  REQUIRE(iter != map.iter().end());
}

TEST_CASE(TEST_TAG "cbegin", TEST_TAG) {
  ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto iter = map.iter().begin();
  REQUIRE(iter != map.iter().end());

  ++iter;
  REQUIRE(iter != map.iter().end());
}

TEST_CASE(TEST_TAG "cbegin const", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto iter = map.iter().begin();
  REQUIRE(iter != map.iter().end());

  ++iter;
  REQUIRE(iter != map.iter().end());
}

TEST_CASE(TEST_TAG "operator++", TEST_TAG) {
  ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto iter = map.iter().begin();
  REQUIRE(iter != map.iter().end());

  ++iter;
  REQUIRE(iter != map.iter().end());
}

TEST_CASE(TEST_TAG "operator++ const", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto iter = map.iter().begin();
  REQUIRE(iter != map.iter().end());

  ++iter;
  REQUIRE(iter != map.iter().end());
}

 TEST_CASE(TEST_TAG "all elements satisfy predicate", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto element = map.iter().all([](const auto &x) { return x.second.size() > 2; });

  REQUIRE(element);
}

TEST_CASE(TEST_TAG "not all elements satisfy predicate", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto element = map.iter().all([](const auto &x) { return x.first > 2; });

  REQUIRE_FALSE(element);
}