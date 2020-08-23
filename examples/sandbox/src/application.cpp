#include <sandbox/application.hpp>

#include <iostream>

#include <ftl/ftl.hpp>

int Application::exec() {
  ftl::array<int, 5> arr = { 1, 2, 3, 4, 5 };

  [[maybe_unused]] auto mapped_array = arr.iter()
                        .inspect([](const auto &x) { std::cout << "Before mapping: " << x << std::endl; })
                        .map([](const auto &x) { return x * x; })
                        .inspect([](const auto &x) { std::cout << "After mapping: " << x << std::endl; })
                        .collect<ftl::array<int, 5>>();

  return 0;
}
