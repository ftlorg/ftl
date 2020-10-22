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

TEST_CASE(TEST_TAG "collect into std::map_unordered", TEST_TAG) {
  ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };
  ftl::unordered_map<int, std::string> map_result = {};

  map.iter().collect_into(map_result);

  REQUIRE(map_result == map);
}

TEST_CASE(TEST_TAG "collect const to std::map_unordered", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };
  ftl::unordered_map<int, std::string> map_result = {};

  map.iter().collect_into(map_result);

  REQUIRE(map_result == map);
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

TEST_CASE(TEST_TAG "any", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  REQUIRE(map.iter().any([](const auto &x) { return x.second == "red"; }) == true);
  REQUIRE(map.iter().any([](const auto &x) { return x.second == "purple"; }) == false);
}

TEST_CASE(TEST_TAG "partition", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  const auto is_even = [](const auto &x) { return x.first % 2 == 0; };
  auto [coll1, coll2] = map.iter().partition<ftl::vector<std::pair<int, std::string>>>(is_even);

  REQUIRE(coll1.size() == 1);
  REQUIRE(coll2.size() == 2);
}

TEST_CASE(TEST_TAG "partition first empty", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 3, "green" }, { 5, "blue" } };

  const auto is_even = [](const auto &x) { return x.first % 2 == 0; };
  auto [coll1, coll2] = map.iter().partition<ftl::vector<std::pair<int, std::string>>>(is_even);

  REQUIRE(coll1.empty() == true);
  REQUIRE(coll2.size() == 3);
}

TEST_CASE(TEST_TAG "partition second empty", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map = { { 2, "red" }, { 4, "green" }, { 6, "blue" } };

  const auto is_even = [](const auto &x) { return x.first % 2 == 0; };
  auto [coll1, coll2] = map.iter().partition<ftl::vector<std::pair<int, std::string>>>(is_even);

  REQUIRE(coll1.size() == 3);
  REQUIRE(coll2.empty() == true);
}

TEST_CASE(TEST_TAG "partition no criteria met", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  const auto has_seven = [](const auto &x) { return x.first == 7; };
  auto [coll1, coll2] = map.iter().partition<ftl::vector<std::pair<int, std::string>>>(has_seven);

  REQUIRE(coll1.empty() == true);
  REQUIRE(coll2.size() == 3);
}

TEST_CASE(TEST_TAG "find", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto element = map.iter().find([](const auto &x) { return x.first > 2; });
  REQUIRE(element.has_value());
  REQUIRE(element.value() == std::pair<const int, std::string>{ 3, "blue" });
}

TEST_CASE(TEST_TAG "find element not in map", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto element = map.iter().find([](const auto &x) { return x.first > 5; });
  REQUIRE_FALSE(element.has_value());
  REQUIRE(element == std::nullopt);
}

TEST_CASE(TEST_TAG "fold", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map
    = { { 1, "red" }, { 2, "green" }, { 3, "blue" }, { 4, "purple" }, { 5, "pink" } };

  const auto sum = map.iter().fold(0, [](auto acc, const auto &x) { return acc += x.first; });

  REQUIRE(sum == map.iter().count() * (1 + 5) / 2);
}

TEST_CASE(TEST_TAG "for_each", TEST_TAG) {
  const ftl::unordered_map<int, std::string> map
    = { { 1, "red" }, { 2, "green" }, { 3, "blue" }, { 4, "purple" }, { 5, "pink" } };

  int sum = 0;
  map.iter().for_each([&sum](const auto &x) { sum += x.first; });

  REQUIRE(sum == map.iter().count() * (1 + 5) / 2);
}