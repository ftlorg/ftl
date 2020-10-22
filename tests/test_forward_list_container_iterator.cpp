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

TEST_CASE(TEST_TAG "collect into std::vector", TEST_TAG) {
  ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };
  std::vector<int> vec;
  list.iter().collect_into(vec);

  REQUIRE(vec == std::vector<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect const into std::vector", TEST_TAG) {
  const ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };
  std::vector<int> vec;
  list.iter().collect_into(vec);

  REQUIRE(vec == std::vector<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect into std::list", TEST_TAG) {
  ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };
  std::list<int> list_result;
  list.iter().collect_into(list_result);

  REQUIRE(list_result == std::list<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect const into std::list", TEST_TAG) {
  const ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };
  std::list<int> list_result;
  list.iter().collect_into(list_result);

  REQUIRE(list_result == std::list<int>{ 1, 2, 3, 4, 5 });
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

TEST_CASE(TEST_TAG "any", TEST_TAG) {
  ftl::forward_list<std::string> list = { { "red", "green", "blue" } };

  REQUIRE(list.iter().any([](const auto &x) { return x == "red"; }) == true);
  REQUIRE(list.iter().any([](const auto &x) { return x == "purple"; }) == false);
}

TEST_CASE(TEST_TAG "min", TEST_TAG) {
  const ftl::forward_list<int> list = { { 3, 1, 5, 0, -1, 4, 4, 7 } };

  const auto min = list.iter().min();
  REQUIRE(min.has_value() == true);
  REQUIRE(min.value() == -1);
}

TEST_CASE(TEST_TAG "min empty", TEST_TAG) {
  const ftl::forward_list<int> list = {};

  const auto min = list.iter().min();
  REQUIRE_FALSE(min.has_value());
}

TEST_CASE(TEST_TAG "max", TEST_TAG) {
  const ftl::forward_list<int> list = { { 3, 1, 12, 0, -1, 4, 4, 7 } };

  REQUIRE(list.iter().max().value() == 12);
}

TEST_CASE(TEST_TAG "max empty range", TEST_TAG) {
  const ftl::forward_list<int> list = {};

  REQUIRE(list.iter().max().has_value() == false);
}

TEST_CASE(TEST_TAG "max equal range lower than zero", TEST_TAG) {
  const ftl::forward_list<int> list = { { -2, -2, -2 } };

  REQUIRE(list.iter().max().value() == -2);
}

TEST_CASE(TEST_TAG "max equal range greater than zero", TEST_TAG) {
  const ftl::forward_list<int> list = { { 2, 2, 2 } };

  REQUIRE(list.iter().max().value() == 2);
}

TEST_CASE(TEST_TAG "max at the beginning", TEST_TAG) {
  const ftl::forward_list<int> list = { { 4, 3, -1 } };

  REQUIRE(list.iter().max().value() == 4);
}

TEST_CASE(TEST_TAG "max at the end", TEST_TAG) {
  const ftl::forward_list<int> list = { { -1, 3, 7 } };

  REQUIRE(list.iter().max().value() == 7);
}

TEST_CASE(TEST_TAG "all elements satisfy predicate", TEST_TAG) {
  const ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };

  auto element = list.iter().all([](const auto &number) { return number < 10; });

  REQUIRE(element);
}

TEST_CASE(TEST_TAG "not all elements satisfy predicate", TEST_TAG) {
  const ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };

  auto element = list.iter().all([](const auto &number) { return number == 3; });

  REQUIRE_FALSE(element);
}

TEST_CASE(TEST_TAG "partition", TEST_TAG) {
  ftl::list<int> list = { { 1, 3, 2, 0, 2, 5, 7, 8 } };

  const auto is_even = [](const auto &x) { return x % 2 == 0; };
  auto [coll1, coll2] = list.iter().partition<ftl::list<int>>(is_even);

  for (const auto &e : coll1) { REQUIRE(is_even(e) == true); }
  for (const auto &e : coll2) { REQUIRE(is_even(e) == false); }
}

TEST_CASE(TEST_TAG "partition first empty", TEST_TAG) {
  ftl::list<int> list = { { 1, 3, 9, 5 } };

  const auto is_even = [](const auto &x) { return x % 2 == 0; };
  auto [coll1, coll2] = list.iter().partition<ftl::list<int>>(is_even);

  REQUIRE(coll1.empty() == true);
  for (const auto &e : coll2) { REQUIRE(is_even(e) == false); }
}

TEST_CASE(TEST_TAG "partition second empty", TEST_TAG) {
  ftl::list<int> list = { { 8, 2, 4, 0 } };

  const auto is_even = [](const auto &x) { return x % 2 == 0; };
  auto [coll1, coll2] = list.iter().partition<ftl::list<int>>(is_even);

  for (const auto &e : coll1) { REQUIRE(is_even(e) == true); }
  REQUIRE(coll2.empty() == true);
}

TEST_CASE(TEST_TAG "partition no criteria met", TEST_TAG) {
  ftl::list<int> list = { { 1, 2, 3, 4 } };

  const auto has_seven = [](const auto &x) { return x == 7; };
  auto [coll1, coll2] = list.iter().partition<ftl::list<int>>(has_seven);

  REQUIRE(coll1.empty() == true);

  int i = 0;
  for (const auto &e : coll2) { REQUIRE(e == ++i); }
}

TEST_CASE(TEST_TAG "find", TEST_TAG) {
  const ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };

  auto element = list.iter().find([](const auto &number) { return number == 3; });
  REQUIRE(element.has_value());
  REQUIRE(element.value() == 3);
}

TEST_CASE(TEST_TAG "find element not in list", TEST_TAG) {
  const ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };

  auto element = list.iter().find([](const auto &number) { return number == 0; });
  REQUIRE_FALSE(element.has_value());
  REQUIRE(element == std::nullopt);
}

TEST_CASE(TEST_TAG "fold", TEST_TAG) {
  const ftl::forward_list<int> list = { 1, 2, 3, 4, 5 };

  const auto sum = list.iter().fold(0, [](auto acc, const auto &x) { return acc += x; });

  REQUIRE(sum == list.iter().count() * (1 + 5) / 2);
}

TEST_CASE(TEST_TAG "for_each", TEST_TAG) {
  const ftl::forward_list<int> list = { { 1, 2, 3, 4, 5 } };

  int sum = 0;
  list.iter().for_each([&sum](const auto &x) { sum += x; });

  REQUIRE(sum == list.iter().count() * (1 + 5) / 2);
}
