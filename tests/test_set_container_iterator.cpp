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

TEST_CASE(TEST_TAG "find", TEST_TAG) {
  const ftl::set<std::string> set = { { "red", "green", "blue" } };

  auto element = set.iter().find([](const auto &x) { return x.size() > 4; });
  REQUIRE(element.has_value());
  REQUIRE(element.value() == "green");
}

TEST_CASE(TEST_TAG "find element not in set", TEST_TAG) {
  const ftl::set<std::string> set = { { "red", "green", "blue" } };

  auto element = set.iter().find([](const auto &x) { return x.size() > 10; });
  REQUIRE_FALSE(element.has_value());
  REQUIRE(element == std::nullopt);
}

TEST_CASE(TEST_TAG "all elements satisfy predicate", TEST_TAG) {
  const ftl::set<std::string> set = { { "red", "green", "blue" } };

  auto element = set.iter().all([](const auto &x) { return x.size() >= 3; });

  REQUIRE(element);
}

TEST_CASE(TEST_TAG "not all elements satisfy predicate", TEST_TAG) {
  const ftl::set<std::string> set = { { "red", "green", "blue" } };

  auto element = set.iter().all([](const auto &x) { return x.size() > 4; });

  REQUIRE_FALSE(element);
}

TEST_CASE(TEST_TAG "any", TEST_TAG) {
  const ftl::set<std::string> set = { { "red", "green", "blue" } };

  REQUIRE(set.iter().any([](const auto &x) { return x == "red"; }) == true);
  REQUIRE(set.iter().any([](const auto &x) { return x == "purple"; }) == false);
}

TEST_CASE(TEST_TAG "min", TEST_TAG) {
  const ftl::set<int> set = { { 3, 1, 5, 0, -1, 4, 4, 7 } };

  const auto min = set.iter().min();
  REQUIRE(min.has_value() == true);
  REQUIRE(min.value() == -1);
}

TEST_CASE(TEST_TAG "min empty", TEST_TAG) {
  const ftl::set<int> set = {};

  const auto min = set.iter().min();
  REQUIRE_FALSE(min.has_value());
}

TEST_CASE(TEST_TAG "max", TEST_TAG) {
  const ftl::set<int> set = { { 3, 1, 12, 0, -1, 4, 4, 7 } };

  REQUIRE(set.iter().max().value() == 12);
}

TEST_CASE(TEST_TAG "max empty range", TEST_TAG) {
  const ftl::set<int> set = {};

  REQUIRE(set.iter().max().has_value() == false);
}

TEST_CASE(TEST_TAG "max equal range lower than zero", TEST_TAG) {
  const ftl::set<int> set = { { -2, -2, -2 } };

  REQUIRE(set.iter().max().value() == -2);
}

TEST_CASE(TEST_TAG "max equal range greater than zero", TEST_TAG) {
  const ftl::set<int> set = { { 2, 2, 2 } };

  REQUIRE(set.iter().max().value() == 2);
}

TEST_CASE(TEST_TAG "max at the beginning", TEST_TAG) {
  const ftl::set<int> set = { { 4, 3, -1 } };

  REQUIRE(set.iter().max().value() == 4);
}

TEST_CASE(TEST_TAG "max at the end", TEST_TAG) {
  const ftl::set<int> set = { { -1, 3, 7 } };

  REQUIRE(set.iter().max().value() == 7);
}

TEST_CASE(TEST_TAG "partition", TEST_TAG) {
  ftl::set<int> set = { { 1, 3, 2, 0, 2, 5, 7, 8 } };

  const auto is_even = [](const auto &x) { return x % 2 == 0; };
  auto [coll1, coll2] = set.iter().partition<ftl::set<int>>(is_even);

  for (const auto &e : coll1) { REQUIRE(is_even(e) == true); }
  for (const auto &e : coll2) { REQUIRE(is_even(e) == false); }
}

TEST_CASE(TEST_TAG "partition first empty", TEST_TAG) {
  ftl::set<int> set = { { 1, 3, 9, 5 } };

  const auto is_even = [](const auto &x) { return x % 2 == 0; };
  auto [coll1, coll2] = set.iter().partition<ftl::set<int>>(is_even);

  REQUIRE(coll1.empty() == true);
  for (const auto &e : coll2) { REQUIRE(is_even(e) == false); }
}

TEST_CASE(TEST_TAG "partition second empty", TEST_TAG) {
  ftl::set<int> set = { { 8, 2, 4, 0 } };

  const auto is_even = [](const auto &x) { return x % 2 == 0; };
  auto [coll1, coll2] = set.iter().partition<ftl::set<int>>(is_even);

  for (const auto &e : coll1) { REQUIRE(is_even(e) == true); }
  REQUIRE(coll2.empty() == true);
}

TEST_CASE(TEST_TAG "partition no criteria met", TEST_TAG) {
  ftl::set<int> set = { { 1, 2, 3, 4 } };

  const auto has_seven = [](const auto &x) { return x == 7; };
  auto [coll1, coll2] = set.iter().partition<ftl::set<int>>(has_seven);

  REQUIRE(coll1.empty() == true);

  int i = 0;
  for (const auto &e : coll2) { REQUIRE(e == ++i); }
}
