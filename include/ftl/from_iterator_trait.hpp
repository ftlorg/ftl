
// Copyright Grzegorz Litarowicz and Lukasz Gut 2020 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once
#include <algorithm>
namespace ftl {

/**
 * This trait must be specialized for iterator types
 * that can be converted into a collection.
 *
 * @tparam Iter The iterator type which is being converted to a collection.
 * @tparam Collection The type of a collection to which we want to convert from a given T.
 */
template<typename Iter, typename Collection>
struct from_iterator_trait {
  [[nodiscard]] constexpr static auto from_iter(const Iter &iter) -> Collection {
    return Collection{ iter.begin(), iter.end() };
  }

  constexpr static auto from_iter_into_collection(const Iter &iter, Collection &collection) -> void {
    collection.insert(collection.cend(), iter.begin(), iter.end());
  }

  [[nodiscard]] constexpr static auto from_iter_sorted(const Iter &iter) -> Collection {
    Collection collection{ iter.begin(), iter.end() };
    std::sort(collection.begin(), collection.end());
    return collection;
  }
};

}// namespace ftl
