#pragma once

#include <ftl/iterator_interface.hpp>
#include <ftl/inspect_iterator.hpp>
#include <ftl/map_iterator.hpp>
#include <tuple>
#include <utility>

namespace ftl {

template<typename Iter>
class enumerate_iterator final
  : public iterator_interface<enumerate_iterator<Iter>, typename Iter::value_type, typename Iter::size_type> {
public:
  using difference_type = typename Iter::difference_type;
  using pointer = typename Iter::pointer;
  using reference = typename Iter::reference;
  using const_pointer = typename Iter::const_pointer;
  using const_reference = typename Iter::const_reference;
  using inherited_iterator_category = typename Iter::iterator_category;
  using iterator_category = inherited_iterator_category;
  using size_type = typename Iter::size_type;
  using value_type = typename Iter::value_type;

  enumerate_iterator(Iter iterator) : iterator_{ std::move(iterator) }, index_{ 0 } {
  }

  // private:
  [[nodiscard]] constexpr auto count_impl() const -> size_type {
    return iterator_.count();
  }

  [[nodiscard]] constexpr auto begin_impl() const noexcept -> enumerate_iterator<Iter> {
    return { iterator_.cbegin() };
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> enumerate_iterator<Iter> {
    return { iterator_.cbegin() };
  }

  [[nodiscard]] constexpr auto end_impl() const noexcept -> enumerate_iterator<Iter> {
    return { iterator_.cend() };
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> enumerate_iterator<Iter> {
    return { iterator_.cend() };
  }

  // TODO: Think about return type
  [[nodiscard]] constexpr auto deref_impl() -> std::tuple<size_type, decltype(std::declval<Iter>().operator*())> {
    return { index_, *iterator_ };
  }

  [[nodiscard]] constexpr auto const_deref_impl() const
    -> std::tuple<size_type, decltype(std::declval<Iter>().operator*())> {
    return { index_, *iterator_ };
  }

  auto preincrement_impl() -> enumerate_iterator<Iter> & {
    ++iterator_;
    ++index_;

    return *this;
  }

  [[nodiscard]] friend constexpr auto operator+=(const enumerate_iterator<Iter> &lhs, size_type n)
    -> enumerate_iterator<Iter> & {
    return lhs.iterator_ += n;
  }

  [[nodiscard]] friend constexpr auto operator+(const enumerate_iterator<Iter> &lhs, size_type n)
    -> enumerate_iterator<Iter> {
    return lhs.iterator_ += n;
  }

  [[nodiscard]] friend constexpr auto operator+(size_type n, const enumerate_iterator<Iter> &rhs)
    -> enumerate_iterator<Iter> {
    return rhs.iterator_ += n;
  }

  [[nodiscard]] friend constexpr auto operator-=(const enumerate_iterator<Iter> &lhs, size_type n)
    -> enumerate_iterator<Iter> & {
    return lhs.iterator_ += -n;
  }

  [[nodiscard]] friend constexpr auto operator-(const enumerate_iterator<Iter> &lhs, size_type n)
    -> enumerate_iterator<Iter> {
    return lhs.iterator_ -= n;
  }

  [[nodiscard]] friend constexpr auto operator-(const enumerate_iterator<Iter> &lhs, const enumerate_iterator<Iter> &rhs)
    -> difference_type {
    return lhs.iterator_ - rhs.iterator_;
  }

  [[nodiscard]] friend constexpr auto operator==(const enumerate_iterator<Iter> &lhs,
    const enumerate_iterator<Iter> &rhs) noexcept -> bool {
    return lhs.iterator_ == rhs.iterator_;
  }

  [[nodiscard]] friend constexpr auto operator!=(const enumerate_iterator<Iter> &lhs,
    const enumerate_iterator<Iter> &rhs) noexcept -> bool {
    return lhs.iterator_ != rhs.iterator_;
  }

  [[nodiscard]] friend constexpr auto operator<(const enumerate_iterator<Iter> &lhs,
    const enumerate_iterator<Iter> &rhs) noexcept -> bool {
    return rhs.iterator_ - lhs.iterator_ > 0;
  }

  [[nodiscard]] friend constexpr auto operator<=(const enumerate_iterator<Iter> &lhs,
    const enumerate_iterator<Iter> &rhs) noexcept -> bool {
    return !(rhs.iterator_ < lhs.iterator_);
  }

  [[nodiscard]] friend constexpr auto operator>(const enumerate_iterator<Iter> &lhs,
    const enumerate_iterator<Iter> &rhs) noexcept -> bool {
    return rhs.iterator_ < lhs.iterator_;
  }

  [[nodiscard]] friend constexpr auto operator>=(const enumerate_iterator<Iter> &lhs,
    const enumerate_iterator<Iter> &rhs) noexcept -> bool {
    return !(lhs.iterator_ < rhs.iterator_);
  }

  mutable Iter iterator_;
  mutable size_type index_;
};

}// namespace ftl

template<typename Iter>
struct std::iterator_traits<ftl::enumerate_iterator<Iter>> {
  using difference_type = typename ftl::enumerate_iterator<Iter>::difference_type;
  using value_type = typename ftl::enumerate_iterator<Iter>::value_type;
  using pointer = typename ftl::enumerate_iterator<Iter>::pointer;
  using reference = typename ftl::enumerate_iterator<Iter>::reference;
  using iterator_category = typename ftl::enumerate_iterator<Iter>::iterator_category;
};
