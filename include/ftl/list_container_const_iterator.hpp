#pragma once

#include <ftl/iterator_interface.hpp>
#include <ftl/map_iterator.hpp>
#include <list>

namespace ftl {

template<typename Item>
class list_container_const_iterator final : public const_iterator_interface<list_container_const_iterator<Item>, Item, std::size_t> {

  friend const_iterator_interface<list_container_const_iterator<Item>, Item, std::size_t>;

public:
  using difference_type = std::ptrdiff_t;
  using value_type = std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::bidirectional_iterator_tag;
  using size_type = std::size_t;
  using std_list_iterator = typename std::list<value_type>::const_iterator;

  list_container_const_iterator(std_list_iterator begin, std_list_iterator end) : current_{ begin }, begin_{ begin }, end_{ end } {
  }

  list_container_const_iterator(std_list_iterator current, std_list_iterator begin, std_list_iterator end)
    : current_{ current }, begin_{ begin }, end_{ end } {
  }

private:
  template<typename Collection>
  [[nodiscard]] auto collect_impl() const -> Collection {
    return from_iterator_trait<list_container_const_iterator<Item>, Collection>::from_iter(*this);
  }

  [[nodiscard]] auto enumerate_impl() const -> enumerate_iterator<list_container_const_iterator<Item>> {
    return { *this };
  }

  template<typename NewCallable>
  [[nodiscard]] auto inspect_impl(NewCallable &&callable) const -> inspect_iterator<list_container_const_iterator<Item>, NewCallable> {
    return { *this, std::forward<NewCallable>(callable) };
  }

  template<typename Callable>
  [[nodiscard]] auto map_impl(Callable &&callable) const -> map_iterator<list_container_const_iterator<Item>, Callable> {
    return { *this, std::forward<Callable>(callable) };
  }

  template<typename Callable>
  [[nodiscard]] auto filter_impl(Callable &&callable) const -> filter_iterator<list_container_const_iterator<Item>, Callable> {
    return { *this, std::forward<Callable>(callable) };
  }

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

  auto preincrement_impl() const -> const list_container_const_iterator<Item> & {
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

private:
  mutable std_list_iterator current_;
  std_list_iterator begin_;
  std_list_iterator end_;
};

}// namespace ftl

template<typename Item>
struct std::iterator_traits<ftl::list_container_const_iterator<Item>> {
  using difference_type = typename ftl::list_container_const_iterator<Item>::difference_type;
  using value_type = typename ftl::list_container_const_iterator<Item>::value_type;
  using pointer = typename ftl::list_container_const_iterator<Item>::pointer;
  using reference = typename ftl::list_container_const_iterator<Item>::reference;
  using iterator_category = typename ftl::list_container_const_iterator<Item>::iterator_category;
};
