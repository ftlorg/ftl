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
