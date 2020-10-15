#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>
#include <vector>
#include <list>

#define TEST_TAG "[array_container_iterator]"

TEST_CASE(TEST_TAG "collect", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().collect<ftl::array<int, size>>();

  constexpr std::size_t size2 = 3;
  ftl::array<int, size2> arr2 = { { 1, 2, 3 } };

  auto mapped_arr2 = arr2.iter().collect<ftl::array<int, size2>>();

  REQUIRE(mapped_arr == ftl::array<int, size>{ { 1, 2, 3, 4, 5 } });
  REQUIRE(mapped_arr2 == ftl::array<int, size2>{ { 1, 2, 3 } });
}

TEST_CASE(TEST_TAG "collect to std::vector", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().collect<std::vector<int>>();

  REQUIRE(mapped_arr == std::vector<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect const to std::vector", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().collect<std::vector<int>>();

  REQUIRE(mapped_arr == std::vector<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect to std::list", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().collect<std::list<int>>();

  REQUIRE(mapped_arr == std::list<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect const to std::list", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().collect<std::list<int>>();

  REQUIRE(mapped_arr == std::list<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "collect const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().collect<ftl::array<int, size>>();

  constexpr std::size_t size2 = 3;
  const ftl::array<int, size2> arr2 = { { 1, 2, 3 } };

  auto mapped_arr2 = arr2.iter().collect<ftl::array<int, size2>>();

  REQUIRE(mapped_arr == ftl::array<int, size>{ { 1, 2, 3, 4, 5 } });
  REQUIRE(mapped_arr2 == ftl::array<int, size2>{ { 1, 2, 3 } });
}

TEST_CASE(TEST_TAG "count", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  REQUIRE(5 == arr.iter().count());
}

TEST_CASE(TEST_TAG "count const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  REQUIRE(5 == arr.iter().count());
}

TEST_CASE(TEST_TAG "begin", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto iter = arr.iter().begin();
  REQUIRE(arr[0] == *iter);

  ++iter;
  REQUIRE(arr[1] == *iter);
}

TEST_CASE(TEST_TAG "begin const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto iter = arr.iter().begin();
  REQUIRE(arr[0] == *iter);

  ++iter;
  REQUIRE(arr[1] == *iter);
}

TEST_CASE(TEST_TAG "cbegin", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto iter = arr.iter().cbegin();
  REQUIRE(arr[0] == *iter);

  ++iter;
  REQUIRE(arr[1] == *iter);
}

TEST_CASE(TEST_TAG "cbegin const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto iter = arr.iter().cbegin();
  REQUIRE(arr[0] == *iter);

  ++iter;
  REQUIRE(arr[1] == *iter);
}

TEST_CASE(TEST_TAG "operator++", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto iter = arr.iter();
  REQUIRE(arr[0] == *iter);

  ++iter;
  REQUIRE(arr[1] == *iter);

  ++iter;
  REQUIRE(arr[2] == *iter);

  ++iter;
  REQUIRE(arr[3] == *iter);

  ++iter;
  REQUIRE(arr[4] == *iter);

  ++iter;
  REQUIRE(iter == iter.end());
}

TEST_CASE(TEST_TAG "operator++ const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto iter = arr.iter();
  REQUIRE(arr[0] == *iter);

  ++iter;
  REQUIRE(arr[1] == *iter);

  ++iter;
  REQUIRE(arr[2] == *iter);

  ++iter;
  REQUIRE(arr[3] == *iter);

  ++iter;
  REQUIRE(arr[4] == *iter);
}

TEST_CASE(TEST_TAG "operator--", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto iter = arr.iter() + 4;
  REQUIRE(arr[4] == *iter);
  REQUIRE(arr[3] == *(--iter));
  REQUIRE(arr[2] == *(--iter));
  REQUIRE(arr[1] == *(--iter));
  REQUIRE(arr[0] == *(--iter));
}

TEST_CASE(TEST_TAG "operator-- const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto iter = arr.iter() + 4;
  REQUIRE(arr[4] == *iter);
  REQUIRE(arr[3] == *(--iter));
  REQUIRE(arr[2] == *(--iter));
  REQUIRE(arr[1] == *(--iter));
  REQUIRE(arr[0] == *(--iter));
}

TEST_CASE(TEST_TAG "operator+=", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto iter = arr.iter();
  iter += 4;
  REQUIRE(arr[4] == *iter);
}

TEST_CASE(TEST_TAG "product", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 2, 4, 6, 8, 10 } };

  auto product = arr.iter().product();

  REQUIRE(product == 3840);
}

TEST_CASE(TEST_TAG "find", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto elem = arr.iter().find([](const auto &element) { return element % 2 == 0; });

  REQUIRE(elem.has_value());
  REQUIRE(elem.value() == 2);
}

TEST_CASE(TEST_TAG "find element not in array", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 7, 3, 11, 5 } };

  auto elem = arr.iter().find([](const auto &element) { return element % 2 == 0; });

  REQUIRE_FALSE(elem.has_value());
  REQUIRE(elem == std::nullopt);
}


