#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

#define TEST_TAG "[inspect_iterator]"

TEST_CASE(TEST_TAG "inspect", TEST_TAG) {
  constexpr std::size_t size = 5;
  ftl::array<int, size> arr = { 1, 2, 3, 4, 5 };

  for ([[maybe_unused]] const auto &x : arr.iter().inspect([](const auto &x) { INFO("Inspecting x = " << x); })) {}
}
