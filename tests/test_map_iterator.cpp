#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>
#include <vector>
#include <list>

#define TEST_TAG "[map_iterator]"

TEST_CASE(TEST_TAG "operator--", TEST_TAG) {
  ftl::vector<int> vec = { { 1, 2, 3, 4, 5 } };

  auto iter = vec.iter().map([](const auto &x) { return x; }) + 4;
  REQUIRE(vec[4] == *iter);
  REQUIRE(vec[3] == *(--iter));
  REQUIRE(vec[2] == *(--iter));
  REQUIRE(vec[1] == *(--iter));
  REQUIRE(vec[0] == *(--iter));
}

TEST_CASE(TEST_TAG "operator-- const", TEST_TAG) {
  const ftl::vector<int> vec = { { 1, 2, 3, 4, 5 } };

  auto iter = vec.iter().map([](const auto &x) { return x; }) + 4;
  REQUIRE(vec[4] == *iter);
  REQUIRE(vec[3] == *(--iter));
  REQUIRE(vec[2] == *(--iter));
  REQUIRE(vec[1] == *(--iter));
  REQUIRE(vec[0] == *(--iter));
}

TEST_CASE(TEST_TAG "map collect", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().map([](const auto &x) { return x * x; }).collect<ftl::array<int, size>>();

  REQUIRE(mapped_arr == ftl::array<int, size>{ { 1, 4, 9, 16, 25 } });
}

TEST_CASE(TEST_TAG "map collect const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().map([](const auto &x) { return x * x; }).collect<ftl::array<int, size>>();

  REQUIRE(mapped_arr == ftl::array<int, size>{ { 1, 4, 9, 16, 25 } });
}

TEST_CASE(TEST_TAG "collect to std::vector", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().map([](const auto &x) { return x * x; }).collect<std::vector<int>>();

  REQUIRE(mapped_arr == std::vector<int>{ 1, 4, 9, 16, 25 });
}

TEST_CASE(TEST_TAG "collect const to std::vector", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().map([](const auto &x) { return x * x; }).collect<std::vector<int>>();

  REQUIRE(mapped_arr == std::vector<int>{ 1, 4, 9, 16, 25 });
}

TEST_CASE(TEST_TAG "collect to std::list", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().map([](const auto &x) { return x * x; }).collect<std::list<int>>();

  REQUIRE(mapped_arr == std::list<int>{ 1, 4, 9, 16, 25 });
}

TEST_CASE(TEST_TAG "collect to std::list of doubles", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr
    = arr.iter()
        .map([](const auto &x) { return x * x; })
        .map([](const auto &x) { return std::make_pair<double, double>(static_cast<double>(x), static_cast<double>(x)); })
        .map([](const auto &p) { return p; })
        .collect<std::list<std::pair<double, double>>>();

  REQUIRE(mapped_arr
          == std::list<std::pair<double, double>>{
            { 1.0, 1.0 },
            { 4.0, 4.0 },
            { 9.0, 9.0 },
            { 16.0, 16.0 },
            { 25.0, 25.0 },
          });
}

TEST_CASE(TEST_TAG "collect const to std::list", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().map([](const auto &x) { return x * x; }).collect<std::list<int>>();

  REQUIRE(mapped_arr == std::list<int>{ 1, 4, 9, 16, 25 });
}

TEST_CASE(TEST_TAG "chain map", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter()
                      .map([](const auto &x) { return x * x; })
                      .map([](const auto &x) { return 2 * x; })
                      .collect<ftl::array<int, size>>();

  REQUIRE(mapped_arr == ftl::array<int, size>{ { 2, 8, 18, 32, 50 } });
}

TEST_CASE(TEST_TAG "chain map const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter()
                      .map([](const auto &x) { return x * x; })
                      .map([](const auto &x) { return 2 * x; })
                      .collect<ftl::array<int, size>>();

  REQUIRE(mapped_arr == ftl::array<int, size>{ { 2, 8, 18, 32, 50 } });
}

TEST_CASE(TEST_TAG "map any", TEST_TAG) {
  ftl::vector<std::string> vec = { { "red", "green", "blue" } };

  REQUIRE(vec.iter().map([](const auto &x) { return x + "abc"; }).any([](const auto &x) { return x[0] == 'g'; }) == true);
  REQUIRE(vec.iter().map([](const auto &x) { return x + "abc"; }).any([](const auto &x) { return x[0] == 'x'; }) == false);
}

TEST_CASE(TEST_TAG "map map any", TEST_TAG) {
  ftl::vector<int> vec = { { 1, 2, 3 } };

  REQUIRE(
    vec.iter().map([](const auto &x) { return x + 1; }).map([](const auto &x) { return 2 * x; }).any([](const auto &x) {
      return x == 8;
    })
    == true);
  REQUIRE(
    vec.iter().map([](const auto &x) { return x + 1; }).map([](const auto &x) { return 2 * x; }).any([](const auto &x) {
      return x == 7;
    })
    == false);
}

TEST_CASE(TEST_TAG "map min", TEST_TAG) {
  ftl::list<int> list = { { 3, 1, 5, 0, -1, 4, 4, 7 } };

  const auto min = list.iter().map([](const auto &x) { return x < 0 ? -x : x; }).min();
  REQUIRE(min.has_value() == true);
  REQUIRE(min.value() == 0);
}

TEST_CASE(TEST_TAG "find", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto element
    = arr.iter().map([](const auto &x) { return x * x; }).map([](const auto &x) { return 2 * x; }).find([](const auto &x) {
        return x > 15;
      });

  REQUIRE(element.has_value());
  REQUIRE(element.value() == 18);
}

