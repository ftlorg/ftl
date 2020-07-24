#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

TEST_CASE("next", "[array_iterator]") {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  auto iter = arr.iter();
  REQUIRE(arr[1] == *iter.next());
}

TEST_CASE("next const", "[array_iterator]") {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  auto iter = arr.iter();
  REQUIRE(arr[1] == *iter.next());
}

TEST_CASE("count", "[array_iterator]") {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  REQUIRE(5 == arr.iter().count());
}

TEST_CASE("count const", "[array_iterator]") {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  REQUIRE(5 == arr.iter().count());
}

TEST_CASE("begin", "[array_iterator]") {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };


  auto iter = arr.iter().begin();
  REQUIRE(arr[0] == *iter);

  ++iter;
  REQUIRE(arr[1] == *iter);
}

TEST_CASE("begin const", "[array_iterator]") {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };


  auto iter = arr.iter().begin();
  REQUIRE(arr[0] == *iter);

  ++iter;
  REQUIRE(arr[1] == *iter);
}

TEST_CASE("cbegin", "[array_iterator]") {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  auto iter = arr.iter().cbegin();
  REQUIRE(arr[0] == *iter);

  ++iter;
  REQUIRE(arr[1] == *iter);
}

TEST_CASE("cbegin const", "[array_iterator]") {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  auto iter = arr.iter().cbegin();
  REQUIRE(arr[0] == *iter);

  ++iter;
  REQUIRE(arr[1] == *iter);
}

TEST_CASE("operator++", "[array_iterator]") {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

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

TEST_CASE("operator++ const", "[array_iterator]") {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

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
