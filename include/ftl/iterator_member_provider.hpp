#pragma once
#include <iterator>
#include <ftl/iterator_traits.hpp>

namespace ftl {

template<typename Iter, typename IterCategory = void>
struct iterator_member_provider {
  [[nodiscard]] auto operator*() const -> decltype(auto) {
    return static_cast<const Iter &>(*this).const_deref_impl();
  }

  auto operator++() -> decltype(auto) {
    return static_cast<Iter &>(*this).preincrement_impl();
  }

  auto operator++() const -> decltype(auto) {
    return static_cast<const Iter &>(*this).const_preincrement_impl();
  }

  auto operator++(int) const -> decltype(auto) {
    auto result = *this;
    ++static_cast<const Iter &>(*this);
    return result;
  }

  auto operator++(int) -> decltype(auto) {
    auto result = *this;
    ++static_cast<Iter &>(*this);
    return result;
  }

  [[nodiscard]] constexpr auto begin() noexcept -> Iter {
    return static_cast<Iter &>(*this).begin_impl();
  }

  [[nodiscard]] constexpr auto begin() const noexcept -> Iter {
    return static_cast<const Iter &>(*this).begin_impl();
  }

  [[nodiscard]] constexpr auto cbegin() const noexcept -> Iter {
    return static_cast<const Iter &>(*this).cbegin_impl();
  }

  [[nodiscard]] constexpr auto end() noexcept -> Iter {
    return static_cast<Iter &>(*this).end_impl();
  }

  [[nodiscard]] constexpr auto end() const noexcept -> Iter {
    return static_cast<const Iter &>(*this).end_impl();
  }

  [[nodiscard]] constexpr auto cend() const noexcept -> Iter {
    return static_cast<const Iter &>(*this).cend_impl();
  }
};

template<typename Iter>
struct iterator_member_provider<Iter, std::input_iterator_tag> : public iterator_member_provider<Iter> {
  constexpr auto operator==(const Iter &rhs) const -> bool {
    return static_cast<const Iter &>(*this).iterator_ == rhs.iterator_;
  }

  constexpr friend auto operator!=(const Iter &lhs, const Iter &rhs) {
    return !(lhs == rhs);
  }

  //  constexpr auto operator->() const -> typename std::iterator_traits<Iter>::const_reference {
  //    return *static_cast<Iter &>(*this).iterator_;
  //  }
  //
  //  constexpr auto operator->() -> typename std::iterator_traits<Iter>::reference {
  //    return *static_cast<Iter &>(*this).iterator_;
  //  }
};

template<typename Iter>
struct iterator_member_provider<Iter, std::output_iterator_tag> : public iterator_member_provider<Iter> {
  constexpr friend auto operator==(const Iter &lhs, const Iter &rhs) {
    return lhs.begin_ == rhs.begin_ && lhs.end_ == rhs.end_ && lhs.iterator_ == rhs.iterator_;
  }

  constexpr friend auto operator!=(const Iter &lhs, const Iter &rhs) {
    return !(lhs == rhs);
  }

  constexpr auto operator->() const -> typename std::iterator_traits<Iter>::const_reference {
    return *static_cast<Iter &>(*this).iterator_;
  }

  constexpr auto operator->() -> typename std::iterator_traits<Iter>::reference {
    return *static_cast<Iter &>(*this).iterator_;
  }
};

template<typename Iter>
struct iterator_member_provider<Iter, std::forward_iterator_tag>
  : public iterator_member_provider<Iter, std::input_iterator_tag> {};

template<typename Iter>
struct iterator_member_provider<Iter, std::bidirectional_iterator_tag>
  : public iterator_member_provider<Iter, std::forward_iterator_tag> {
  auto operator--() const -> const Iter & {
    return --static_cast<const Iter &>(*this).iterator_;
  }

  auto operator--() -> Iter & {
    return --static_cast<Iter &>(*this).iterator_;
  }

  auto operator--(int) -> Iter {
    auto tmp = static_cast<Iter &>(*this);

    --static_cast<Iter &>(*this);

    return tmp;
  }

  auto operator--(int) const -> Iter {
    auto tmp = static_cast<const Iter &>(*this);

    --static_cast<const Iter &>(*this);

    return tmp;
  }
};

template<typename Iter>
struct iterator_member_provider<Iter, std::random_access_iterator_tag>
  : public iterator_member_provider<Iter, std::bidirectional_iterator_tag> {

  [[nodiscard]] constexpr auto operator[](typename std::iterator_traits<Iter>::size_type pos) noexcept ->
    typename std::iterator_traits<Iter>::reference {
    return static_cast<Iter &>(*this).begin_[pos];
  }

  [[nodiscard]] constexpr auto operator[](typename std::iterator_traits<Iter>::size_type pos) const noexcept ->
    typename std::iterator_traits<Iter>::const_reference {
    return static_cast<Iter &>(*this).begin_[pos];
  }

  constexpr auto operator+=(typename std::iterator_traits<Iter>::size_type n) -> Iter & {
    static_cast<Iter&>(*this).iterator_ += n;
    return static_cast<Iter &>(*this);
  }

  [[nodiscard]] friend constexpr auto operator+(const Iter &lhs, typename std::iterator_traits<Iter>::size_type n) -> Iter {
    return lhs += n;
  }

  [[nodiscard]] friend constexpr auto operator+(typename std::iterator_traits<Iter>::size_type n, const Iter &rhs) -> Iter {
    return rhs += n;
  }

  friend constexpr auto operator-=(const Iter &lhs, typename std::iterator_traits<Iter>::size_type n) -> Iter & {
    return lhs += -n;
  }

  [[nodiscard]] friend constexpr auto operator-(const Iter &lhs, typename std::iterator_traits<Iter>::size_type n) -> Iter {
    return lhs -= n;
  }

  [[nodiscard]] constexpr auto operator-(const Iter &rhs) const -> typename std::iterator_traits<Iter>::difference_type {
    return std::distance(rhs.iterator_, static_cast<const Iter &>(*this).iterator_);
  }

  [[nodiscard]] friend constexpr auto operator<(const Iter &lhs, const Iter &rhs) noexcept -> bool {
    return rhs - lhs > 0;
  }

  [[nodiscard]] friend constexpr auto operator<=(const Iter &lhs, const Iter &rhs) noexcept -> bool {
    return !(rhs < lhs);
  }


  [[nodiscard]] friend constexpr auto operator>(const Iter &lhs, const Iter &rhs) noexcept -> bool {
    return rhs < lhs;
  }

  [[nodiscard]] friend constexpr auto operator>=(const Iter &lhs, const Iter &rhs) noexcept -> bool {
    return !(lhs < rhs);
  }
};


}// namespace ftl