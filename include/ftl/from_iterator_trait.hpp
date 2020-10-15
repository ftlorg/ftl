
// Copyright Grzegorz Litarowicz and Lukasz Gut 2020 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

namespace ftl {

/**
 * This trait must be specialized for iterator types
 * that can be converted into a collection.
 *
 * @tparam T The iterator type which is being converted to a collection.
 * @tparam U The type of a collection to which we want to convert from a given T.
 */
template<typename T, typename U>
struct from_iterator_trait {
  [[nodiscard]] constexpr static auto from_iter(const T &iter) -> U {
    return U { iter.begin(), iter.end() };
  }
};

}// namespace ftl
