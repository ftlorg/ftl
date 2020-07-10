#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

TEST_CASE("Factorials are computed with constexpr", "[factorial]")
{
  STATIC_REQUIRE(ftl::factorial(1) == 1);
  STATIC_REQUIRE(ftl::factorial(2) == 2);
  STATIC_REQUIRE(ftl::factorial(3) == 6);
  STATIC_REQUIRE(ftl::factorial(10) == 3628800);
}
