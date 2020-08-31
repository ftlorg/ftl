#pragma once

#include <list>

#include <ftl/list_iterator.hpp>
#include <ftl/list_const_iterator.hpp>
#include <ftl/into_iterator_trait.hpp>

namespace ftl {

template<typename T, typename Allocator = std::allocator<T>>
class list : public std::list<T, Allocator> {
public:
  using value_type = typename std::list<T, Allocator>::value_type;
  using allocator_type = typename std::list<T, Allocator>::allocator_type;
  using size_type = typename std::list<T, Allocator>::size_type;
  using difference_type = typename std::list<T, Allocator>::difference_type;
  using pointer = typename std::list<T, Allocator>::pointer;
  using reference = typename std::list<T, Allocator>::reference;
  using const_pointer = typename std::list<T, Allocator>::const_pointer;
  using const_reference = typename std::list<T, Allocator>::const_reference;
  using ftl_iterator = list_iterator<T>;
  using ftl_const_iterator = list_const_iterator<T>;
  using iterator = typename std::list<T, Allocator>::iterator;
  using const_iterator = typename std::list<T, Allocator>::const_iterator;
  using reverse_iterator = typename std::list<T, Allocator>::reverse_iterator;
  using const_reverse_iterator = typename std::list<T, Allocator>::const_reverse_iterator;

  using std::list<T, Allocator>::list;

  [[nodiscard]] auto iter() noexcept -> ftl_iterator {
    return into_iterator_trait<list<T, Allocator>, ftl_iterator>::into_iter(*this);
  }

  [[nodiscard]] auto iter() const noexcept -> ftl_const_iterator {
    return into_iterator_trait<list<T, Allocator>, ftl_const_iterator>::into_iter(*this);
  }
};

}// namespace ftl

template<typename Item, typename Allocator>
struct ftl::into_iterator_trait<ftl::list<Item, Allocator>, typename ftl::list<Item, Allocator>::ftl_iterator> {
  using iterator = typename ftl::list<Item, Allocator>::ftl_iterator;

  [[nodiscard]] static auto into_iter(ftl::list<Item, Allocator> &list) -> iterator {
    return { list.begin(), list.end() };
  }
};

template<typename Item, typename Allocator>
struct ftl::into_iterator_trait<ftl::list<Item, Allocator>, typename ftl::list<Item, Allocator>::ftl_const_iterator> {
  using const_iterator = typename ftl::list<Item, Allocator>::ftl_const_iterator;

  [[nodiscard]] static auto into_iter(const ftl::list<Item, Allocator> &list) -> const_iterator {
    return { list.begin(), list.end() };
  }
};
