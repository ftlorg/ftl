
// Copyright Grzegorz Litarowicz and Lukasz Gut 2020 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <vector>
#include <ftl/vector_container_iterator.hpp>
#include <ftl/vector_container_const_iterator.hpp>

namespace ftl {
template<typename T, typename Allocator = std::allocator<T>>
class vector : public std::vector<T, Allocator> {
public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using allocator_type = Allocator;
  using ftl_iterator = ftl::vector_container_iterator<T>;
  using ftl_const_iterator = ftl::vector_container_const_iterator<T>;

  vector() = default;

  vector(size_type size) : std::vector<T, Allocator>(size) {
  }

  vector(std::vector<T> vec) : std::vector<T, Allocator>(std::move(vec)) {
  }

  vector(std::initializer_list<T> list) : std::vector<T, Allocator>(std::move(list)) {
  }

  template<typename Iter>
  vector(Iter begin, Iter end) : std::vector<T, Allocator>{ begin, end } {
  }


  [[nodiscard]] constexpr auto iter() noexcept -> ftl_iterator {
    return into_iterator_trait<ftl::vector<T, Allocator>, ftl_iterator>::into_iter(*this);
  }

  [[nodiscard]] constexpr auto iter() const noexcept -> ftl_const_iterator {
    return into_iterator_trait<ftl::vector<T, Allocator>, ftl_const_iterator>::into_iter(*this);
  }
};

template<typename T, typename Allocator = std::allocator<T>>
[[nodiscard]] constexpr auto to_vector(const std::vector<T> &vec) -> vector<T, Allocator> {
  return vector<T, Allocator>{ vec };
}

}// namespace ftl

template<typename Item, typename Allocator>
struct ftl::into_iterator_trait<ftl::vector<Item, Allocator>, ftl::vector_container_iterator<Item>> {
  using ftl_iterator = typename ftl::vector<Item, Allocator>::ftl_iterator;
  [[nodiscard]] constexpr static auto into_iter(ftl::vector<Item, Allocator> &vec) {
    return ftl_iterator{ vec.begin(), vec.begin(), vec.end() };
  }
};

template<typename Item, typename Allocator>
struct ftl::into_iterator_trait<ftl::vector<Item, Allocator>, ftl::vector_container_const_iterator<Item>> {
  using ftl_const_iterator = typename ftl::vector<Item, Allocator>::ftl_const_iterator;
  [[nodiscard]] constexpr static auto into_iter(const ftl::vector<Item, Allocator> &vec) { return ftl_const_iterator{ vec.begin(), vec.begin(), vec.end() } ;
  }
};