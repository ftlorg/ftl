#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>
#include <vector>
#include <list>

#define TEST_TAG "[filter_iterator]"

TEST_CASE(TEST_TAG "filter collect", TEST_TAG) {
  ftl::vector<int> vec = { 1, 5, 6, 12 };

  auto f_vec = vec.iter()
                 .filter([](const auto &x) { return x % 2 == 0; })
                 .filter([](const auto &x) { return x % 3 == 0; })
                 .collect<std::vector<int>>();

  REQUIRE(f_vec == ftl::vector<int>{ 6, 12 });
}

TEST_CASE(TEST_TAG "const filter collect", TEST_TAG) {
  const ftl::vector<int> vec = { 1, 2, 3, 4, 5, 6, 12 };

  auto f_vec = vec.iter()
                 .filter([](const auto &x) { return x % 2 == 0; })
                 .filter([](const auto &x) { return x % 3 == 0; })
                 .collect<std::vector<int>>();

  REQUIRE(f_vec == ftl::vector<int>{ 6, 12 });
}

TEST_CASE(TEST_TAG "const filter collect to empty", TEST_TAG) {
  const ftl::vector<int> vec = { 1, 3, 4, 5 };

  auto f_vec = vec.iter()
                 .filter([](const auto &x) { return x % 2 == 0; })
                 .filter([](const auto &x) { return x % 3 == 0; })
                 .collect<std::vector<int>>();

  REQUIRE(f_vec.empty());
}


TEST_CASE(TEST_TAG "filter after map", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter()
                      .map([](const auto &x) { return x * x; })
                      .filter([](const auto &x) { return x % 2 == 0; })
                      .collect<std::vector<int>>();

  REQUIRE(mapped_arr == std::vector<int>{ 4, 16 });
}

TEST_CASE(TEST_TAG "filter const ftl::list", TEST_TAG) {
  const ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto f_list = list.iter().filter([](const auto &x) { return x % 2 == 0; }).collect<ftl::vector<int>>();

  REQUIRE(f_list == ftl::vector<int>{ 2, 4 });
}

TEST_CASE(TEST_TAG "filter ftl::list", TEST_TAG) {
  ftl::list<int> list = { 1, 2, 3, 4, 5 };

  auto f_list = list.iter().filter([](const auto &x) { return x % 2 == 0; }).collect<ftl::list<int>>();

  REQUIRE(f_list == ftl::list<int>{ 2, 4 });
}

TEST_CASE(TEST_TAG "filter const ftl::array", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().filter([](const auto &x) { return x > 3; }).collect<std::list<int>>();

  REQUIRE(mapped_arr == std::list<int>{ 4, 5 });
}

TEST_CASE(TEST_TAG "filter ftl::array", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().filter([](const auto &x) { return x > 3; }).collect<std::list<int>>();

  REQUIRE(mapped_arr == std::list<int>{ 4, 5 });
}

TEST_CASE(TEST_TAG "chain inspect and filter", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter()
                      .inspect([](const auto &x) { INFO("Inspecting x = " << x) })
                      .filter([](const auto &x) { return x % 2; })
                      .collect<ftl::vector<int>>();

  REQUIRE(mapped_arr == ftl::vector<int>{ 1, 3, 5 });
}

TEST_CASE(TEST_TAG "chain enumerate and filter", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter()
                      .enumerate()
                      .filter([](const auto &x) { return std::get<0>(x) > 2; })
                      .map([](const auto &x) { return std::get<1>(x); })
                      .collect<ftl::vector<int>>();

  REQUIRE(mapped_arr == ftl::vector<int>{ 4, 5 });
}

TEST_CASE(TEST_TAG "all elements satisfy predicate", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto element = arr.iter().filter([](const auto &x) { return x % 2 == 0; }).all([](const auto &elem) { return elem > 0; });

  REQUIRE(element);
}

TEST_CASE(TEST_TAG "not all elements satisfy predicate", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto element = arr.iter().filter([](const auto &x) { return x % 2 == 0; }).all([](const auto &elem) { return elem > 2; });

  REQUIRE_FALSE(element);
}

TEST_CASE(TEST_TAG "filter any", TEST_TAG) {
  ftl::forward_list<std::string> vec = { { "red", "green", "blue" } };

  REQUIRE(
    vec.iter().filter([](const auto &x) { return x != "green"; }).any([](const auto &x) { return x == "red"; }) == true);
  REQUIRE(
    vec.iter().filter([](const auto &x) { return x != "green"; }).any([](const auto &x) { return x == "green"; }) == false);
}

TEST_CASE(TEST_TAG "map filter any", TEST_TAG) {
  ftl::forward_list<int> vec = { { 1, 2, 3 } };

  REQUIRE(vec.iter()
            .map([](const auto &x) { return 2 * x; })
            .filter([](const auto &x) { return x % 2 != 0; })
            .any([](const auto &x) { return x % 2 == 0; })
          == false);
}

