#pragma once

#include <optional>

#include <ftl/array.hpp>
#include <ftl/into_iterator_trait.hpp>
#include <ftl/iterator_interface.hpp>

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

