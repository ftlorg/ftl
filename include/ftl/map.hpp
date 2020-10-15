
// Copyright Grzegorz Litarowicz and Lukasz Gut 2020 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <map>

#include <ftl/map_container_iterator.hpp>
#include <ftl/map_container_const_iterator.hpp>
#include <ftl/into_iterator_trait.hpp>

namespace ftl {

template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T>>>
class map : public std::map<Key, T, Compare, Allocator> {
public:
  using value_type = typename std::map<Key, T, Compare, Allocator>::value_type;
  using allocator_type = typename std::map<Key, T, Compare, Allocator>::allocator_type;
  using size_type = typename std::map<Key, T, Compare, Allocator>::size_type;
  using difference_type = typename std::map<Key, T, Compare, Allocator>::difference_type;
  using pointer = typename std::map<Key, T, Compare, Allocator>::pointer;
  using reference = typename std::map<Key, T, Compare, Allocator>::reference;
  using const_pointer = typename std::map<Key, T, Compare, Allocator>::const_pointer;
  using const_reference = typename std::map<Key, T, Compare, Allocator>::const_reference;
  using ftl_iterator = map_container_iterator<Key, T>;
  using ftl_const_iterator = map_container_const_iterator<Key, T>;
  using iterator = typename std::map<Key, T, Compare, Allocator>::iterator;
  using const_iterator = typename std::map<Key, T, Compare, Allocator>::const_iterator;
  using reverse_iterator = typename std::map<Key, T, Compare, Allocator>::reverse_iterator;
  using const_reverse_iterator = typename std::map<Key, T, Compare, Allocator>::const_reverse_iterator;

  using std::map<Key, T, Compare, Allocator>::map;

  [[nodiscard]] auto iter() noexcept -> ftl_iterator {
    return into_iterator_trait<map<Key, T, Compare, Allocator>, ftl_iterator>::into_iter(*this);
  }

  [[nodiscard]] auto iter() const noexcept -> ftl_const_iterator {
    return into_iterator_trait<map<Key, T, Compare, Allocator>, ftl_const_iterator>::into_iter(*this);
  }
};

template<typename Key, typename T, typename Compare, typename Allocator>
[[nodiscard]] constexpr auto to_map(const std::map<Key, T, Compare, Allocator> &map)
  -> ftl::map<Key, T, Compare, Allocator> {
  return { std::begin(map), std::end(map) };
}

}// namespace ftl

template<typename Iter, typename Key, typename T>
struct ftl::from_iterator_trait<ftl::enumerate_iterator<Iter>, ftl::map<Key, T>> {
  [[nodiscard]] constexpr static auto from_iter(const ftl::enumerate_iterator<Iter> &iter) -> ftl::map<Key, T> {
    ftl::map<Key, T> result{};

    for (auto &&item : iter) { result.emplace(std::get<0>(item), std::get<1>(item)); }

    return result;
  }
};

template<typename Key, typename T, typename Compare, typename Allocator>
struct ftl::into_iterator_trait<ftl::map<Key, T, Compare, Allocator>,
  typename ftl::map<Key, T, Compare, Allocator>::ftl_iterator> {
  using iterator = typename ftl::map<Key, T, Compare, Allocator>::ftl_iterator;

  [[nodiscard]] static auto into_iter(ftl::map<Key, T, Compare, Allocator> &map) -> iterator {
    return { map.begin(), map.end() };
  }
};

template<typename Key, typename T, typename Compare, typename Allocator>
struct ftl::into_iterator_trait<ftl::map<Key, T, Compare, Allocator>,
  typename ftl::map<Key, T, Compare, Allocator>::ftl_const_iterator> {
  using const_iterator = typename ftl::map<Key, T, Compare, Allocator>::ftl_const_iterator;

  [[nodiscard]] static auto into_iter(const ftl::map<Key, T, Compare, Allocator> &map) -> const_iterator {
    return { map.begin(), map.end() };
  }
};

template<typename Iter,
  class Key,
  class Item,
  class Compare,
  class Allocator>
struct ftl::from_iterator_trait<Iter, ftl::map<Key, Item, Compare, Allocator>> {
  [[nodiscard]] constexpr static auto from_iter(const Iter &iter) -> ftl::map<Key, Item, Compare, Allocator> {
    return ftl::map<Key, Item, Compare, Allocator>{ iter.begin(), iter.end() };
  }

  constexpr static auto from_iter_into_collection(const Iter &iter, ftl::map<Key, Item, Compare, Allocator> &collection)
    -> void {
    collection.insert(iter.begin(), iter.end());
  }
};

template<typename Iter, class Key, class Item, class Compare, class Allocator>
struct ftl::from_iterator_trait<Iter, std::map<Key, Item, Compare, Allocator>> {
  [[nodiscard]] constexpr static auto from_iter(const Iter &iter) -> std::map<Key, Item, Compare, Allocator> {
    return std::map<Key, Item, Compare, Allocator>{ iter.begin(), iter.end() };
  }

  constexpr static auto from_iter_into_collection(const Iter &iter, std::map<Key, Item, Compare, Allocator> &collection)
    -> void {
    collection.insert(iter.begin(), iter.end());
  }
};
