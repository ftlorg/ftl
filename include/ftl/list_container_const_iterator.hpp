#pragma once

#include <ftl/iterator_interface.hpp>
#include <ftl/iterator_member_provider.hpp>
#include <ftl/map_iterator.hpp>
#include <list>

namespace ftl {

template<typename Item>
class list_container_const_iterator final
  : public const_iterator_interface<list_container_const_iterator<Item>, Item, std::size_t> {

  friend const_iterator_interface<list_container_const_iterator<Item>, Item, std::size_t>;
  friend iterator_member_provider<list_container_const_iterator<Item>, std::bidirectional_iterator_tag>;

public:
  using difference_type = typename std::iterator_traits<ftl::list_container_iterator<Item>>::difference_type;
  using value_type = typename std::iterator_traits<ftl::list_container_iterator<Item>>::value_type;
  using pointer = typename std::iterator_traits<ftl::list_container_iterator<Item>>::pointer;
  using reference = typename std::iterator_traits<ftl::list_container_iterator<Item>>::reference;
  using const_pointer = typename std::iterator_traits<ftl::list_container_iterator<Item>>::const_pointer;
  using const_reference = typename std::iterator_traits<ftl::list_container_iterator<Item>>::const_reference;
  using iterator_category = typename std::iterator_traits<ftl::list_container_iterator<Item>>::iterator_category;
  using size_type = typename std::iterator_traits<ftl::list_container_iterator<Item>>::size_type;
  using std_list_container_const_iterator = typename std::iterator_traits<ftl::list_container_iterator<Item>>::std_list_container_const_iterator;

  list_container_const_iterator(std_list_container_const_iterator begin, std_list_container_const_iterator end)
    : current_{ begin }, begin_{ begin }, end_{ end } {
  }

  list_container_const_iterator(std_list_container_const_iterator current,
    std_list_container_const_iterator begin,
    std_list_container_const_iterator end)
    : current_{ current }, begin_{ begin }, end_{ end } {
  }

  // private:
  [[nodiscard]] constexpr auto count_impl() const -> size_type {
    return static_cast<size_type>(std::distance(begin_, end_));
  }

  [[nodiscard]] constexpr auto begin_impl() const noexcept -> list_container_const_iterator<Item> {
    return { begin_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> list_container_const_iterator<Item> {
    return { begin_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto end_impl() const noexcept -> list_container_const_iterator<Item> {
    return { end_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> list_container_const_iterator<Item> {
    return { end_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto const_deref_impl() const -> const_reference {
    return *current_;
  }

  auto const_preincrement_impl() const -> const list_container_const_iterator<Item> & {
    ++current_;

    return *this;
  }

  [[nodiscard]] friend constexpr auto operator==(const list_container_const_iterator<Item> &lhs,
    const list_container_const_iterator<Item> &rhs) noexcept -> bool {
    return lhs.begin_ == rhs.begin_ && lhs.end_ == rhs.end_ && lhs.current_ == rhs.current_;
  }

  [[nodiscard]] friend constexpr auto operator!=(const list_container_const_iterator<Item> &lhs,
    const list_container_const_iterator<Item> &rhs) noexcept -> bool {
    return !(lhs == rhs);
  }

  mutable std_list_container_const_iterator current_;
  std_list_container_const_iterator begin_;
  std_list_container_const_iterator end_;
};

}// namespace ftl

