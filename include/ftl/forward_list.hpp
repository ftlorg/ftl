
// Copyright Grzegorz Litarowicz and £ukasz Gut 2020 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <forward_list>

#include <ftl/forward_list_container_iterator.hpp>
#include <ftl/forward_list_container_const_iterator.hpp>
#include <ftl/into_iterator_trait.hpp>

namespace ftl {

template<typename T, typename Allocator = std::allocator<T>>
class forward_list : public std::forward_list<T, Allocator> {
public:
  using value_type = typename std::forward_list<T, Allocator>::value_type;
  using allocator_type = typename std::forward_list<T, Allocator>::allocator_type;
  using size_type = typename std::forward_list<T, Allocator>::size_type;
  using difference_type = typename std::forward_list<T, Allocator>::difference_type;
  using pointer = typename std::forward_list<T, Allocator>::pointer;
  using reference = typename std::forward_list<T, Allocator>::reference;
  using const_pointer = typename std::forward_list<T, Allocator>::const_pointer;
  using const_reference = typename std::forward_list<T, Allocator>::const_reference;
  using ftl_iterator = forward_list_container_iterator<T>;
  using ftl_const_iterator = forward_list_container_const_iterator<T>;
  using iterator = typename std::forward_list<T, Allocator>::iterator;
  using const_iterator = typename std::forward_list<T, Allocator>::const_iterator;

  using std::forward_list<T, Allocator>::forward_list;

  [[nodiscard]] auto iter() noexcept -> ftl_iterator {
    return into_iterator_trait<forward_list<T, Allocator>, ftl_iterator>::into_iter(*this);
  }

  [[nodiscard]] auto iter() const noexcept -> ftl_const_iterator {
    return into_iterator_trait<forward_list<T, Allocator>, ftl_const_iterator>::into_iter(*this);
  }
};

template<typename T, typename Allocator = std::allocator<T>>
[[nodiscard]] constexpr auto to_forward_list(const std::forward_list<T, Allocator> &forward_list)
  -> ftl::forward_list<T, Allocator> {
  return { std::begin(forward_list), std::end(forward_list) };
}

}// namespace ftl

template<typename Item, typename Allocator>
struct ftl::into_iterator_trait<ftl::forward_list<Item, Allocator>,
  typename ftl::forward_list<Item, Allocator>::ftl_iterator> {
  using iterator = typename ftl::forward_list<Item, Allocator>::ftl_iterator;

  [[nodiscard]] static auto into_iter(ftl::forward_list<Item, Allocator> &forward_list) -> iterator {
    return { forward_list.begin(), forward_list.end() };
  }
};

template<typename Item, typename Allocator>
struct ftl::into_iterator_trait<ftl::forward_list<Item, Allocator>,
  typename ftl::forward_list<Item, Allocator>::ftl_const_iterator> {
  using const_iterator = typename ftl::forward_list<Item, Allocator>::ftl_const_iterator;

  [[nodiscard]] static auto into_iter(const ftl::forward_list<Item, Allocator> &forward_list) -> const_iterator {
    return { forward_list.begin(), forward_list.end() };
  }
};
