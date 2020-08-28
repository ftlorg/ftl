#pragma once

#include <ftl/iterator_interface.hpp>
#include <ftl/list_const_iterator.hpp>
#include <ftl/map_iterator.hpp>

#include <list>

namespace ftl {

template<typename Item>
class list_iterator final : public iterator_interface<list_iterator<Item>, Item, std::size_t> {

  friend iterator_interface<list_iterator<Item>, Item, std::size_t>;

public:
  using difference_type = std::ptrdiff_t;
  using value_type = std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::bidirectional_iterator_tag;
  using size_type = std::size_t;
  using std_list_iterator = typename std::list<value_type>::iterator;
  
  list_iterator(std_list_iterator begin, std_list_iterator end) : current_{ begin }, begin_{ begin }, end_{ end } {
  }

  auto operator++() -> list_iterator & {
    ++current_;

    return *this;
  }

  auto operator++(int) -> list_iterator {
    const auto it = *this;

    ++current_;

    return it;
  }

  auto operator--() -> list_iterator & {
    --current_;

    return *this;
  }


  auto operator--(int) -> list_iterator {
    const auto it = *this;

    --current_;

    return it;
  }

  operator list_const_iterator<Item>() {
    return { begin_, end_ };
  }

private:
  [[nodiscard]] auto next_impl() -> std::optional<value_type> {
    if (++current_ != end_) { return { *current_ }; }

    return std::nullopt;
  }

  template<typename Collection>
  [[nodiscard]] auto collect_impl() -> Collection {
    return from_iterator_trait<list_iterator<Item>, Collection>::from_iter(*this);
  }

  [[nodiscard]] auto enumerate_impl() const -> enumerate_iterator<list_iterator<Item>> {
    return { *this };
  }

  template<typename Callable>
  [[nodiscard]] auto map_impl(Callable &&callable) -> map_iterator<list_iterator<Item>, Callable> {
    return { *this, std::forward<Callable>(callable) };
  }

  [[nodiscard]] constexpr auto count_impl() const -> size_type {
    return static_cast<size_type>(end_ - begin_);
  }

  [[nodiscard]] constexpr auto begin_impl() noexcept -> list_iterator<Item> {
    return { begin_, end_ };
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> list_iterator<Item> {
    return { begin_, end_ };
  }

  [[nodiscard]] constexpr auto end_impl() noexcept -> list_iterator<Item> {
    return { end_, end_ };
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> list_iterator<Item> {
    return { end_, end_ };
  }

  [[nodiscard]] constexpr auto deref_impl() -> reference {
    return *current_;
  }

  [[nodiscard]] constexpr auto const_deref_impl() const -> const_reference {
    return *current_;
  }

  auto preincrement_impl() const -> list_iterator & {
    ++current_;

    return *this;
  }

  [[nodiscard]] friend constexpr auto operator==(const list_iterator<Item> &lhs, const list_iterator<Item> &rhs) noexcept
    -> bool {
    return lhs.begin_ == rhs.begin_ && lhs.end_ == rhs.end_ && lhs.current_ == rhs.current_;
  }

  [[nodiscard]] friend constexpr auto operator!=(const list_iterator<Item> &lhs, const list_iterator<Item> &rhs) noexcept
    -> bool {
    return !(lhs == rhs);
  }

  mutable std_list_iterator current_;
  std_list_iterator begin_;
  std_list_iterator end_;
};

}// namespace ftl

template<typename Item>
struct std::iterator_traits<ftl::list_iterator<Item>> {
  using difference_type = typename ftl::list_iterator<Item>::difference_type;
  using value_type = typename ftl::list_iterator<Item>::value_type;
  using pointer = typename ftl::list_iterator<Item>::pointer;
  using reference = typename ftl::list_iterator<Item>::reference;
  using iterator_category = typename ftl::list_iterator<Item>::iterator_category;
};
