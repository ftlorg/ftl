#pragma once

#include <optional>

namespace ftl {

/// \brief Factorial
///
/// This computes a factorial
///

constexpr unsigned int factorial(unsigned int number)
{
  return number <= 1 ? number : factorial(number - 1) * number;
}

constexpr std::optional<int> get_optional() {
  return {5};
}

int fun();

}// namespace ftl

