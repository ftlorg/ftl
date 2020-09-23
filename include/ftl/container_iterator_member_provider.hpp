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

  constexpr auto operator->() const -> Iter::const_reference {
    return *static_cast<Iter &>(*this).current_;
  }

  constexpr auto operator->() -> Iter::reference {
    return *static_cast<Iter &>(*this).current_;
  }
};

template<typename Iter>
struct container_iterator_member_provider<Iter, std::output_iterator_tag> : public container_iterator_member_provider<Iter> {
  constexpr friend auto operator==(const Iter &lhs, const Iter &rhs) {
    return lhs.begin_ == rhs.begin_ && lhs.end_ == rhs.end_ && lhs.current_ == rhs.current_;
  }

  constexpr friend auto operator!=(const Iter &lhs, const Iter &rhs) {
    return !(lhs == rhs);
  }

  constexpr auto operator->() const -> Iter::const_reference {
    return *static_cast<Iter &>(*this).current_;
  }

  constexpr auto operator->() -> Iter::reference {
    return *static_cast<Iter &>(*this).current_;
  }
};


}// namespace ftl