#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

#define TEST_TAG "[deque]"

TEST_CASE(TEST_TAG "default ctor", TEST_TAG) {
  ftl::deque<int> deq;

  REQUIRE(deq.size() == 0);
}
