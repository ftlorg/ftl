
// Copyright Grzegorz Litarowicz and Lukasz Gut 2020 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once
#include <iterator>
#include <ftl/iterator_traits.hpp>

namespace ftl {

template<typename Iter, typename IterCategory = void>
struct container_iterator_member_provider {
  static constexpr bool is_container_iterator = true;
  [[nodiscard]] auto operator*() const -> decltype(auto) {
    return *static_cast<const Iter &>(*this).current_;
  }

  [[nodiscard]] auto operator*() -> decltype(auto) {
    return *static_cast<Iter &>(*this).current_;
  }

  auto operator++() const -> const Iter & {
    ++static_cast<const Iter &>(*this).current_;
    return static_cast<const Iter &>(*this);
  }

  auto operator++() -> Iter & {
    ++static_cast<Iter &>(*this).current_;
    return static_cast<Iter &>(*this);
  }

  auto operator++(int) -> Iter {
    auto tmp = static_cast<Iter &>(*this);

    ++static_cast<Iter &>(*this);

    return tmp;
  }

  [[nodiscard]] constexpr auto begin() const noexcept -> Iter {
    return {
      static_cast<const Iter &>(*this).begin_, static_cast<const Iter &>(*this).begin_, static_cast<const Iter &>(*this).end_
    };
  }

  [[nodiscard]] constexpr auto begin() noexcept -> Iter {
    return { static_cast<Iter &>(*this).begin_, static_cast<Iter &>(*this).begin_, static_cast<Iter &>(*this).end_ };
  }

  [[nodiscard]] constexpr auto cbegin() const noexcept -> Iter {
    return {
      static_cast<const Iter &>(*this).begin_, static_cast<const Iter &>(*this).begin_, static_cast<const Iter &>(*this).end_
    };
  }

  [[nodiscard]] constexpr auto end() const noexcept -> Iter {
    return {
      static_cast<const Iter &>(*this).end_, static_cast<const Iter &>(*this).begin_, static_cast<const Iter &>(*this).end_
    };
  }

  [[nodiscard]] constexpr auto end() noexcept -> Iter {
    return { static_cast<Iter &>(*this).end_, static_cast<Iter &>(*this).begin_, static_cast<Iter &>(*this).end_ };
  }

  [[nodiscard]] constexpr auto cend() const noexcept -> Iter {
    return {
      static_cast<const Iter &>(*this).end_, static_cast<const Iter &>(*this).begin_, static_cast<const Iter &>(*this).end_
    };
  }
};

template<typename Iter>
struct container_iterator_member_provider<Iter, std::input_iterator_tag> : public container_iterator_member_provider<Iter> {
  constexpr auto operator==(const Iter &rhs) const -> bool {
    return static_cast<const Iter &>(*this).begin_ == rhs.begin_ && static_cast<const Iter &>(*this).end_ == rhs.end_
           && static_cast<const Iter &>(*this).current_ == rhs.current_;
  }

  constexpr friend auto operator!=(const Iter &lhs, const Iter &rhs) -> bool {
    return !(lhs == rhs);
  }

  //  constexpr auto operator->() const -> typename std::iterator_traits<Iter>::const_reference {
  //    return *static_cast<Iter &>(*this).current_;
  //  }
  //
  //  constexpr auto operator->() -> typename std::iterator_traits<Iter>::reference {
  //    return *static_cast<Iter &>(*this).current_;
  //  }
};

template<typename Iter>
struct container_iterator_member_provider<Iter, std::output_iterator_tag> : public container_iterator_member_provider<Iter> {
  constexpr friend auto operator==(const Iter &lhs, const Iter &rhs) {
    return lhs.begin_ == rhs.begin_ && lhs.end_ == rhs.end_ && lhs.current_ == rhs.current_;
  }

  constexpr friend auto operator!=(const Iter &lhs, const Iter &rhs) {
    return !(lhs == rhs);
  }

  constexpr auto operator->() const -> typename std::iterator_traits<Iter>::const_reference {
    return *static_cast<Iter &>(*this).current_;
  }

  constexpr auto operator->() -> typename std::iterator_traits<Iter>::reference {
    return *static_cast<Iter &>(*this).current_;
  }
};

template<typename Iter>
struct container_iterator_member_provider<Iter, std::forward_iterator_tag>
  : public container_iterator_member_provider<Iter, std::input_iterator_tag> {};

template<typename Iter>
struct container_iterator_member_provider<Iter, std::bidirectional_iterator_tag>
  : public container_iterator_member_provider<Iter, std::forward_iterator_tag> {

  auto operator--() const -> const Iter & {
    --static_cast<const Iter &>(*this).current_;
    return static_cast<const Iter &>(*this);
  }

  auto operator--() -> Iter & {
    --static_cast<Iter &>(*this).current_;
    return static_cast<Iter &>(*this);
  }

  auto operator--(int) -> Iter {
    auto tmp = static_cast<Iter &>(*this);

    --static_cast<Iter &>(*this);

    return tmp;
  }
};

template<typename Iter>
struct container_iterator_member_provider<Iter, std::random_access_iterator_tag>
  : public container_iterator_member_provider<Iter, std::bidirectional_iterator_tag> {

  [[nodiscard]] constexpr auto operator[](typename std::iterator_traits<Iter>::size_type pos) noexcept ->
    typename std::iterator_traits<Iter>::reference {
    return static_cast<Iter &>(*this).begin_[pos];
  }

  [[nodiscard]] constexpr auto operator[](typename std::iterator_traits<Iter>::size_type pos) const noexcept ->
    typename std::iterator_traits<Iter>::const_reference {
    return static_cast<Iter &>(*this).begin_[pos];
  }

  constexpr auto operator+=(typename std::iterator_traits<Iter>::size_type n) -> Iter & {
    static_cast<Iter &>(*this).current_ += static_cast<typename std::iterator_traits<Iter>::difference_type>(n);
    return static_cast<Iter &>(*this);
  }

  [[nodiscard]] friend constexpr auto operator+(Iter &lhs, typename std::iterator_traits<Iter>::size_type n) -> Iter {
    return lhs += n;
  }

  [[nodiscard]] friend constexpr auto operator+(Iter &&lhs, typename std::iterator_traits<Iter>::size_type n) -> Iter {
    return lhs += n;
  }

  [[nodiscard]] friend constexpr auto operator+(typename std::iterator_traits<Iter>::size_type n, Iter &rhs) -> Iter {
    return rhs += n;
  }

  [[nodiscard]] friend constexpr auto operator+(typename std::iterator_traits<Iter>::size_type n, Iter &&rhs) -> Iter {
    return rhs += n;
  }

  friend constexpr auto operator-=(const Iter &lhs, typename std::iterator_traits<Iter>::size_type n) -> Iter & {
    return lhs += -n;
  }

  [[nodiscard]] friend constexpr auto operator-(const Iter &lhs, typename std::iterator_traits<Iter>::size_type n) -> Iter {
    return lhs -= n;
  }

  [[nodiscard]] constexpr auto operator-(const Iter &rhs) const -> typename std::iterator_traits<Iter>::difference_type {
    return std::distance(rhs.current_, static_cast<const Iter &>(*this).current_);
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