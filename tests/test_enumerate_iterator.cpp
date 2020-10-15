#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

#define TEST_TAG "[enumerate_iterator]"

TEST_CASE(TEST_TAG "enumerate", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  for (const auto &[index, item] : arr.iter().enumerate()) {
    REQUIRE(arr[index] == item);
    REQUIRE(&arr[index] == &item);
  }
}

TEST_CASE(TEST_TAG "enumerate const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  for (const auto &[index, item] : arr.iter().enumerate()) {
    REQUIRE(arr[index] == item);
    REQUIRE(&arr[index] == &item);
  }
}

TEST_CASE(TEST_TAG "enumerate enumerate", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  for (const auto &[index, enumerateTuple] : arr.iter().enumerate().enumerate()) {
    REQUIRE(index == std::get<0>(enumerateTuple));
    REQUIRE(arr[index] == std::get<1>(enumerateTuple));
    REQUIRE(&arr[index] == &std::get<1>(enumerateTuple));
  }
}

TEST_CASE(TEST_TAG "enumerate enumerate const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  for (const auto &[index, enumerateTuple] : arr.iter().enumerate().enumerate()) {
    REQUIRE(index == std::get<0>(enumerateTuple));
    REQUIRE(arr[index] == std::get<1>(enumerateTuple));
    REQUIRE(&arr[index] == &std::get<1>(enumerateTuple));
  }
}

TEST_CASE(TEST_TAG "enumerate size", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  REQUIRE(size == arr.iter().enumerate().count());
}

TEST_CASE(TEST_TAG "enumerate size const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  REQUIRE(size == arr.iter().enumerate().count());
}

TEST_CASE(TEST_TAG "enumerate with side effects", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  for (auto &&[index, item] : arr.iter().enumerate()) { item = static_cast<int>(size - index); }

  REQUIRE(arr == ftl::array<int, size>{ { 5, 4, 3, 2, 1 } });
}

TEST_CASE(TEST_TAG "preincrement", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto iter = arr.iter().enumerate();
  REQUIRE(*iter == std::make_tuple(0, 1));

  ++iter;
  REQUIRE(*iter == std::make_tuple(1, 2));

  ++iter;
  REQUIRE(*iter == std::make_tuple(2, 3));

  ++iter;
  REQUIRE(*iter == std::make_tuple(3, 4));

  ++iter;
  REQUIRE(*iter == std::make_tuple(4, 5));
}

TEST_CASE(TEST_TAG "preincrement const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto iter = arr.iter().enumerate();
  REQUIRE(*iter == std::make_tuple(0, 1));

  ++iter;
  REQUIRE(*iter == std::make_tuple(1, 2));

  ++iter;
  REQUIRE(*iter == std::make_tuple(2, 3));

  ++iter;
  REQUIRE(*iter == std::make_tuple(3, 4));

  ++iter;
  REQUIRE(*iter == std::make_tuple(4, 5));
}

TEST_CASE(TEST_TAG "map enumerate", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  for (const auto &[index, item] : arr.iter().map([](const auto &x) { return 2 * x; }).enumerate()) {
    REQUIRE(2 * arr[index] == item);
  }
}

TEST_CASE(TEST_TAG "map enumerate const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  for (const auto &[index, item] : arr.iter().map([](const auto &x) { return 2 * x; }).enumerate()) {
    REQUIRE(2 * arr[index] == item);
  }
}

TEST_CASE(TEST_TAG "enumerate collect to std::vector", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().enumerate().collect<std::vector<std::tuple<std::size_t, int>>>();

  REQUIRE(mapped_arr
          == std::vector<std::tuple<std::size_t, int>>{
            { 0, 1 },
            { 1, 2 },
            { 2, 3 },
            { 3, 4 },
            { 4, 5 },
          });
}

TEST_CASE(TEST_TAG "enumerate collect to std::vector const", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto mapped_arr = arr.iter().enumerate().collect<std::vector<std::tuple<std::size_t, int>>>();

  REQUIRE(mapped_arr
          == std::vector<std::tuple<std::size_t, int>>{
            { 0, 1 },
            { 1, 2 },
            { 2, 3 },
            { 3, 4 },
            { 4, 5 },
          });
}

TEST_CASE(TEST_TAG "enumerate any", TEST_TAG) {
  ftl::list<std::string> arr = { { "red", "green", "blue" } };

  REQUIRE(arr.iter().enumerate().any([](const auto &x) { return std::get<1>(x) == "red"; }) == true);
  REQUIRE(arr.iter().enumerate().any([](const auto &x) { return std::get<1>(x) == "green"; }) == true);
  REQUIRE(arr.iter().enumerate().any([](const auto &x) { return std::get<1>(x) == "blue"; }) == true);
}

TEST_CASE(TEST_TAG "enumerate filter any", TEST_TAG) {
  ftl::list<std::string> arr = { { "red", "green", "blue" } };

  REQUIRE(arr.iter().enumerate().filter([](const auto &x) { return std::get<1>(x) != "green"; }).any([](const auto &x) {
    return std::get<1>(x) == "red";
  }) == true);
  REQUIRE(arr.iter().enumerate().filter([](const auto &x) { return std::get<1>(x) != "green"; }).any([](const auto &x) {
    return std::get<1>(x) == "green";
  }) == false);
  REQUIRE(arr.iter().enumerate().filter([](const auto &x) { return std::get<1>(x) != "green"; }).any([](const auto &x) {
    return std::get<1>(x) == "blue";
  }) == true);
}

