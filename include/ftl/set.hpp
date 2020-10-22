
// Copyright Grzegorz Litarowicz and Lukasz Gut 2020 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <set>
#include <ftl/set_container_iterator.hpp>
#include <ftl/set_container_const_iterator.hpp>
#include <ftl/into_iterator_trait.hpp>

namespace ftl {
template<class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key>>
class set final : public std::set<Key, Compare, Allocator> {
public:
  using value_type = typename std::set<Key, Compare, Allocator>::value_type;
  using size_type = typename std::set<Key, Compare, Allocator>::size_type;
  using difference_type = typename std::set<Key, Compare, Allocator>::difference_type;
  using pointer = typename std::set<Key, Compare, Allocator>::pointer;
  using reference = typename std::set<Key, Compare, Allocator>::reference;
  using const_pointer = typename std::set<Key, Compare, Allocator>::const_pointer;
  using const_reference = typename std::set<Key, Compare, Allocator>::const_reference;
  using ftl_iterator = set_container_iterator<Key>;
  using ftl_const_iterator = set_container_const_iterator<Key>;
  using iterator = typename std::set<Key, Compare, Allocator>::iterator;
  using const_iterator = typename std::set<Key, Compare, Allocator>::const_iterator;
  using reverse_iterator = typename std::set<Key, Compare, Allocator>::reverse_iterator;
  using const_reverse_iterator = typename std::set<Key, Compare, Allocator>::const_reverse_iterator;

  using std::set<Key, Compare, Allocator>::set;

  [[nodiscard]] auto iter() noexcept -> ftl_iterator {
    return into_iterator_trait<set<Key, Compare, Allocator>, ftl_iterator>::into_iter(*this);
  }

  [[nodiscard]] auto iter() const noexcept -> ftl_const_iterator {
    return into_iterator_trait<set<Key, Compare, Allocator>, ftl_const_iterator>::into_iter(*this);
  }
};
}// namespace ftl

template<class Key, class Compare, class Allocator>
struct ftl::into_iterator_trait<ftl::set<Key, Compare, Allocator>,
  typename ftl::set<Key, Compare, Allocator>::ftl_iterator> {
  using iterator = typename ftl::set<Key, Compare, Allocator>::ftl_iterator;

  [[nodiscard]] static auto into_iter(ftl::set<Key, Compare, Allocator> &set) -> iterator {
    return { set.begin(), set.end() };
  }
};

template<class Key, class Compare, class Allocator>
struct ftl::into_iterator_trait<ftl::set<Key, Compare, Allocator>,
  typename ftl::set<Key, Compare, Allocator>::ftl_const_iterator> {
  using iterator = typename ftl::set<Key, Compare, Allocator>::ftl_const_iterator;

  [[nodiscard]] static auto into_iter(const ftl::set<Key, Compare, Allocator> &set) -> iterator {
    return { set.begin(), set.end() };
  }
};

template<typename Iter, class Key, class Compare, class Allocator> 
struct ftl::from_iterator_trait<Iter, ftl::set<Key, Compare, Allocator>> {
  [[nodiscard]] constexpr static auto from_iter(const Iter &iter) -> ftl::set<Key, Compare, Allocator> {
    return ftl::set<Key, Compare, Allocator>{ iter.begin(), iter.end() };
  }

  constexpr static auto from_iter_into_collection(const Iter &iter, ftl::set<Key, Compare, Allocator> &collection)
    -> void {
    collection.insert(iter.begin(), iter.end());
  }
};

template<typename Iter, class Key, class Compare, class Allocator>
struct ftl::from_iterator_trait<Iter, std::set<Key, Compare, Allocator>> {
  [[nodiscard]] constexpr static auto from_iter(const Iter &iter) -> std::set<Key, Compare, Allocator> {
    return std::set<Key, Compare, Allocator>{ iter.begin(), iter.end() };
  }

  constexpr static auto from_iter_into_collection(const Iter &iter, std::set<Key, Compare, Allocator> &collection)
    -> void {
    collection.insert(iter.begin(), iter.end());
  }
};