#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

#define TEST_TAG "[map]"

TEST_CASE(TEST_TAG "default ctor", TEST_TAG) {
  ftl::map<std::string, int> map;

  REQUIRE(map.size() == 0);
}

TEST_CASE(TEST_TAG "input iterator ctor", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  ftl::map<std::string, int> map2 = { std::begin(map1), std::end(map1) };

  REQUIRE(map1.size() == map2.size());
  REQUIRE(map1["red"] == map2["red"]);
  REQUIRE(map1["green"] == map2["green"]);
  REQUIRE(map1["blue"] == map2["blue"]);
}

TEST_CASE(TEST_TAG "copy ctor", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };
  ftl::map<std::string, int> map2 = map1;

  REQUIRE(map1.size() == map2.size());
  REQUIRE(map1["red"] == map2["red"]);
  REQUIRE(map1["green"] == map2["green"]);
  REQUIRE(map1["blue"] == map2["blue"]);
}

TEST_CASE(TEST_TAG "move ctor", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };
  ftl::map<std::string, int> map2 = std::move(map1);

  REQUIRE(map2.size() == 3);
  REQUIRE(map2["red"] == 1);
  REQUIRE(map2["green"] == 2);
  REQUIRE(map2["blue"] == 3);
}

TEST_CASE(TEST_TAG "initializer list ctor", TEST_TAG) {
  ftl::map<std::string, int> map = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  REQUIRE(map.size() == 3);
  REQUIRE(map["red"] == 1);
  REQUIRE(map["green"] == 2);
  REQUIRE(map["blue"] == 3);
}

TEST_CASE(TEST_TAG "operator=", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };
  ftl::map<std::string, int> map2;
  map2 = map1;

  REQUIRE(map1.size() == map2.size());
  REQUIRE(map1["red"] == map2["red"]);
  REQUIRE(map1["green"] == map2["green"]);
  REQUIRE(map1["blue"] == map2["blue"]);
}

TEST_CASE(TEST_TAG "move operator=", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };
  ftl::map<std::string, int> map2;
  map2 = std::move(map1);

  REQUIRE(map2.size() == 3);
  REQUIRE(map2["red"] == 1);
  REQUIRE(map2["green"] == 2);
  REQUIRE(map2["blue"] == 3);
}

TEST_CASE(TEST_TAG "at", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  REQUIRE(map1.at("red") == 1);
  REQUIRE(map1.at("green") == 2);
  REQUIRE(map1.at("blue") == 3);
  REQUIRE_THROWS(map1.at("orange"));
}

TEST_CASE(TEST_TAG "operator[]", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  REQUIRE(map1["red"] == 1);
  REQUIRE(map1["green"] == 2);
  REQUIRE(map1["blue"] == 3);
}

TEST_CASE(TEST_TAG "begin", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  REQUIRE(map1.begin()->first == "blue");
}

TEST_CASE(TEST_TAG "begin const", TEST_TAG) {
  const ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  REQUIRE(map1.begin()->first == "blue");
}

TEST_CASE(TEST_TAG "cbegin const", TEST_TAG) {
  const ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  REQUIRE(map1.cbegin()->first == "blue");
}

TEST_CASE(TEST_TAG "rbegin", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  REQUIRE(map1.rbegin()->first == "red");
}

TEST_CASE(TEST_TAG "rbegin const", TEST_TAG) {
  const ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  REQUIRE(map1.rbegin()->first == "red");
}

TEST_CASE(TEST_TAG "crbegin const", TEST_TAG) {
  const ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  REQUIRE(map1.crbegin()->first == "red");
}

TEST_CASE(TEST_TAG "empty", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  REQUIRE_FALSE(map1.empty());
}

TEST_CASE(TEST_TAG "empty const", TEST_TAG) {
  const ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  REQUIRE_FALSE(map1.empty());
}

TEST_CASE(TEST_TAG "size", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  REQUIRE(map1.size() == 3);
}

TEST_CASE(TEST_TAG "size const", TEST_TAG) {
  const ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  REQUIRE(map1.size() == 3);
}

TEST_CASE(TEST_TAG "clear", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  map1.clear();

  REQUIRE_FALSE(!map1.empty());
}

TEST_CASE(TEST_TAG "insert", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  REQUIRE(map1.size() == 3);
  REQUIRE(map1["red"] == 1);
  REQUIRE(map1["green"] == 2);
  REQUIRE(map1["blue"] == 3);

  map1.insert({ "orange", 4 });

  REQUIRE(map1.size() == 4);
  REQUIRE(map1["orange"] == 4);
}

TEST_CASE(TEST_TAG "insert_or_assign", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  REQUIRE(map1.size() == 3);
  REQUIRE(map1["red"] == 1);
  REQUIRE(map1["green"] == 2);
  REQUIRE(map1["blue"] == 3);

  map1.insert_or_assign("orange", 4);

  REQUIRE(map1.size() == 4);
  REQUIRE(map1["orange"] == 4);

  map1.insert_or_assign("orange", 5);


  REQUIRE(map1.size() == 4);
  REQUIRE(map1["orange"] == 5);
}

TEST_CASE(TEST_TAG "emplace", TEST_TAG) {
  ftl::map<std::string, int> map1 = {};

  map1.emplace("red", 1);
  map1.emplace("green", 2);
  map1.emplace("blue", 3);

  REQUIRE(map1.size() == 3);
  REQUIRE(map1["red"] == 1);
  REQUIRE(map1["green"] == 2);
  REQUIRE(map1["blue"] == 3);
}