TEST_CASE(TEST_TAG "enumerate min", TEST_TAG) {
  constexpr std::size_t size = 8;
  ftl::array<int, size> arr = { { 3, 1, 5, 0, -1, 4, 4, 7 } };

  const auto min = arr.iter().enumerate().min();
  REQUIRE(min.has_value() == true);
  REQUIRE(min.value() == std::make_tuple<std::size_t, int>(0, 3));
}

TEST_CASE(TEST_TAG "enumerate max", TEST_TAG) {
  constexpr std::size_t size = 8;
  ftl::array<int, size> arr = { { 3, 1, 12, 0, -1, 4, 4, 7 } };

  const auto max = arr.iter().enumerate().max();
  REQUIRE(max.has_value() == true);
  REQUIRE(max.value() == std::make_tuple<std::size_t, int>(7, 7));
}

TEST_CASE(TEST_TAG "enumerate max empty range", TEST_TAG) {
  constexpr std::size_t size = 0;
  ftl::array<int, size> arr = {};

  const auto max = arr.iter().enumerate().max();
  REQUIRE_FALSE(max.has_value());
}

TEST_CASE(TEST_TAG "enumerate max equal range lower than zero", TEST_TAG) {
  constexpr std::size_t size = 3;
  ftl::array<int, size> arr = { { -2, -2, -2 } };

  const auto max = arr.iter().enumerate().max();
  REQUIRE(max.has_value() == true);
  REQUIRE(max.value() == std::make_tuple<std::size_t, int>(2, -2));
}

TEST_CASE(TEST_TAG "enumerate max equal range greater than zero", TEST_TAG) {
  constexpr std::size_t size = 3;
  ftl::array<int, size> arr = { { 2, 2, 2 } };

  const auto max = arr.iter().enumerate().max();
  REQUIRE(max.has_value() == true);
  REQUIRE(max.value() == std::make_tuple<std::size_t, int>(2, 2));
}

TEST_CASE(TEST_TAG "enumerate max at the beginning", TEST_TAG) {
  constexpr std::size_t size = 3;
  ftl::array<int, size> arr = { { 4, 3, -1 } };

  const auto max = arr.iter().enumerate().max();
  REQUIRE(max.has_value() == true);
  REQUIRE(max.value() == std::make_tuple<std::size_t, int>(2, -1));
}

TEST_CASE(TEST_TAG "enumerate max at the end", TEST_TAG) {
  constexpr std::size_t size = 3;
  ftl::array<int, size> arr = { { -1, 3, 7 } };

  const auto max = arr.iter().enumerate().max();
  REQUIRE(max.has_value() == true);
  REQUIRE(max.value() == std::make_tuple<std::size_t, int>(2, 7));
}

TEST_CASE(TEST_TAG "not all elements satisfy predicate", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto element = arr.iter().enumerate().all([](const auto &x) { return std::get<1>(x) < 3; });
  REQUIRE_FALSE(element);
}

TEST_CASE(TEST_TAG "all elements satisfy predicate", TEST_TAG) {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { { 1, 2, 3, 4, 5 } };

  auto element = arr.iter().enumerate().all([](const auto &x) { return std::get<1>(x) > 0; });
  REQUIRE(element);
}

TEST_CASE(TEST_TAG "enumerate partition", TEST_TAG) {
  ftl::list<int> list = { { 1, 3, 2, 0, 2, 5, 7, 8 } };

  const auto is_even = [](const auto &x) { return std::get<1>(x) % 2 == 0; };
  auto [coll1, coll2] = list.iter().enumerate().partition<ftl::list<std::tuple<std::size_t, int>>>(is_even);

  REQUIRE(coll1.size() == 4);
  REQUIRE(coll2.size() == 4);
}

TEST_CASE(TEST_TAG "enumerate partition first empty", TEST_TAG) {
  ftl::list<int> list = { { 1, 3, 9, 5 } };

  const auto is_even = [](const auto &x) { return std::get<1>(x) % 2 == 0; };
  auto [coll1, coll2] = list.iter().enumerate().partition<ftl::list<std::tuple<std::size_t, int>>>(is_even);

  REQUIRE(coll1.empty() == true);
  REQUIRE(coll2.size() == 4);
}

TEST_CASE(TEST_TAG "enumerate partition second empty", TEST_TAG) {
  ftl::list<int> list = { { 8, 2, 4, 0 } };

  const auto is_even = [](const auto &x) { return std::get<1>(x) % 2 == 0; };
  auto [coll1, coll2] = list.iter().enumerate().partition<ftl::list<std::tuple<std::size_t, int>>>(is_even);

  REQUIRE(coll1.size() == 4);
  REQUIRE(coll2.empty() == true);
}

TEST_CASE(TEST_TAG "enumerate partition no criteria met", TEST_TAG) {
  ftl::list<int> list = { { 1, 2, 3, 4 } };

  const auto has_seven = [](const auto &x) { return std::get<1>(x) == 7; };
  auto [coll1, coll2] = list.iter().enumerate().partition<ftl::list<std::tuple<std::size_t, int>>>(has_seven);

  REQUIRE(coll1.empty() == true);
  REQUIRE(coll2.size() == 4);
}
