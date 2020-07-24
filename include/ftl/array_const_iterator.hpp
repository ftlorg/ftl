#pragma once

#include <ftl/iterator.hpp>

namespace ftl {

template<typename Item, std::size_t N>
class array_const_iterator final : public const_iterator_interface<array_const_iterator<Item, N>, Item, std::size_t> {

  friend const_iterator_interface<array_const_iterator<Item, N>, Item, std::size_t>;

public:
  using iterator_category = /* */ void;
  using value_type = typename std::remove_cv_t<Item>;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using size_type = std::size_t;

  constexpr array_const_iterator(const_pointer const begin, const_pointer const end)
    : position_{ 0 }, begin_{ begin }, end_{ end } {
  }

  constexpr array_const_iterator(size_type position, const_pointer const begin, const_pointer const end)
    : position_{ position }, begin_{ begin }, end_{ end } {
  }

private:
  [[nodiscard]] auto next_impl() const -> std::optional<value_type> {
    ++position_;

    if (begin_ + position_ != end_) { return { begin_[position_] }; }
    return std::nullopt;
  }

  template<typename Collection>
  [[nodiscard]] auto collect_impl() const -> Collection {
    return from_iterator_trait<array_const_iterator<Item, N>, Collection>::from_iter(*this);
  }

  template<typename Callable>
  [[nodiscard]] auto map_impl(Callable &&callable) const -> map_iterator<array_const_iterator<Item, N>, Callable> {
    return { array_const_iterator<Item, N>{ begin_, end_ }, std::forward<Callable>(callable) };
  }

  [[nodiscard]] constexpr auto count_impl() const -> size_type {
    return std::distance(cbegin_impl(), cend_impl());
  }

  [[nodiscard]] constexpr auto begin_impl() const noexcept -> array_const_iterator<Item, N> {
    return { 0, begin_, end_ };
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> array_const_iterator<Item, N> {
    return { 0, begin_, end_ };
  }

  [[nodiscard]] constexpr auto end_impl() const noexcept -> array_const_iterator<Item, N> {
    return { N, begin_, end_ };
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> array_const_iterator<Item, N> {
    return { N, begin_, end_ };
  }

  [[nodiscard]] constexpr auto deref_impl() const -> value_type {
    return begin_[position_];
  }

  auto preincrement_impl() const -> void {
    position_++;
  }

  [[nodiscard]] friend constexpr auto operator!=(const array_const_iterator<Item, N> &lhs,
    const array_const_iterator<Item, N> &rhs) -> bool {
    return lhs.position_ != rhs.position_;
  }

private:
  mutable size_type position_;
  const_pointer const begin_;
  const_pointer const end_;
};

}// namespace ftl
