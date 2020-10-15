
// Copyright Grzegorz Litarowicz and £ukasz Gut 2020 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

namespace ftl {

/**
 * This trait must be specialized for data types
 * that can be converted into an iterator.
 *
 * @tparam T The type which is being converted to an iterator.
 * @tparam U The type of an iterator suitable for type T.
 */
template<typename T, typename U>
struct into_iterator_trait {
  [[nodiscard]] constexpr static auto into_iter(T &) -> U {
    return {};
  }
};

}// namespace ftl