TEST_CASE(TEST_TAG "all elements satisfy predicate", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 2, 4, 6, 8, 10 } };

  auto elem = arr.iter().all([](const auto &element) { return element % 2 == 0; });

  REQUIRE(elem);
}

TEST_CASE(TEST_TAG "not all elements satisfy predicate", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 7, 3, 11, 5 } };

  auto elem = arr.iter().all([](const auto &element) { return element % 2 == 0; });

  REQUIRE_FALSE(elem);
}

TEST_CASE(TEST_TAG "any", TEST_TAG) {
  constexpr std::size_t size = 3;
  ftl::array<std::string, size> arr = { { "red", "green", "blue" } };

  REQUIRE(arr.iter().any([](const auto &x) { return x == "red"; }) == true);
  REQUIRE(arr.iter().any([](const auto &x) { return x == "purple"; }) == false);
}

TEST_CASE(TEST_TAG "min", TEST_TAG) {
  constexpr std::size_t size = 8;
  const ftl::array<int, size> arr = { { 3, 1, 5, 0, -1, 4, 4, 7 } };

  const auto min = arr.iter().min();
  REQUIRE(min.has_value() == true);
  REQUIRE(min.value() == -1);
}

TEST_CASE(TEST_TAG "max", TEST_TAG) {
  constexpr std::size_t size = 8;
  ftl::array<int, size> arr = { { 3, 1, 12, 0, -1, 4, 4, 7 } };

  REQUIRE(arr.iter().max().value() == 12);
}

TEST_CASE(TEST_TAG "max empty range", TEST_TAG) {
  constexpr std::size_t size = 0;
  ftl::array<int, size> arr = {};

  REQUIRE(arr.iter().max().has_value() == false);
}

TEST_CASE(TEST_TAG "max equal range lower than zero", TEST_TAG) {
  constexpr std::size_t size = 3;
  ftl::array<int, size> arr = { { -2, -2, -2 } };

  REQUIRE(arr.iter().max().value() == -2);
}

TEST_CASE(TEST_TAG "max equal range greater than zero", TEST_TAG) {
  constexpr std::size_t size = 3;
  ftl::array<int, size> arr = { { 2, 2, 2 } };

  REQUIRE(arr.iter().max().value() == 2);
}

TEST_CASE(TEST_TAG "max at the beginning", TEST_TAG) {
  constexpr std::size_t size = 3;
  ftl::array<int, size> arr = { { 4, 3, -1 } };

  REQUIRE(arr.iter().max().value() == 4);
}

TEST_CASE(TEST_TAG "max at the end", TEST_TAG) {
  constexpr std::size_t size = 3;
  ftl::array<int, size> arr = { { -1, 3, 7 } };

  REQUIRE(arr.iter().max().value() == 7);
}

TEST_CASE(TEST_TAG "partition", TEST_TAG) {
  constexpr std::size_t size = 8;
  ftl::array<int, size> arr = { { 1, 3, 2, 0, 2, 5, 7, 8 } };

  const auto is_even = [](const auto &x) { return x % 2 == 0; };
  auto [coll1, coll2] = arr.iter().partition<ftl::list<int>>(is_even);

  for (const auto &e : coll1) { REQUIRE(is_even(e) == true); }
  for (const auto &e : coll2) { REQUIRE(is_even(e) == false); }
}

TEST_CASE(TEST_TAG "partition first empty", TEST_TAG) {
  constexpr std::size_t size = 4;
  ftl::array<int, size> arr = { { 1, 3, 9, 5 } };

  const auto is_even = [](const auto &x) { return x % 2 == 0; };
  auto [coll1, coll2] = arr.iter().partition<ftl::list<int>>(is_even);

  REQUIRE(coll1.empty() == true);
  for (const auto &e : coll2) { REQUIRE(is_even(e) == false); }
}

TEST_CASE(TEST_TAG "partition second empty", TEST_TAG) {
  constexpr std::size_t size = 4;
  ftl::array<int, size> arr = { { 8, 2, 4, 0 } };

  const auto is_even = [](const auto &x) { return x % 2 == 0; };
  auto [coll1, coll2] = arr.iter().partition<ftl::list<int>>(is_even);

  for (const auto &e : coll1) { REQUIRE(is_even(e) == true); }
  REQUIRE(coll2.empty() == true);
}

TEST_CASE(TEST_TAG "partition no criteria met", TEST_TAG) {
  constexpr std::size_t size = 4;
  ftl::array<int, size> arr = { { 1, 2, 3, 4 } };

  const auto has_seven = [](const auto &x) { return x == 7; };
  auto [coll1, coll2] = arr.iter().partition<ftl::list<int>>(has_seven);

  REQUIRE(coll1.empty() == true);

  int i = 0;
  for (const auto &e : coll2) { REQUIRE(e == ++i); }
}

TEST_CASE(TEST_TAG "sum", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 2, 4, 6, 8, 10 } };

  auto sum = arr.iter().sum();

  REQUIRE(sum == 30);
}

TEST_CASE(TEST_TAG "fold", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  const auto sum = arr.iter().fold(0, [](auto acc, const auto &x) { return acc += x; });

  REQUIRE(sum == arr.iter().count() * (1 + 5) / 2);
}
