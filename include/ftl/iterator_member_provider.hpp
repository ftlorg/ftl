#pragma once

#include <iterator>

namespace ftl {

  // TODO: Think about std::enable_if and only one struct with all of the operators that are enabled/disabled via
  //       the std::enable_if statement based on iterator_tag.
  //       i.e.
  //       [[nodiscard]] auto operator*() 
  //          -> typename std::enable_if_t<is_contained<IterCategory, std::bidirectional_tag, std::random_access_tag>, decltype(auto)> {
  //          return static_cast<Iter &>(*this).deref_impl();
  //       }
  // 
  //      We would have to write the above is_contained meta-function to check if the IterCategory is the same as one of the provided tags.

template<typename Iter, typename IterCategory = void>
struct iterator_member_provider {
  [[nodiscard]] auto operator*() -> decltype(auto) {
    return static_cast<Iter &>(*this).deref_impl();
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
struct iterator_member_provider<Iter, std::forward_iterator_tag>
  : iterator_member_provider<Iter, std::input_iterator_tag> {};

template<typename Iter>
struct iterator_member_provider<Iter, std::bidirectional_iterator_tag>
  : iterator_member_provider<Iter, std::forward_iterator_tag> {
  auto operator--() const -> Iter & {
    return static_cast<const Iter &>(*this).predecrement_impl();
  }

  auto operator--(int) -> Iter {
    auto tmp = *static_cast<Iter &>(*this);

    --static_cast<Iter &>(*this);

    return static_cast<Iter &>(*this);
  }
};

template<typename Iter>
struct iterator_member_provider<Iter, std::random_access_iterator_tag>
  : iterator_member_provider<Iter, std::bidirectional_iterator_tag> {
  using size_type = std::size_t;

  [[nodiscard]] constexpr auto operator[](size_type pos) noexcept -> decltype(auto) {
    return static_cast<Iter &>(*this).begin_[pos];
  }

  [[nodiscard]] constexpr auto operator[](size_type pos) const noexcept -> decltype(auto) {
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

  [[nodiscard]] friend constexpr auto operator-(const Iter &lhs, const Iter &rhs) -> decltype(auto) {
    return std::distance(rhs.current_, lhs.current_);
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