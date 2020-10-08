#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

#define TEST_TAG "[any]"

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
