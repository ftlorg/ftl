#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

#define TEST_TAG "[set]"

TEST_CASE(TEST_TAG "default ctor", TEST_TAG) {
  ftl::set<std::string> set;

  REQUIRE(set.empty());
}

TEST_CASE(TEST_TAG "input iterator ctor", TEST_TAG) {
  ftl::set<std::string> set1 = { { std::string("red"), std::string("green"), std::string("blue") } };

  ftl::set<std::string> set2 = { { std::begin(set1), std::end(set1) } };

  REQUIRE(set1.size() == set2.size());
  REQUIRE(*set1.find("red") == *set2.find("red"));
  REQUIRE(*set1.find("green") == *set2.find("green"));
  REQUIRE(*set1.find("blue") == *set2.find("blue"));
}

TEST_CASE(TEST_TAG "copy ctor", TEST_TAG) {
  ftl::set<std::string> set1 = { { std::string("red"), std::string("green"), std::string("blue") } };
  ftl::set<std::string> set2 = set1;

  REQUIRE(set1.size() == set2.size());
  REQUIRE(*set1.find("red") == *set2.find("red"));
  REQUIRE(*set1.find("green") == *set2.find("green"));
  REQUIRE(*set1.find("blue") == *set2.find("blue"));
}

TEST_CASE(TEST_TAG "move ctor", TEST_TAG) {
  ftl::set<std::string> set1 = { { "red", "green", "blue" } };
  ftl::set<std::string> set2 = std::move(set1);

  REQUIRE(set2.size() == 3);
  REQUIRE(set2.find("red") != set2.end());
  REQUIRE(set2.find("green") != set2.end());
  REQUIRE(set2.find("blue") != set2.end());
}

TEST_CASE(TEST_TAG "insert elements which already exist", TEST_TAG) {
  ftl::set<std::string> set = { { "red", "green", "blue" } };
  set.insert("blue");
  set.insert("green");
  set.insert("red");

  REQUIRE(set.size() == 3);
}

TEST_CASE(TEST_TAG "operator=", TEST_TAG) {
  ftl::set<std::string> set1 = { { "red", "green", "blue" } };
  ftl::set<std::string> set2{};
  set2 = set1;

  REQUIRE(set2.size() == 3);
  REQUIRE(set2.find("red") != set2.end());
  REQUIRE(set2.find("green") != set2.end());
  REQUIRE(set2.find("blue") != set2.end());
}

TEST_CASE(TEST_TAG "move operator=", TEST_TAG) {
  ftl::set<std::string> set1 = { { "red", "green", "blue" } };
  ftl::set<std::string> set2{};
  set2 = std::move(set1);

  REQUIRE(set1.empty());
  REQUIRE(set2.size() == 3);
  REQUIRE(set2.find("red") != set2.end());
  REQUIRE(set2.find("green") != set2.end());
  REQUIRE(set2.find("blue") != set2.end());
}

TEST_CASE(TEST_TAG "begin", TEST_TAG) {
  ftl::set<std::string> set1 = { { "red", "green", "blue" } };

  REQUIRE(set1.begin() != set1.end());
}

TEST_CASE(TEST_TAG "begin const", TEST_TAG) {
  const ftl::set<std::string> set1 = { { "red", "green", "blue" } };

  REQUIRE(set1.begin() != set1.end());
}

TEST_CASE(TEST_TAG "empty", TEST_TAG) {
  ftl::set<std::string> set1 = { { "red", "green", "blue" } };

  REQUIRE_FALSE(set1.empty());
}

TEST_CASE(TEST_TAG "empty const", TEST_TAG) {
  ftl::set<std::string> set1 = { { "red", "green", "blue" } };

  REQUIRE_FALSE(set1.empty());
}

TEST_CASE(TEST_TAG "size", TEST_TAG) {
  ftl::set<std::string> set1 = { { "red", "green", "blue" } };

  REQUIRE(set1.size() == 3);
}

TEST_CASE(TEST_TAG "size const", TEST_TAG) {
  const ftl::set<std::string> set1 = { { "red", "green", "blue" } };

  REQUIRE(set1.size() == 3);
}

TEST_CASE(TEST_TAG "clear", TEST_TAG) {
  ftl::set<std::string> set1 = { { "red", "green", "blue" } };

  set1.clear();

  REQUIRE(set1.empty());
}

TEST_CASE(TEST_TAG "insert", TEST_TAG) {
  ftl::set<std::string> set = { { "red", "green", "blue" } };

  REQUIRE(set.size() == 3);
  set.insert("blue");
  set.insert("green");
  set.insert("red");
  set.insert({ "orange" });

  REQUIRE(set.size() == 4);
  REQUIRE(set.find("orange") != set.end());
}

