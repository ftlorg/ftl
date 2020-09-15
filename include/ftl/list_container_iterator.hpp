#pragma once

#include <ftl/iterator_interface.hpp>
#include <ftl/iterator_member_provider.hpp>
#include <ftl/map_iterator.hpp>
#include <list>

namespace ftl {

template<typename Item>
class list_container_iterator final : public iterator_interface<list_container_iterator<Item>, Item, std::size_t> {

public:
  using value_type = std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::bidirectional_iterator_tag;
  using size_type = std::size_t;
  using std_list_container_iterator = typename std::list<value_type>::iterator;
  using difference_type = typename std_list_container_iterator::difference_type;

  list_container_iterator(std_list_container_iterator begin, std_list_container_iterator end)
    : current_{ begin }, begin_{ begin }, end_{ end } {
  }

  list_container_iterator(std_list_container_iterator current,
    std_list_container_iterator begin,
    std_list_container_iterator end)
    : current_{ current }, begin_{ begin }, end_{ end } {
  }

  // private:
  [[nodiscard]] constexpr auto count_impl() const -> size_type {
    return static_cast<size_type>(std::distance(begin_, end_));
  }

  [[nodiscard]] constexpr auto begin_impl() noexcept -> list_container_iterator<Item> {
    return { begin_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto begin_impl() const noexcept -> list_container_iterator<Item> {
    return cbegin_impl();
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> list_container_iterator<Item> {
    return { begin_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto end_impl() noexcept -> list_container_iterator<Item> {
    return { end_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto end_impl() const noexcept -> list_container_iterator<Item> {
    return cend_impl();
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> list_container_iterator<Item> {
    return { end_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto deref_impl() -> reference {
    return *current_;
  }

  [[nodiscard]] constexpr auto const_deref_impl() const -> const_reference {
    return *current_;
  }

  auto preincrement_impl() -> list_container_iterator<Item> & {
    ++current_;

    return *this;
  }

  auto const_preincrement_impl() const -> const list_container_iterator<Item> & {
    ++current_;

    return *this;
  }

  [[nodiscard]] friend constexpr auto operator==(const list_container_iterator<Item> &lhs,
    const list_container_iterator<Item> &rhs) noexcept -> bool {
    return lhs.begin_ == rhs.begin_ && lhs.end_ == rhs.end_ && lhs.current_ == rhs.current_;
  }

  [[nodiscard]] friend constexpr auto operator!=(const list_container_iterator<Item> &lhs,
    const list_container_iterator<Item> &rhs) noexcept -> bool {
    return !(lhs == rhs);
  }

  mutable std_list_container_iterator current_;
  std_list_container_iterator begin_;
  std_list_container_iterator end_;
};

}// namespace ftl

template<typename Item>
struct std::iterator_traits<ftl::list_container_iterator<Item>> {
  using difference_type = typename ftl::list_container_iterator<Item>::difference_type;
  using value_type = typename ftl::list_container_iterator<Item>::value_type;
  using pointer = typename ftl::list_container_iterator<Item>::pointer;
  using reference = typename ftl::list_container_iterator<Item>::reference;
  using iterator_category = typename ftl::list_container_iterator<Item>::iterator_category;
};
