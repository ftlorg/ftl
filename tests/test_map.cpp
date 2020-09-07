#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

#define TEST_TAG "[map]"

TEST_CASE(TEST_TAG "default ctor", TEST_TAG) {
  ftl::map<std::string, int> map;

  REQUIRE(map.size() == 0);
}