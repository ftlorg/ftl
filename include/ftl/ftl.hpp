#pragma once

#include <optional>

#include <ftl/array.hpp>
#include <ftl/list.hpp>
#include <ftl/map.hpp>
#include <ftl/vector.hpp>
#include <ftl/vector_iterator.hpp>
#include <ftl/from_iterator_trait.hpp>
#include <ftl/into_iterator_trait.hpp>
#include <ftl/iterator_interface.hpp>
#include <ftl/map_iterator.hpp>
#include <ftl/enumerate_iterator.hpp>

namespace ftl {

/// \brief Factorial
///
/// This computes a factorial
///

constexpr auto factorial(unsigned int number) -> unsigned int {
  return number <= 1 ? number : factorial(number - 1) * number;
}

}// namespace ftl
