#pragma once
#include <iterator>

namespace ftl {

template<typename Iter, typename IterCategory = void>
struct container_iterator_member_provider {
  [[nodiscard]] auto operator*() const -> decltype(auto) {
    return *static_cast<const Iter &>(*this).current_;
  }

  [[nodiscard]] auto operator*() -> decltype(auto) {
    return *static_cast<Iter &>(*this).current_;
  }

  auto operator++() const -> Iter & {
    return ++static_cast<const Iter &>(*this).current_;
  }

  auto operator++(int) -> Iter {
    auto tmp = static_cast<Iter &>(*this);

    ++static_cast<Iter &>(*this);

    return tmp;
  }
};

template<typename Iter>
struct container_iterator_member_provider<Iter, std::input_iterator_tag> : public container_iterator_member_provider<Iter> {
  constexpr friend auto operator==(const Iter &lhs, const Iter &rhs) {
    return lhs.begin_ == rhs.begin_ && lhs.end_ == rhs.end_ && lhs.current_ == rhs.current_;
  }

  constexpr friend auto operator!=(const Iter &lhs, const Iter &rhs) {
    return !(lhs == rhs);
  }

//  constexpr auto operator->() const -> typename Iter::const_reference {
//    return *static_cast<Iter &>(*this).current_;
//  }
//
//  constexpr auto operator->() -> typename Iter::reference {
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

  constexpr auto operator->() const -> typename Iter::const_reference {
    return *static_cast<Iter &>(*this).current_;
  }

  constexpr auto operator->() -> typename Iter::reference {
    return *static_cast<Iter &>(*this).current_;
  }
};

template <typename Iter>
struct container_iterator_member_provider<Iter, std::forward_iterator_tag> : public container_iterator_member_provider<Iter, std::input_iterator_tag> {
};

template <typename Iter>
struct container_iterator_member_provider<Iter, std::bidirectional_iterator_tag> : public container_iterator_member_provider<Iter, std::forward_iterator_tag> {
  auto operator--() const -> Iter & {
    return --static_cast<const Iter &>(*this).current_;
  }

  auto operator--(int) -> Iter {
    auto tmp = static_cast<Iter &>(*this);

    --static_cast<Iter &>(*this);

    return tmp;
  }
};

template <typename Iter>
struct container_iterator_member_provider<Iter, std::random_access_iterator_tag> : public container_iterator_member_provider<Iter, std::bidirectional_iterator_tag> {
  [[nodiscard]] constexpr auto operator[](typename Iter::size_type pos) noexcept -> typename Iter::reference {
    return static_cast<Iter&>(*this).begin_[pos];
  }

  [[nodiscard]] constexpr auto operator[](typename Iter::size_type pos) const noexcept -> typename Iter::const_reference {
    return static_cast<Iter&>(*this).begin_[pos];
  }

  [[nodiscard]] friend constexpr auto operator+=(const Iter &lhs, typename Iter::size_type n)
  -> Iter & {
    lhs.current_ += n;
    return lhs;
  }

  [[nodiscard]] friend constexpr auto operator+(const Iter &lhs, typename Iter::size_type n)
  -> Iter {
    return lhs += n;
  }

  [[nodiscard]] friend constexpr auto operator+(typename Iter::size_type n, const Iter &rhs)
  -> Iter {
    return rhs += n;
  }

  [[nodiscard]] friend constexpr auto operator-=(const Iter &lhs, typename Iter::size_type n)
  -> Iter & {
    return lhs += -n;
  }

  [[nodiscard]] friend constexpr auto operator-(const Iter &lhs, typename Iter::size_type n)
  -> Iter {
    return lhs -= n;
  }

  [[nodiscard]] friend constexpr auto operator-(const Iter &lhs,
                                                const Iter &rhs) -> typename Iter::difference_type {
    return std::distance(rhs.current_, lhs.current_);
  }

  [[nodiscard]] friend constexpr auto operator<(const Iter &lhs,
                                                const Iter &rhs) noexcept -> bool {
    return rhs - lhs > 0;
  }

  [[nodiscard]] friend constexpr auto operator<=(const Iter &lhs, const Iter &rhs) noexcept
  -> bool {
    return !(rhs < lhs);
  }


  [[nodiscard]] friend constexpr auto operator>(const Iter &lhs, const Iter &rhs) noexcept
  -> bool {
    return rhs < lhs;
  }

  [[nodiscard]] friend constexpr auto operator>=(const Iter &lhs, const Iter &rhs) noexcept
  -> bool {
    return !(lhs < rhs);
  }
};


}// namespace ftl