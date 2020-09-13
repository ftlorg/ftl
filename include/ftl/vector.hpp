#pragma once

#include <vector>
#include "vector_container_iterator.hpp"
#include "vector_container_const_iterator.hpp"

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
  using iterator = ftl::vector_container_iterator<T>;
  using const_iterator = ftl::vector_container_const_iterator<T>;

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


  [[nodiscard]] constexpr auto iter() noexcept -> iterator {
    return into_iterator_trait<ftl::vector<T, Allocator>, iterator>::into_iter(*this);
  }

  [[nodiscard]] constexpr auto iter() const noexcept -> const_iterator {
    return into_iterator_trait<ftl::vector<T, Allocator>, const_iterator>::into_iter(*this);
  }
};

template<typename T, typename Allocator = std::allocator<T>>
[[nodiscard]] constexpr auto to_vector(const std::vector<T> &vec) -> vector<T, Allocator> {
  return vector<T, Allocator>{ vec };
}

}// namespace ftl

template<typename Item, typename Allocator>
struct ftl::into_iterator_trait<ftl::vector<Item, Allocator>, ftl::vector_container_iterator<Item>> {
  using iterator = typename ftl::vector<Item, Allocator>::iterator;
  [[nodiscard]] constexpr static auto into_iter(ftl::vector<Item, Allocator> &vec) {
    return iterator{ vec.begin(), vec.end() };
  }
};

template<typename Item, typename Allocator>
struct ftl::into_iterator_trait<ftl::vector<Item, Allocator>, ftl::vector_container_const_iterator<Item>> {
  using const_iterator = typename ftl::vector<Item, Allocator>::const_iterator;
  [[nodiscard]] constexpr static auto into_iter(const ftl::vector<Item, Allocator> &vec) {
    return const_iterator{ vec.begin(), vec.end() };
  }
};