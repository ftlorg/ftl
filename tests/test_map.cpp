#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

#define TEST_TAG "[map]"

TEST_CASE(TEST_TAG "default ctor", TEST_TAG) {
  ftl::map<std::string, int> map;

  REQUIRE(map.size() == 0);
}

TEST_CASE(TEST_TAG "input iterator ctor", TEST_TAG) {
  ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };

  ftl::map<std::string, int> map2 = { std::begin(map1), std::end(map1) };

  REQUIRE(map1.size() == map2.size());
  REQUIRE(map1["red"] == map2["red"]);
  REQUIRE(map1["green"] == map2["green"]);
  REQUIRE(map1["blue"] == map2["blue"]);
}

TEST_CASE(TEST_TAG "copy ctor", TEST_TAG) {
  ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };
  ftl::map<std::string, int> map2 = map1;

  REQUIRE(map1.size() == map2.size());
  REQUIRE(map1["red"] == map2["red"]);
  REQUIRE(map1["green"] == map2["green"]);
  REQUIRE(map1["blue"] == map2["blue"]);
}

TEST_CASE(TEST_TAG "move ctor", TEST_TAG) {
  ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };
  ftl::map<std::string, int> map2 = std::move(map1);

  REQUIRE(map2.size() == 3);
  REQUIRE(map2["red"] == 1);
  REQUIRE(map2["green"] == 2);
  REQUIRE(map2["blue"] == 3);
}

TEST_CASE(TEST_TAG "initializer list ctor", TEST_TAG) {
  ftl::map<std::string, int> map = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };

  REQUIRE(map.size() == 3);
  REQUIRE(map["red"] == 1);
  REQUIRE(map["green"] == 2);
  REQUIRE(map["blue"] == 3);
}

TEST_CASE(TEST_TAG "operator=", TEST_TAG) {
  ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };
  ftl::map<std::string, int> map2;
  map2 = map1;

  REQUIRE(map1.size() == map2.size());
  REQUIRE(map1["red"] == map2["red"]);
  REQUIRE(map1["green"] == map2["green"]);
  REQUIRE(map1["blue"] == map2["blue"]);
}

TEST_CASE(TEST_TAG "move operator=", TEST_TAG) {
  ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };
  ftl::map<std::string, int> map2;
  map2 = std::move(map1);

  REQUIRE(map2.size() == 3);
  REQUIRE(map2["red"] == 1);
  REQUIRE(map2["green"] == 2);
  REQUIRE(map2["blue"] == 3);
}

TEST_CASE(TEST_TAG "at", TEST_TAG) {
  ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };

  REQUIRE(map1.at("red") == 1);
  REQUIRE(map1.at("green") == 2);
  REQUIRE(map1.at("blue") == 3);
  REQUIRE_THROWS(map1.at("orange"));
}

TEST_CASE(TEST_TAG "operator[]", TEST_TAG) {
  ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };

  REQUIRE(map1["red"] == 1);
  REQUIRE(map1["green"] == 2);
  REQUIRE(map1["blue"] == 3);
}

TEST_CASE(TEST_TAG "begin", TEST_TAG) {
  ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };

  REQUIRE(map1.begin()->first == "blue");
}

TEST_CASE(TEST_TAG "begin const", TEST_TAG) {
  const ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };

  REQUIRE(map1.begin()->first == "blue");
}

TEST_CASE(TEST_TAG "cbegin const", TEST_TAG) {
  const ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };

  REQUIRE(map1.cbegin()->first == "blue");
}

TEST_CASE(TEST_TAG "rbegin", TEST_TAG) {
  ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };

  REQUIRE(map1.rbegin()->first == "red");
}

TEST_CASE(TEST_TAG "rbegin const", TEST_TAG) {
  const ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };

  REQUIRE(map1.rbegin()->first == "red");
}

TEST_CASE(TEST_TAG "crbegin const", TEST_TAG) {
  const ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };

  REQUIRE(map1.crbegin()->first == "red");
}

TEST_CASE(TEST_TAG "empty", TEST_TAG) {
  ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };

  REQUIRE_FALSE(map1.empty());
}

TEST_CASE(TEST_TAG "empty const", TEST_TAG) {
  const ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };

  REQUIRE_FALSE(map1.empty());
}

TEST_CASE(TEST_TAG "size", TEST_TAG) {
  ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };

  REQUIRE(map1.size() == 3);
}

TEST_CASE(TEST_TAG "size const", TEST_TAG) {
  const ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };

  REQUIRE(map1.size() == 3);
}

TEST_CASE(TEST_TAG "clear", TEST_TAG) {
  ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };

  map1.clear();

  REQUIRE_FALSE(!map1.empty());
}

TEST_CASE(TEST_TAG "insert", TEST_TAG) {
  ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };

  REQUIRE(map1.size() == 3);
  REQUIRE(map1["red"] == 1);
  REQUIRE(map1["green"] == 2);
  REQUIRE(map1["blue"] == 3);

  map1.insert({ "orange", 4 });

  REQUIRE(map1.size() == 4);
  REQUIRE(map1["orange"] == 4);
}

TEST_CASE(TEST_TAG "insert_or_assign", TEST_TAG) {
  ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };

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

TEST_CASE(TEST_TAG "erase by iterator", TEST_TAG) {
  ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };

  auto it = std::begin(map1);
  map1.erase(it);

  REQUIRE(map1.size() == 2);
  REQUIRE(map1["red"] == 1);
  REQUIRE(map1["green"] == 2);
}

TEST_CASE(TEST_TAG "erase with key", TEST_TAG) {
  ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };

  map1.erase("blue");

  REQUIRE(map1.size() == 2);
  REQUIRE(map1["red"] == 1);
  REQUIRE(map1["green"] == 2);
}

TEST_CASE(TEST_TAG "erase range", TEST_TAG) {
  ftl::map<std::string, int> map1 = {
    { "red", 1 },
    { "green", 2 },
    { "blue", 3 },
  };

  map1.erase(std::begin(map1), std::end(map1));

  REQUIRE_FALSE(!map1.empty());
}
