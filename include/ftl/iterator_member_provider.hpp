#pragma once

#include <iterator>

namespace ftl {

template<typename Iter, typename IterCategory = void>
struct iterator_member_provider {
  [[nodiscard]] virtual auto operator*() -> decltype(auto) = 0;// Implementation specific

  [[nodiscard]] virtual auto operator*() const -> decltype(auto) = 0;// Implementation specific

  virtual auto operator++() -> Iter & = 0;// Implementation specific

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
struct iterator_member_provider<Iter, std::forward_iterator_tag> : iterator_member_provider<Iter> {};

template<typename Iter>
struct iterator_member_provider<Iter, std::bidirectional_iterator_tag> : iterator_member_provider<Iter> {
  virtual auto operator--() -> Iter & = 0;// Implementation specific

  auto operator--(int) -> Iter {
    auto tmp = *static_cast<Iter &>(*this);

    --static_cast<Iter &>(*this);

    return static_cast<Iter &>(*this);
  }
};

template<typename Iter>
struct iterator_member_provider<Iter, std::random_access_iterator_tag> : iterator_member_provider<Iter> {
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