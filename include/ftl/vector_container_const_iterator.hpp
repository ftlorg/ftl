#pragma once

#include <iterator>
#include <ftl/iterator_interface.hpp>
#include <ftl/filter_iterator.hpp>

namespace ftl {

template<typename Item>
class vector_container_const_iterator final
  : public const_iterator_interface<vector_container_const_iterator<Item>, Item, std::size_t> {

  friend const_iterator_interface<vector_container_const_iterator<Item>, Item, std::size_t>;

public:
  using difference_type = std::ptrdiff_t;
  using value_type = typename std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::random_access_iterator_tag;
  using size_type = std::size_t;
  using std_vector_iterator = typename std::vector<value_type>::const_iterator;

  constexpr vector_container_const_iterator() = default;
  constexpr vector_container_const_iterator(std_vector_iterator begin, std_vector_iterator end)
    : current_{ begin }, begin_{ std::move(begin) }, end_{ std::move(end) } {
  }

private:
  template<typename Collection>
  [[nodiscard]] auto collect_impl() const -> Collection {
    return from_iterator_trait<vector_container_const_iterator<Item>, Collection>::from_iter(*this);
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> vector_container_const_iterator<Item> {
    return { begin_, end_ };
  }

  [[nodiscard]] constexpr auto begin_impl() const noexcept -> vector_container_const_iterator<Item> {
    return { begin_, end_ };
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> vector_container_const_iterator<Item> {
    return { end_, end_ };
  }

  [[nodiscard]] constexpr auto end_impl() const noexcept -> vector_container_const_iterator<Item> {
    return { end_, end_ };
  }

  [[nodiscard]] constexpr auto deref_impl() -> reference {
    return *current_;
  }

  [[nodiscard]] constexpr auto const_deref_impl() const -> const_reference {
    return *current_;
  }

  auto preincrement_impl() const -> const vector_container_const_iterator<Item> & {
    ++current_;
    return *this;
  }

  auto predecrement_impl() const -> const vector_container_const_iterator<Item> & {
    --current_;
    return *this;
  }

  [[nodiscard]] constexpr auto count_impl() const -> size_type {
    return static_cast<size_type>(end_ - begin_);
  }

  template<typename Callable>
  [[nodiscard]] auto map_impl(Callable &&callable) const -> map_iterator<vector_container_const_iterator<Item>, Callable> {
    return { *this, std::forward<Callable>(callable) };
  }

  template<typename Callable>
  [[nodiscard]] auto filter_impl(Callable &&callable) const
    -> filter_iterator<vector_container_const_iterator<Item>, Callable> {
    return { *this, std::forward<Callable>(callable) };
  }

  [[nodiscard]] friend constexpr auto operator==(const vector_container_const_iterator<Item> &lhs,
    const vector_container_const_iterator<Item> &rhs) noexcept -> bool {
    return rhs.current_ == lhs.current_;
  }

  [[nodiscard]] constexpr auto operator[](size_type pos) noexcept -> reference {
    return begin_[pos];
  }

  [[nodiscard]] constexpr auto operator[](size_type pos) const noexcept -> const_reference {
    return begin_[pos];
  }

  [[nodiscard]] friend constexpr auto operator+=(const vector_container_const_iterator<Item> &lhs, size_type n)
    -> const vector_container_const_iterator<Item> & {
    lhs.current_ += n;
    return lhs;
  }

  [[nodiscard]] friend constexpr auto operator+(const vector_container_const_iterator<Item> &lhs, size_type n)
    -> vector_container_const_iterator<Item> {
    return lhs += n;
  }

  [[nodiscard]] friend constexpr auto operator+(size_type n, const vector_container_const_iterator<Item> &rhs)
    -> vector_container_const_iterator<Item> {
    return rhs += n;
  }

  [[nodiscard]] friend constexpr auto operator-=(const vector_container_const_iterator<Item> &lhs, size_type n)
    -> vector_container_const_iterator<Item> & {
    return lhs += -n;
  }

  [[nodiscard]] friend constexpr auto operator-(const vector_container_const_iterator<Item> &lhs, size_type n)
    -> vector_container_const_iterator<Item> {
    return lhs -= n;
  }

  [[nodiscard]] friend constexpr auto operator-(const vector_container_const_iterator<Item> &lhs,
    const vector_container_const_iterator<Item> &rhs) -> difference_type {
    return std::distance(rhs.current_, lhs.current_);
  }

  [[nodiscard]] friend constexpr auto operator!=(const vector_container_const_iterator<Item> &lhs,
    const vector_container_const_iterator<Item> &rhs) noexcept -> bool {
    return !(lhs == rhs);
  }

  [[nodiscard]] friend constexpr auto operator<(const vector_container_const_iterator<Item> &lhs,
    const vector_container_const_iterator<Item> &rhs) noexcept -> bool {
    return rhs - lhs > 0;
  }

  [[nodiscard]] friend constexpr auto operator<=(const vector_container_const_iterator<Item> &lhs,
    const vector_container_const_iterator<Item> &rhs) noexcept -> bool {
    return !(rhs < lhs);
  }

  [[nodiscard]] friend constexpr auto operator>(const vector_container_const_iterator<Item> &lhs,
    const vector_container_const_iterator<Item> &rhs) noexcept -> bool {
    return rhs < lhs;
  }

  [[nodiscard]] friend constexpr auto operator>=(const vector_container_const_iterator<Item> &lhs,
    const vector_container_const_iterator<Item> &rhs) noexcept -> bool {
    return !(lhs < rhs);
  }

private:
  mutable std_vector_iterator current_{};
  std_vector_iterator begin_{};
  std_vector_iterator end_{};
};

}// namespace ftl

template<typename Item>
struct std::iterator_traits<ftl::vector_container_const_iterator<Item>> {
  using difference_type = typename ftl::vector_container_const_iterator<Item>::difference_type;
  using value_type = typename ftl::vector_container_const_iterator<Item>::value_type;
  using pointer = typename ftl::vector_container_const_iterator<Item>::pointer;
  using reference = typename ftl::vector_container_const_iterator<Item>::reference;
  using iterator_category = typename ftl::vector_container_const_iterator<Item>::iterator_category;
};