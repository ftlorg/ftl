#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

#include <array>

TEST_CASE("to_array", "[array]") {
  constexpr std::size_t size = 5;
  std::array<int, size> arr = { 1, 2, 3, 4, 6 };

  const auto converted_arr = ftl::to_array(arr);

  REQUIRE(converted_arr[0] == 1);
  REQUIRE(converted_arr[1] == 2);
  REQUIRE(converted_arr[2] == 3);
  REQUIRE(converted_arr[3] == 4);
  REQUIRE(converted_arr[4] == 6);
}

TEST_CASE("operator[]", "[array]") {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { 1, 2, 3, 4, 6 };

  REQUIRE(arr[0] == 1);
  REQUIRE(arr[1] == 2);
  REQUIRE(arr[2] == 3);
  REQUIRE(arr[3] == 4);
  REQUIRE(arr[4] == 6);
}

TEST_CASE("operator[] const", "[array]") {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { 1, 2, 3, 4, 6 };

  REQUIRE(arr[0] == 1);
  REQUIRE(arr[1] == 2);
  REQUIRE(arr[2] == 3);
  REQUIRE(arr[3] == 4);
  REQUIRE(arr[4] == 6);
}

TEST_CASE("front", "[array]") {
  constexpr std::size_t size = 2;
  ftl::array<int, size> arr = { 2, 3 };

  REQUIRE(arr.front() == 2);
}

TEST_CASE("front const", "[array]") {
  constexpr std::size_t size = 2;
  const ftl::array<int, size> arr = { 2, 3 };

  REQUIRE(arr.front() == 2);
}

TEST_CASE("back", "[array]") {
  constexpr std::size_t size = 2;
  ftl::array<int, size> arr = { 2, 3 };

  REQUIRE(arr.back() == 3);
}

TEST_CASE("back const", "[array]") {
  constexpr std::size_t size = 2;
  const ftl::array<int, size> arr = { 2, 3 };

  REQUIRE(arr.back() == 3);
}

TEST_CASE("data", "[array]") {
  constexpr std::size_t size = 2;
  ftl::array<int, size> arr = { 2, 3 };

  REQUIRE(arr.data()[0] == 2);
  REQUIRE(arr.data()[1] == 3);
}

TEST_CASE("data const", "[array]") {
  constexpr std::size_t size = 2;
  const ftl::array<int, size> arr = { 2, 3 };

  REQUIRE(arr.data()[0] == 2);
  REQUIRE(arr.data()[1] == 3);
}

TEST_CASE("size", "[array]") {
  constexpr std::size_t size = 2;
  const ftl::array<int, size> arr = {};

  REQUIRE(arr.size() == 2);
}

TEST_CASE("max_size", "[array]") {
  constexpr std::size_t size = 2;
  const ftl::array<int, size> arr = {};

  REQUIRE(arr.size() == 2);
}

TEST_CASE("empty", "[array]") {
  constexpr std::size_t size = 1;
  const ftl::array<int, size> arr = {};

  REQUIRE(arr.empty() == false);
}

TEST_CASE("fill", "[array]") {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr1 = {};
  ftl::array<int, size> arr2 = { 1337, 1337, 1337, 1337, 1337 };
  arr1.fill(1337);

  REQUIRE(arr1 == arr2);
}

TEST_CASE("swap", "[array]") {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr1 = { 5, 5, 5, 5, 5 };
  ftl::array<int, size> arr2 = { 1337, 1337, 1337, 1337, 1337 };
  arr1.swap(arr2);

  REQUIRE(arr1 == ftl::array<int, size>{ 1337, 1337, 1337, 1337, 1337 });
  REQUIRE(arr2 == ftl::array<int, size>{ 5, 5, 5, 5, 5 });
}

TEST_CASE("iter", "[array]") {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  [[maybe_unused]] auto iter = arr.iter();
}

TEST_CASE("iter const", "[array]") {
  constexpr std::size_t size = 5;
  const ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  [[maybe_unused]] auto iter = arr.iter();
}