TEST_CASE(TEST_TAG "emplace_hint", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 } };

  map1.emplace_hint(map1.begin(), "green", 2);
  map1.emplace_hint(map1.begin(), "blue", 3);

  REQUIRE(map1.size() == 3);
  REQUIRE(map1["red"] == 1);
  REQUIRE(map1["green"] == 2);
  REQUIRE(map1["blue"] == 3);
}


TEST_CASE(TEST_TAG "try_emplace", TEST_TAG) {
  ftl::map<std::string, int> map1 = {};

  map1.try_emplace("red", 1);
  map1.try_emplace("green", 2);
  map1.try_emplace("blue", 3);

  REQUIRE(map1.size() == 3);
  REQUIRE(map1["red"] == 1);
  REQUIRE(map1["green"] == 2);
  REQUIRE(map1["blue"] == 3);
}

TEST_CASE(TEST_TAG "try_emplace_hint", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 } };

  map1.try_emplace(map1.begin(), "green", 2);
  map1.try_emplace(map1.begin(), "blue", 3);

  REQUIRE(map1.size() == 3);
  REQUIRE(map1["red"] == 1);
  REQUIRE(map1["green"] == 2);
  REQUIRE(map1["blue"] == 3);
}

TEST_CASE(TEST_TAG "erase by iter", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  auto it = map1.find("blue");
  map1.erase(it);

  REQUIRE(map1.size() == 2);
  REQUIRE(map1["red"] == 1);
  REQUIRE(map1["green"] == 2);
}

TEST_CASE(TEST_TAG "erase with key", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  map1.erase("blue");

  REQUIRE(map1.size() == 2);
  REQUIRE(map1["red"] == 1);
  REQUIRE(map1["green"] == 2);
}

TEST_CASE(TEST_TAG "erase range", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  map1.erase(std::begin(map1), std::end(map1));

  REQUIRE_FALSE(!map1.empty());
}

TEST_CASE(TEST_TAG "swap", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  REQUIRE(map1.size() == 3);
  REQUIRE(map1["red"] == 1);
  REQUIRE(map1["green"] == 2);
  REQUIRE(map1["blue"] == 3);

  ftl::map<std::string, int> map2 = { { "orange", 4 }, { "purple", 5 } };

  REQUIRE(map2.size() == 2);
  REQUIRE(map2["orange"] == 4);
  REQUIRE(map2["purple"] == 5);

  map1.swap(map2);

  REQUIRE(map1.size() == 2);
  REQUIRE(map1["orange"] == 4);
  REQUIRE(map1["purple"] == 5);

  REQUIRE(map2.size() == 3);
  REQUIRE(map2["red"] == 1);
  REQUIRE(map2["green"] == 2);
  REQUIRE(map2["blue"] == 3);
}

TEST_CASE(TEST_TAG "extract by iter", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  auto it = map1.find("red");
  auto handle = map1.extract(it);

  REQUIRE(handle.key() == "red");
  REQUIRE(handle.mapped() == 1);

  REQUIRE(map1.size() == 2);
  REQUIRE(map1["green"] == 2);
  REQUIRE(map1["blue"] == 3);
}

TEST_CASE(TEST_TAG "extract by key", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  auto handle = map1.extract("red");

  REQUIRE(handle.key() == "red");
  REQUIRE(handle.mapped() == 1);

  REQUIRE(map1.size() == 2);
  REQUIRE(map1["green"] == 2);
  REQUIRE(map1["blue"] == 3);
}

TEST_CASE(TEST_TAG "merge", TEST_TAG) {
  ftl::map<int, std::string> ma{ { 1, "apple" }, { 5, "pear" }, { 10, "banana" } };
  ftl::map<int, std::string> mb{ { 2, "zorro" }, { 4, "batman" }, { 5, "X" }, { 8, "alpaca" } };
  ftl::map<int, std::string> u;
  u.merge(ma);
  REQUIRE(u.size() == 3);

  u.merge(mb);
  REQUIRE(u.size() == 6);

  REQUIRE(mb.at(5) == "X");
}

TEST_CASE(TEST_TAG "count", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  REQUIRE(map1.count("red") == 1);
  REQUIRE(map1.count("orange") == 0);
}

TEST_CASE(TEST_TAG "find", TEST_TAG) {
  ftl::map<std::string, int> map1 = { { "red", 1 }, { "green", 2 }, { "blue", 3 } };

  auto found_it = map1.find("red");

  REQUIRE(found_it != std::end(map1));
  REQUIRE(found_it->first == "red");
  REQUIRE(found_it->second == 1);

  auto not_found_it = map1.find("orange");
  REQUIRE(not_found_it == std::end(map1));
}

TEST_CASE(TEST_TAG "equal_range", TEST_TAG) {
  ftl::map<int, std::string> map1 = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto [lower_bound, upper_bound] = map1.equal_range(2);

  REQUIRE(lower_bound != std::end(map1));
  REQUIRE(lower_bound->first == 2);
  REQUIRE(lower_bound->second == "green");

  REQUIRE(upper_bound != std::end(map1));
  REQUIRE(upper_bound->first == 3);
  REQUIRE(upper_bound->second == "blue");
}

TEST_CASE(TEST_TAG "lower_bound", TEST_TAG) {
  ftl::map<int, std::string> map1 = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto lower_bound = map1.lower_bound(2);

  REQUIRE(lower_bound != std::end(map1));
  REQUIRE(lower_bound->first == 2);
  REQUIRE(lower_bound->second == "green");
}

TEST_CASE(TEST_TAG "upper_bound", TEST_TAG) {
  ftl::map<int, std::string> map1 = { { 1, "red" }, { 2, "green" }, { 3, "blue" } };

  auto lower_bound = map1.upper_bound(2);

  REQUIRE(lower_bound != std::end(map1));
  REQUIRE(lower_bound->first == 3);
  REQUIRE(lower_bound->second == "blue");
}
