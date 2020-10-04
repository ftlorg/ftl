#pragma once

#include <set>
#include <ftl/set_container_iterator.hpp>
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
  // using ftl_const_iterator = set_container_const_iterator<T, N>;
  using iterator = typename std::set<Key, Compare, Allocator>::iterator;
  using const_iterator = typename std::set<Key, Compare, Allocator>::const_iterator;
  using reverse_iterator = typename std::set<Key, Compare, Allocator>::reverse_iterator;
  using const_reverse_iterator = typename std::set<Key, Compare, Allocator>::const_reverse_iterator;

  [[nodiscard]] auto iter() noexcept -> ftl_iterator {
    return into_iterator_trait<set<Key, Compare, Allocator>, ftl_iterator>::into_iter(*this);
  }

  //[[nodiscard]] auto iter() const noexcept -> ftl_const_iterator {
  //  return into_iterator_trait<array<T, N>, ftl_const_iterator>::into_iter(*this);
  //}
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