TEST_CASE(TEST_TAG "emplace", TEST_TAG) {
  ftl::set<std::string> set1 = {};

  set1.emplace("red");
  set1.emplace("green");
  set1.emplace("blue");

  REQUIRE(set1.size() == 3);
}

TEST_CASE(TEST_TAG "emplace_hint", TEST_TAG) {
  ftl::set<std::string> set1 = { { "red" } };

  set1.emplace_hint(set1.begin(), "green");
  set1.emplace_hint(set1.begin(), "blue");

  REQUIRE(set1.size() == 3);
}

TEST_CASE(TEST_TAG "erase by iter", TEST_TAG) {
  ftl::set<std::string> set = { { "red", "green", "blue", "blue" } };

  auto it = set.find("blue");
  set.erase(it);

  REQUIRE(set.size() == 2);
}

TEST_CASE(TEST_TAG "erase with key", TEST_TAG) {
  ftl::set<std::string> set = { { "red", "green", "blue", "blue" } };

  set.erase("blue");

  REQUIRE(set.size() == 2);
}

TEST_CASE(TEST_TAG "erase range", TEST_TAG) {
  ftl::set<std::string> set = { { "red", "green", "blue", "blue" } };

  set.erase(std::begin(set), std::end(set));

  REQUIRE_FALSE(!set.empty());
}

TEST_CASE(TEST_TAG "swap", TEST_TAG) {
  ftl::set<std::string> set1 = { { "red", "green", "blue", "blue" } };

  REQUIRE(set1.size() == 3);

  ftl::set<std::string> set2 = { { "orange", "purple" } };

  REQUIRE(set2.size() == 2);

  set1.swap(set2);

  REQUIRE(set1.size() == 2);
  REQUIRE(set2.size() == 3);
}

TEST_CASE(TEST_TAG "extract by iter", TEST_TAG) {
  ftl::set<std::string> set1 = { { "red", "green", "blue" } };

  auto it = set1.find("red");
  auto handle = set1.extract(it);

  REQUIRE(handle.value() == "red");

  REQUIRE(set1.size() == 2);
}

TEST_CASE(TEST_TAG "extract by key", TEST_TAG) {
  ftl::set<std::string> set1 = { { "red", "green", "blue" } };

  auto handle = set1.extract("red");

  REQUIRE(handle.value() == "red");

  REQUIRE(set1.size() == 2);
}

TEST_CASE(TEST_TAG "merge", TEST_TAG) {
  ftl::set<std::string> ma{ { "apple", "pear", "banana" } };
  ftl::set<std::string> mb{ { "zorro", "batman", "X", "alpaca", "apple" } };
  ftl::set<std::string> u;
  u.merge(ma);
  REQUIRE(u.size() == 3);

  u.merge(mb);
  REQUIRE(u.size() == 7);
}

TEST_CASE(TEST_TAG "count", TEST_TAG) {
  ftl::set<std::string> set1 = { { "red", "green", "blue" } };

  REQUIRE(set1.count("red") == 1);
  REQUIRE(set1.count("orange") == 0);
}

TEST_CASE(TEST_TAG "find", TEST_TAG) {
  ftl::set<std::string> set1 = { { "red", "green", "blue" } };

  auto found_it = set1.find("red");

  REQUIRE(found_it != std::end(set1));
  REQUIRE(*found_it == "red");

  auto not_found_it = set1.find("orange");
  REQUIRE(not_found_it == std::end(set1));
}

TEST_CASE(TEST_TAG "equal_range", TEST_TAG) {
  ftl::set<std::string> set1 = { { "red", "green", "blue" } };

  auto [lower_bound, upper_bound] = set1.equal_range("red");

  REQUIRE(lower_bound == set1.lower_bound("red"));

  REQUIRE(upper_bound == set1.upper_bound("red"));
}

TEST_CASE(TEST_TAG "lower_bound", TEST_TAG) {
  ftl::set<std::string> set1 = { { "red", "green", "blue" } };

  auto lower_bound = set1.lower_bound("blue");

  REQUIRE(lower_bound != std::end(set1));
}

TEST_CASE(TEST_TAG "upper_bound", TEST_TAG) {
  ftl::set<std::string> set1 = { { "red", "green", "blue" } };

  auto upper_bound = set1.upper_bound("red");

  REQUIRE(upper_bound == std::end(set1));
}
