
// Copyright Grzegorz Litarowicz and Lukasz Gut 2020 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <deque>
#include <ftl/deque_container_iterator.hpp>
#include <ftl/deque_container_const_iterator.hpp>
#include <ftl/into_iterator_trait.hpp>

namespace ftl {

template<typename T, typename Allocator = std::allocator<T>>
class deque : public std::deque<T, Allocator> {
public:
  using value_type = typename std::deque<T, Allocator>::value_type;
  using allocator_type = typename std::deque<T, Allocator>::allocator_type;
  using size_type = typename std::deque<T, Allocator>::size_type;
  using difference_type = typename std::deque<T, Allocator>::difference_type;
  using pointer = typename std::deque<T, Allocator>::pointer;
  using reference = typename std::deque<T, Allocator>::reference;
  using const_pointer = typename std::deque<T, Allocator>::const_pointer;
  using const_reference = typename std::deque<T, Allocator>::const_reference;
  using ftl_iterator = deque_container_iterator<T>;
  using ftl_const_iterator = deque_container_const_iterator<T>;
  using iterator = typename std::deque<T, Allocator>::iterator;
  using const_iterator = typename std::deque<T, Allocator>::const_iterator;
  using reverse_iterator = typename std::deque<T, Allocator>::reverse_iterator;
  using const_reverse_iterator = typename std::deque<T, Allocator>::const_reverse_iterator;

  using std::deque<T, Allocator>::deque;

  deque(std::deque<T> deq) : std::deque<T, Allocator>(std::move(deq)) {
  }

  [[nodiscard]] constexpr auto iter() noexcept -> ftl_iterator {
    return into_iterator_trait<ftl::deque<T, Allocator>, ftl_iterator>::into_iter(*this);
  }

  [[nodiscard]] constexpr auto iter() const noexcept -> ftl_const_iterator {
    return into_iterator_trait<ftl::deque<T, Allocator>, ftl_const_iterator>::into_iter(*this);
  }
};

template<typename T, typename Allocator = std::allocator<T>>
[[nodiscard]] constexpr auto to_deque(const std::deque<T> &deq) -> deque<T, Allocator> {
  return deque<T, Allocator>{ deq };
}

}// namespace ftl

template<typename T, typename Allocator>
struct ftl::into_iterator_trait<ftl::deque<T, Allocator>, typename ftl::deque<T, Allocator>::ftl_iterator> {
  using iterator = typename ftl::deque<T, Allocator>::ftl_iterator;

  [[nodiscard]] static auto into_iter(ftl::deque<T, Allocator> &deq) -> iterator {
    return { deq.begin(), deq.end() };
  }
};

template<typename T, typename Allocator>
struct ftl::into_iterator_trait<ftl::deque<T, Allocator>, typename ftl::deque<T, Allocator>::ftl_const_iterator> {
  using const_iterator = typename ftl::deque<T, Allocator>::ftl_const_iterator;

  [[nodiscard]] static auto into_iter(const ftl::deque<T, Allocator> &deq) -> const_iterator {
    return { deq.begin(), deq.end() };
  }
};