TEST_CASE(TEST_TAG "find element not in array", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto element
    = arr.iter().map([](const auto &x) { return x * x; }).map([](const auto &x) { return 2 * x; }).find([](const auto &x) {
        return x % 2;
      });

  REQUIRE_FALSE(element.has_value());
  REQUIRE(element == std::nullopt);
}

TEST_CASE(TEST_TAG "map max", TEST_TAG) {
  const ftl::forward_list<int> list = { { 3, 1, 12, 0, -1, 4, 4, 7 } };

  REQUIRE(list.iter().map([](const auto &x) { return x; }).max().value() == 12);
}

TEST_CASE(TEST_TAG "map max equal range lower than zero", TEST_TAG) {
  const ftl::forward_list<int> list = { { -2, -2, -2 } };

  REQUIRE(list.iter().map([](const auto &x) { return x; }).max().value() == -2);
}

TEST_CASE(TEST_TAG "map max equal range greater than zero", TEST_TAG) {
  const ftl::forward_list<int> list = { { 2, 2, 2 } };

  REQUIRE(list.iter().map([](const auto &x) { return x; }).max().value() == 2);
}

TEST_CASE(TEST_TAG "map max at the beginning", TEST_TAG) {
  const ftl::forward_list<int> list = { { 4, 3, -1 } };

  REQUIRE(list.iter().map([](const auto &x) { return x; }).max().value() == 4);
}

TEST_CASE(TEST_TAG "map max at the end", TEST_TAG) {
  const ftl::forward_list<int> list = { { -1, 3, 7 } };

  REQUIRE(list.iter().map([](const auto &x) { return x; }).max().value() == 7);
}

TEST_CASE(TEST_TAG "all elements satisfy predicate", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto element
    = arr.iter().map([](const auto &x) { return x * x; }).map([](const auto &x) { return 2 * x; }).all([](const auto &x) {
        return x % 2 == 0;
      });

  REQUIRE(element);
}

TEST_CASE(TEST_TAG "not all elements satisfy predicate", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto element
    = arr.iter().map([](const auto &x) { return x * x; }).map([](const auto &x) { return 2 * x; }).all([](const auto &x) {
        return x > 15;
      });

  REQUIRE_FALSE(element);
}

TEST_CASE(TEST_TAG "map partition", TEST_TAG) {
  ftl::list<int> list = { { 1, 3, 2, 0, 2, 5, 7, 8 } };

  const auto is_even = [](const auto &x) { return x % 2 == 0; };
  auto [coll1, coll2] = list.iter().map([](const auto &x) { return x; }).partition<ftl::list<int>>(is_even);

  for (const auto &e : coll1) { REQUIRE(is_even(e) == true); }
  for (const auto &e : coll2) { REQUIRE(is_even(e) == false); }
}

TEST_CASE(TEST_TAG "map partition first empty", TEST_TAG) {
  ftl::list<int> list = { { 1, 3, 9, 5 } };

  const auto is_even = [](const auto &x) { return x % 2 == 0; };
  auto [coll1, coll2] = list.iter().map([](const auto &x) { return x; }).partition<ftl::list<int>>(is_even);

  REQUIRE(coll1.empty() == true);
  for (const auto &e : coll2) { REQUIRE(is_even(e) == false); }
}

TEST_CASE(TEST_TAG "map partition second empty", TEST_TAG) {
  ftl::list<int> list = { { 8, 2, 4, 0 } };

  const auto is_even = [](const auto &x) { return x % 2 == 0; };
  auto [coll1, coll2] = list.iter().map([](const auto &x) { return x; }).partition<ftl::list<int>>(is_even);

  for (const auto &e : coll1) { REQUIRE(is_even(e) == true); }
  REQUIRE(coll2.empty() == true);
}

TEST_CASE(TEST_TAG "map partition no criteria met", TEST_TAG) {
  ftl::list<int> list = { { 1, 2, 3, 4 } };

  const auto has_seven = [](const auto &x) { return x == 7; };
  auto [coll1, coll2] = list.iter().map([](const auto &x) { return x; }).partition<ftl::list<int>>(has_seven);

  REQUIRE(coll1.empty() == true);

  int i = 0;
  for (const auto &e : coll2) { REQUIRE(e == ++i); }
}

TEST_CASE(TEST_TAG "sum", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto sum = arr.iter().map([](const auto &x) { return x * x; }).map([](const auto &x) { return 2 * x; }).sum();

  REQUIRE(sum == 110);
}

TEST_CASE(TEST_TAG "product", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto product = arr.iter().map([](const auto &x) { return x * x; }).map([](const auto &x) { return 2 * x; }).product();

  REQUIRE(product == 460800);
}

TEST_CASE(TEST_TAG "map fold", TEST_TAG) {
  const ftl::list<int> list{ { 1, 2, 3, 4, 5 } };

  const auto sum
    = list.iter().map([](const auto &x) { return x; }).fold(0, [](auto acc, const auto &x) { return acc += x; });

  REQUIRE(sum == list.iter().count() * (1 + 5) / 2);
}

TEST_CASE(TEST_TAG "map for_each", TEST_TAG) {
  const ftl::list<int> list{ { 1, 2, 3, 4, 5 } };

  int sum = 0;
  list.iter().map([](const auto &x) { return x; }).for_each([&sum](const auto &x) {
    return sum += x;
  });

  REQUIRE(sum == list.iter().count() * (1 + 5) / 2);
}