TEST_CASE(TEST_TAG "filter min", TEST_TAG) {
  ftl::list<int> list = { { 3, 1, 5, 0, -1, 4, 4, 7 } };

  const auto min = list.iter().filter([](const auto &x) { return x != -1; }).min();
  REQUIRE(min.has_value() == true);
  REQUIRE(min.value() == 0);
}

TEST_CASE(TEST_TAG "filter max", TEST_TAG) {
  ftl::list<int> list = { { 3, 1, 12, 0, -1, 4, 4, 7 } };

  REQUIRE(list.iter().filter([](const auto &x) { return x != 12; }).max().value() == 7);
}

TEST_CASE(TEST_TAG "filter max equal range lower than zero", TEST_TAG) {
  ftl::list<int> list = { { -2, -2, -2 } };

  REQUIRE(list.iter().filter([](const auto &x) { return x != 12; }).max().value() == -2);
  REQUIRE_FALSE(list.iter().filter([](const auto &x) { return x != -2; }).max().has_value());
}

TEST_CASE(TEST_TAG "filter max equal range greater than zero", TEST_TAG) {
  ftl::list<int> list = { { 2, 2, 2 } };

  REQUIRE(list.iter().filter([](const auto &x) { return x != 12; }).max().value() == 2);
  REQUIRE_FALSE(list.iter().filter([](const auto &x) { return x != 2; }).max().has_value());
}

TEST_CASE(TEST_TAG "filter max at the beginning", TEST_TAG) {
  ftl::list<int> list = { { 4, 3, -1 } };

  REQUIRE(list.iter().filter([](const auto &x) { return x > 3; }).max().value() == 4);
}

TEST_CASE(TEST_TAG "filter max at the end", TEST_TAG) {
  ftl::list<int> list = { { -1, 3, 7 } };

  REQUIRE(list.iter().filter([](const auto &x) { return x < 8; }).max().value() == 7);
}

TEST_CASE(TEST_TAG "filter partition", TEST_TAG) {
  ftl::list<int> list = { { 1, 3, 2, 0, 2, 5, 7, 8 } };

  const auto is_even = [](const auto &x) { return x % 2 == 0; };
  auto [coll1, coll2] = list.iter().filter([](const auto &x) { return x >= 0; }).partition<ftl::list<int>>(is_even);

  for (const auto &e : coll1) { REQUIRE(is_even(e) == true); }
  for (const auto &e : coll2) { REQUIRE(is_even(e) == false); }
}

TEST_CASE(TEST_TAG "filter partition first empty", TEST_TAG) {
  ftl::list<int> list = { { 1, 3, 9, 5 } };

  const auto is_even = [](const auto &x) { return x % 2 == 0; };
  auto [coll1, coll2] = list.iter().filter([](const auto &x) { return x >= 0; }).partition<ftl::list<int>>(is_even);

  REQUIRE(coll1.empty() == true);
  for (const auto &e : coll2) { REQUIRE(is_even(e) == false); }
}

TEST_CASE(TEST_TAG "filter partition second empty", TEST_TAG) {
  ftl::list<int> list = { { 8, 2, 4, 0 } };

  const auto is_even = [](const auto &x) { return x % 2 == 0; };
  auto [coll1, coll2] = list.iter().filter([](const auto &x) { return x >= 0; }).partition<ftl::list<int>>(is_even);

  for (const auto &e : coll1) { REQUIRE(is_even(e) == true); }
  REQUIRE(coll2.empty() == true);
}

TEST_CASE(TEST_TAG "filter partition no criteria met", TEST_TAG) {
  ftl::list<int> list = { { 1, 2, 3, 4 } };

  const auto has_seven = [](const auto &x) { return x == 7; };
  auto [coll1, coll2] = list.iter().filter([](const auto &x) { return x >= 0; }).partition<ftl::list<int>>(has_seven);

  REQUIRE(coll1.empty() == true);

  int i = 0;
  for (const auto &e : coll2) { REQUIRE(e == ++i); }
}

TEST_CASE(TEST_TAG "find", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto element = arr.iter().filter([](const auto &x) { return x % 2 == 0; }).find([](const auto &elem) { return elem > 2; });
                      

  REQUIRE(element.has_value());
  REQUIRE(element.value() == 4);
}

TEST_CASE(TEST_TAG "find element not in array", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto element
    = arr.iter().filter([](const auto &x) { return x % 2 == 0; }).find([](const auto &elem) { return elem > 10; });


  REQUIRE_FALSE(element.has_value());
  REQUIRE(element == std::nullopt);
}

TEST_CASE(TEST_TAG "sum", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto sum = arr.iter().filter([](const auto &x) { return x % 2 == 0; }).sum();

  REQUIRE(sum == 6);
}