#pragma once

#include <optional>

#include <ftl/iterator.hpp>
#include <ftl/array.hpp>

namespace ftl {

/// \brief Factorial
///
/// This computes a factorial
///

constexpr unsigned int factorial(unsigned int number)
{
  return number <= 1 ? number : factorial(number - 1) * number;
}

}// namespace ftl

