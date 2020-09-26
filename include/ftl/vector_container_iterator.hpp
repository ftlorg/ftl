#pragma once

#include <ftl/iterator_interface.hpp>
#include <ftl/iterator_member_provider.hpp>
#include <ftl/iterator_traits.hpp>

namespace ftl {

template<typename Item>
class vector_container_iterator final : public iterator_interface<vector_container_iterator<Item>, Item, std::size_t> {
public:
  using difference_type = typename std::iterator_traits<ftl::vector_container_iterator<Item>>::difference_type;
  using value_type = typename std::iterator_traits<ftl::vector_container_iterator<Item>>::value_type;
  using pointer = typename std::iterator_traits<ftl::vector_container_iterator<Item>>::pointer;
  using reference = typename std::iterator_traits<ftl::vector_container_iterator<Item>>::reference;
  using const_pointer = typename std::iterator_traits<ftl::vector_container_iterator<Item>>::const_pointer;
  using const_reference = typename std::iterator_traits<ftl::vector_container_iterator<Item>>::const_reference;
  using iterator_category = typename std::iterator_traits<ftl::vector_container_iterator<Item>>::iterator_category;
  using size_type = typename std::iterator_traits<ftl::vector_container_iterator<Item>>::size_type;
  using std_vector_container_iterator = typename std::iterator_traits<ftl::vector_container_iterator<Item>>::std_vector_container_iterator;

  constexpr vector_container_iterator(std_vector_container_iterator begin, std_vector_container_iterator end)
    : current_{ begin }, begin_{ std::move(begin) }, end_{ std::move(end) } {
  }

  // private:
  [[nodiscard]] constexpr auto count_impl() const -> size_type {
    return static_cast<size_type>(end_ - begin_);
  }

  [[nodiscard]] constexpr auto begin_impl() noexcept -> vector_container_iterator<Item> {
    return { begin_, end_ };
  }

  [[nodiscard]] constexpr auto begin_impl() const noexcept -> vector_container_iterator<Item> {
    return cbegin_impl();
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> vector_container_iterator<Item> {
    return { begin_, end_ };
  }

  [[nodiscard]] constexpr auto end_impl() noexcept -> vector_container_iterator<Item> {
    return { end_, end_ };
  }

  [[nodiscard]] constexpr auto end_impl() const noexcept -> vector_container_iterator<Item> {
    return cend_impl();
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> vector_container_iterator<Item> {
    return { end_, end_ };
  }

  [[nodiscard]] constexpr auto deref_impl() -> reference {
    return *current_;
  }

  [[nodiscard]] constexpr auto const_deref_impl() const -> const_reference {
    return *current_;
  }

  auto preincrement_impl() -> vector_container_iterator<Item> & {
    ++current_;
    return *this;
  }

  auto const_preincrement_impl() const -> const vector_container_iterator<Item> & {
    ++current_;
    return *this;
  }

  auto predecrement_impl() const -> const vector_container_iterator<Item> & {
    --current_;
    return *this;
  }

  [[nodiscard]] constexpr auto operator[](size_type pos) noexcept -> reference {
    return begin_[pos];
  }

  [[nodiscard]] constexpr auto operator[](size_type pos) const noexcept -> const_reference {
    return begin_[pos];
  }

  [[nodiscard]] friend constexpr auto operator+=(const vector_container_iterator<Item> &lhs, size_type n)
    -> const vector_container_iterator<Item> & {
    lhs.current_ += n;
    return lhs;
  }

  [[nodiscard]] friend constexpr auto operator+(const vector_container_iterator<Item> &lhs, size_type n)
    -> vector_container_iterator<Item> {
    return lhs += n;
  }

  [[nodiscard]] friend constexpr auto operator+(size_type n, const vector_container_iterator<Item> &rhs)
    -> vector_container_iterator<Item> {
    return rhs += n;
  }

  [[nodiscard]] friend constexpr auto operator-=(const vector_container_iterator<Item> &lhs, size_type n)
    -> vector_container_iterator<Item> & {
    return lhs += -n;
  }

  [[nodiscard]] friend constexpr auto operator-(const vector_container_iterator<Item> &lhs, size_type n)
    -> vector_container_iterator<Item> {
    return lhs -= n;
  }

  [[nodiscard]] friend constexpr auto operator-(const vector_container_iterator<Item> &lhs,
    const vector_container_iterator<Item> &rhs) -> difference_type {
    return std::distance(rhs.current_, lhs.current_);
  }

  [[nodiscard]] friend constexpr auto operator==(const vector_container_iterator<Item> &lhs,
    const vector_container_iterator<Item> &rhs) noexcept -> bool {
    return lhs.current_ == rhs.current_;
  }

  [[nodiscard]] friend constexpr auto operator!=(const vector_container_iterator<Item> &lhs,
    const vector_container_iterator<Item> &rhs) noexcept -> bool {
    return !(lhs == rhs);
  }

  [[nodiscard]] friend constexpr auto operator<(const vector_container_iterator<Item> &lhs,
    const vector_container_iterator<Item> &rhs) noexcept -> bool {
    return rhs - lhs > 0;
  }

  [[nodiscard]] friend constexpr auto operator<=(const vector_container_iterator<Item> &lhs,
    const vector_container_iterator<Item> &rhs) noexcept -> bool {
    return !(rhs < lhs);
  }

  [[nodiscard]] friend constexpr auto operator>(const vector_container_iterator<Item> &lhs,
    const vector_container_iterator<Item> &rhs) noexcept -> bool {
    return rhs < lhs;
  }

  [[nodiscard]] friend constexpr auto operator>=(const vector_container_iterator<Item> &lhs,
    const vector_container_iterator<Item> &rhs) noexcept -> bool {
    return !(lhs < rhs);
  }

  mutable std_vector_container_iterator current_;
  std_vector_container_iterator begin_;
  std_vector_container_iterator end_;
};

}// namespace ftl

