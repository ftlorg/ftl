#pragma once

#include <iterator>

namespace ftl {

template<typename Iter, typename IterCategory = void>
struct iterator_member_provider {
  using value_type = typename Iter::value_type;
  using pointer = typename Iter::pointer;
  using reference = typename Iter::reference;
  using const_pointer = typename Iter::const_pointer;
  using const_reference = typename Iter::const_reference;
  using size_type = typename Iter::size_type;
  using difference_type = typename Iter::difference_type;

  [[nodiscard]] auto operator*() -> decltype(auto) {
    return static_cast<const Iter &>(*this).deref_impl();
  }

  [[nodiscard]] auto operator*() const -> decltype(auto) {
    return static_cast<const Iter &>(*this).const_deref_impl();
  }

  auto operator++() const -> Iter & {
    return static_cast<const Iter &>(*this).preincrement_impl();
  }

  auto operator++(int) -> Iter {
    auto tmp = *static_cast<Iter &>(*this);

    ++static_cast<Iter &>(*this);

    return static_cast<Iter &>(*this);
  }
};

template<typename Iter>
struct iterator_member_provider<Iter, std::input_iterator_tag> : iterator_member_provider<Iter> {
  [[nodiscard]] friend constexpr auto operator==(const Iter &lhs, const Iter &rhs) noexcept -> bool {
    return lhs.iterator_ == rhs.iterator_;
  }

  [[nodiscard]] friend constexpr auto operator!=(const Iter &lhs, const Iter &rhs) noexcept -> bool {
    return !(lhs == rhs);
  }

  [[nodiscard]] auto operator->() const -> decltype(auto) {
    /// ???
    throw int{ -1 };
  }
};

template<typename Iter>
struct iterator_member_provider<Iter, std::output_iterator_tag> : iterator_member_provider<Iter> {};

template<typename Iter>
struct iterator_member_provider<Iter, std::forward_iterator_tag> : iterator_member_provider<Iter, std::input_iterator_tag> {};

template<typename Iter>
struct iterator_member_provider<Iter, std::bidirectional_iterator_tag> : iterator_member_provider<Iter, std::forward_iterator_tag> {
  virtual auto operator--() -> Iter & = 0;// Implementation specific

  auto operator--(int) -> Iter {
    auto tmp = *static_cast<Iter &>(*this);

    --static_cast<Iter &>(*this);

    return static_cast<Iter &>(*this);
  }
};

template<typename Iter>
struct iterator_member_provider<Iter, std::random_access_iterator_tag> : iterator_member_provider<Iter> {
  using reference = typename Iter::reference;
  using const_reference = typename Iter::const_reference;
  using size_type = typename Iter::size_type;
  using difference_type = typename Iter::difference_type;

  [[nodiscard]] constexpr auto operator[](size_type pos) noexcept -> reference {
    return static_cast<Iter &>(*this).begin_[pos];
  }

  [[nodiscard]] constexpr auto operator[](size_type pos) const noexcept -> const_reference {
    return static_cast<Iter &>(*this).begin_[pos];
  }

  [[nodiscard]] friend constexpr auto operator+=(const Iter &lhs, size_type n) -> const Iter & {
    lhs.current_ += n;
    return lhs;
  }

  [[nodiscard]] friend constexpr auto operator+(const Iter &lhs, size_type n) -> Iter {
    return lhs += n;
  }

  [[nodiscard]] friend constexpr auto operator+(size_type n, const Iter &rhs) -> Iter {
    return rhs += n;
  }

  [[nodiscard]] friend constexpr auto operator-=(const Iter &lhs, size_type n) -> Iter & {
    return lhs += -n;
  }

  [[nodiscard]] friend constexpr auto operator-(const Iter &lhs, size_type n) -> Iter {
    return lhs -= n;
  }

  [[nodiscard]] friend constexpr auto operator-(const Iter &lhs, const Iter &rhs) -> difference_type {
    return std::distance(rhs.current_, lhs.current_);
  }

  [[nodiscard]] friend constexpr auto operator==(const Iter &lhs, const Iter &rhs) noexcept -> bool {
    return lhs.current_ == rhs.current_;
  }

  [[nodiscard]] friend constexpr auto operator!=(const Iter &lhs, const Iter &rhs) noexcept -> bool {
    return !(lhs == rhs);
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