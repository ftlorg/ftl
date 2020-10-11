#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>
#include <vector>
#include <list>
#include <utility>

#define TEST_TAG "[map_container_iterator]"

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

TEST_CASE(TEST_TAG "collect into std::vector", TEST_TAG) {
  ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };
  std::vector<std::pair<int, std::string>> vec;
  map.iter().collect_into(vec);

  REQUIRE(vec == std::vector<std::pair<int, std::string>>{ { 1, "red" }, { 2, "green" }, { 3, "blue" } });
}

TEST_CASE(TEST_TAG "collect const into std::vector", TEST_TAG) {
  const ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };
  std::vector<std::pair<int, std::string>> vec;
  map.iter().collect_into(vec);

  REQUIRE(vec == std::vector<std::pair<int, std::string>>{ { 1, "red" }, { 2, "green" }, { 3, "blue" } });
}

TEST_CASE(TEST_TAG "collect into std::map", TEST_TAG) {
  ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };
  std::map<int, std::string> map_result;
  map.iter().collect_into(map_result);

  REQUIRE(map_result == std::map<int, std::string>{ { 1, "red" }, { 2, "green" }, { 3, "blue" } });
}

TEST_CASE(TEST_TAG "collect const into std::map", TEST_TAG) {
  const ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };
  std::map<int, std::string> map_result;
  map.iter().collect_into(map_result);

  REQUIRE(map_result == std::map<int, std::string>{ { 1, "red" }, { 2, "green" }, { 3, "blue" } });
}

TEST_CASE(TEST_TAG "map collect", TEST_TAG) {
  ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter()
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .collect<ftl::map<int, std::string>>();

  REQUIRE(mapped_map == ftl::map<int, std::string>{ { 1, "redabc" }, { 2, "greenabc" }, { 3, "blueabc" } });
}

TEST_CASE(TEST_TAG "map collect const", TEST_TAG) {
  const ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter()
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .collect<ftl::map<int, std::string>>();

  REQUIRE(mapped_map == ftl::map<int, std::string>{ { 1, "redabc" }, { 2, "greenabc" }, { 3, "blueabc" } });
}

TEST_CASE(TEST_TAG "map map collect", TEST_TAG) {
  ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter()
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .collect<ftl::map<int, std::string>>();

  REQUIRE(mapped_map == ftl::map<int, std::string>{ { 1, "redabcabc" }, { 2, "greenabcabc" }, { 3, "blueabcabc" } });
}

TEST_CASE(TEST_TAG "map map collect const", TEST_TAG) {
  const ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter()
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .collect<ftl::map<int, std::string>>();

  REQUIRE(mapped_map == ftl::map<int, std::string>{ { 1, "redabcabc" }, { 2, "greenabcabc" }, { 3, "blueabcabc" } });
}

TEST_CASE(TEST_TAG "enumerate collect", TEST_TAG) {
  ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  for (const auto &e : map.iter().enumerate()) { INFO(std::get<0>(e)); }

  auto mapped_map = map.iter().enumerate().collect<ftl::map<std::size_t, std::pair<const int, std::string>>>();

  REQUIRE(mapped_map
          == ftl::map<std::size_t, std::pair<const int, std::string>>{
            { 0, { 1, "red" } },
            { 1, { 2, "green" } },
            { 2, { 3, "blue" } },
          });
}

TEST_CASE(TEST_TAG "enumerate collect const", TEST_TAG) {
  const ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  for (const auto &e : map.iter().enumerate()) { INFO(std::get<0>(e)); }

  auto mapped_map = map.iter().enumerate().collect<ftl::map<std::size_t, std::tuple<const int, std::string>>>();

  REQUIRE(mapped_map
          == ftl::map<std::size_t, std::tuple<const int, std::string>>{
            { 0, { 1, "red" } },
            { 1, { 2, "green" } },
            { 2, { 3, "blue" } },
          });
}

TEST_CASE(TEST_TAG "map enumerate collect", TEST_TAG) {
  ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  for (const auto &e : map.iter().enumerate()) { INFO(std::get<0>(e)); }

  auto mapped_map = map.iter()
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .enumerate()
                      .collect<ftl::map<std::size_t, std::pair<const int, std::string>>>();

  REQUIRE(mapped_map
          == ftl::map<std::size_t, std::pair<const int, std::string>>{
            { 0, { 1, "redabc" } },
            { 1, { 2, "greenabc" } },
            { 2, { 3, "blueabc" } },
          });
}

TEST_CASE(TEST_TAG "map enumerate collect const", TEST_TAG) {
  const ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  for (const auto &e : map.iter().enumerate()) { INFO(std::get<0>(e)); }

  auto mapped_map = map.iter()
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .enumerate()
                      .collect<ftl::map<std::size_t, std::tuple<const int, std::string>>>();

  REQUIRE(mapped_map
          == ftl::map<std::size_t, std::tuple<const int, std::string>>{
            { 0, { 1, "redabc" } },
            { 1, { 2, "greenabc" } },
            { 2, { 3, "blueabc" } },
          });
}

TEST_CASE(TEST_TAG "map inspect map collect", TEST_TAG) {
  ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter()
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .inspect([](const auto &entry) { INFO(entry.second); })
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .collect<ftl::map<int, std::string>>();

  REQUIRE(mapped_map == ftl::map<int, std::string>{ { 1, "redabcabc" }, { 2, "greenabcabc" }, { 3, "blueabcabc" } });
}

TEST_CASE(TEST_TAG "map inspect map collect const", TEST_TAG) {
  const ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto mapped_map = map.iter()
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .inspect([](const auto &entry) { INFO(entry.second); })
                      .map([](const auto &entry) {
                        return std::pair<const int, std::string>{ entry.first, entry.second + "abc" };
                      })
                      .collect<ftl::map<int, std::string>>();

  REQUIRE(mapped_map == ftl::map<int, std::string>{ { 1, "redabcabc" }, { 2, "greenabcabc" }, { 3, "blueabcabc" } });
}

// TODO: Fix this code
// TEST_CASE(TEST_TAG "enumerate map collect", TEST_TAG) {
//  ftl::map<int, std::string> map = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };
//
//  for (const auto &e : map.iter().enumerate()) { INFO(std::get<0>(e)); }
//
//  auto mapped_map = map.iter()
//                      .enumerate()
//                      .map([](const auto &entry) {
//                        const auto &index = std::get<0>(entry);
//                        const auto &former_entry = std::get<1>(entry);
//
//                        return std::pair<const std::size_t, std::pair<const int, std::string>>{
//                          index,
//                          { former_entry.first, former_entry.second + "abc" },
//                        };
//                      })
//                      .collect<ftl::map<std::size_t, std::pair<const int, std::string>>>();
//
//  REQUIRE(mapped_map
//          == ftl::map<std::size_t, std::pair<const int, std::string>>{
//            { 0, { 1, "redabc" } },
//            { 1, { 2, "greenabc" } },
//            { 2, { 3, "blueabc" } },
//          });
//}


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
