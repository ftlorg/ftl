#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

TEST_CASE("Simple test is computed", "[simple_test]")
{
  REQUIRE(ftl::fun() == 0);
}
