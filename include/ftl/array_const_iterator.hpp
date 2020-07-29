#pragma once

#include <ftl/iterator.hpp>

namespace ftl {

template<typename Item, std::size_t N>
class array_const_iterator final : public const_iterator_interface<array_const_iterator<Item, N>, Item, std::size_t> {

  friend const_iterator_interface<array_const_iterator<Item, N>, Item, std::size_t>;

public:
  using difference_type = std::ptrdiff_t;
  using value_type = typename std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::random_access_iterator_tag;
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
    // TODO: Use std::distance once we make this iterator compatible with STL
    return static_cast<size_type>(end_ - begin_);
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

  [[nodiscard]] constexpr auto const_deref_impl() const -> const_reference {
    return begin_[position_];
  }

  auto preincrement_impl() const -> void {
    position_++;
  }

  [[nodiscard]] constexpr auto operator[](size_type pos) noexcept -> reference {
    return begin_[pos];
  }

  [[nodiscard]] constexpr auto operator[](size_type pos) const noexcept -> const_reference {
    return begin_[pos];
  }

  [[nodiscard]] friend constexpr auto operator+=(const array_const_iterator<Item, N> &lhs, size_type n)
    -> array_const_iterator<Item, N> & {
    lhs.position_ += n;
    return lhs;
  }

  [[nodiscard]] friend constexpr auto operator+(const array_const_iterator<Item, N> &lhs, size_type n)
    -> array_const_iterator<Item, N> {
    return lhs += n;
  }

  [[nodiscard]] friend constexpr auto operator+(size_type n, const array_const_iterator<Item, N> &rhs)
    -> array_const_iterator<Item, N> {
    return rhs += n;
  }

  [[nodiscard]] friend constexpr auto operator-=(const array_const_iterator<Item, N> &lhs, size_type n)
    -> array_const_iterator<Item, N> & {
    return lhs += -n;
  }

  [[nodiscard]] friend constexpr auto operator-(const array_const_iterator<Item, N> &lhs, size_type n)
    -> array_const_iterator<Item, N> {
    return lhs -= n;
  }

  [[nodiscard]] friend constexpr auto operator-(const array_const_iterator<Item, N> &lhs,
    const array_const_iterator<Item, N> &rhs) -> difference_type {
    return std::distance(rhs.begin_ + rhs.position_, lhs.begin_ + lhs.position_);
  }

  [[nodiscard]] friend constexpr auto operator==(const array_const_iterator<Item, N> &lhs,
    const array_const_iterator<Item, N> &rhs) noexcept -> bool {
    return lhs.begin_ == rhs.begin_ && lhs.end_ == rhs.end_ && lhs.position_ == rhs.position_;
  }

  [[nodiscard]] friend constexpr auto operator!=(const array_const_iterator<Item, N> &lhs,
    const array_const_iterator<Item, N> &rhs) noexcept -> bool {
    return !(lhs == rhs);
  }

  [[nodiscard]] friend constexpr auto operator<(const array_const_iterator<Item, N> &lhs,
    const array_const_iterator<Item, N> &rhs) noexcept -> bool {
    return rhs - lhs > 0;
  }

  [[nodiscard]] friend constexpr auto operator<=(const array_const_iterator &lhs, const array_const_iterator &rhs) noexcept
    -> bool {
    return !(rhs < lhs);
  }


  [[nodiscard]] friend constexpr auto operator>(const array_const_iterator &lhs, const array_const_iterator &rhs) noexcept
    -> bool {
    return rhs < lhs;
  }

  [[nodiscard]] friend constexpr auto operator>=(const array_const_iterator &lhs, const array_const_iterator &rhs) noexcept
    -> bool {
    return !(lhs < rhs);
  }

private:
  mutable size_type position_;
  const_pointer const begin_;
  const_pointer const end_;
};

}// namespace ftl

template<typename Item, std::size_t N>
struct std::iterator_traits<ftl::array_const_iterator<Item, N>> {
  using difference_type = typename ftl::array_const_iterator<Item, N>::difference_type;
  using value_type = typename ftl::array_const_iterator<Item, N>::value_type;
  using pointer = typename ftl::array_const_iterator<Item, N>::pointer;
  using reference = typename ftl::array_const_iterator<Item, N>::reference;
  using iterator_category = typename ftl::array_const_iterator<Item, N>::iterator_category;
};
