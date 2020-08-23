#pragma once

#include <ftl/iterator_interface.hpp>

namespace ftl {

template<typename Iter, typename Callable>
class inspect_iterator
  : public const_iterator_interface<inspect_iterator<Iter, Callable>, typename Iter::value_type, typename Iter::size_type> {

  friend const_iterator_interface<inspect_iterator<Iter, Callable>, typename Iter::value_type, typename Iter::size_type>;

public:
  using difference_type = typename Iter::difference_type;
  using value_type = typename Iter::value_type;
  using pointer = typename Iter::pointer;
  using reference = typename Iter::reference;
  using const_pointer = typename Iter::const_pointer;
  using const_reference = typename Iter::const_reference;
  using iterator_category = typename Iter::iterator_category;
  using size_type = typename Iter::size_type;

  inspect_iterator(Iter iterator, Callable callable) : iterator_{ std::move(iterator) }, callable_{ std::move(callable) } {
  }

private:
  template<typename Collection>
  [[nodiscard]] auto collect_impl() const -> Collection {
    return from_iterator_trait<inspect_iterator<Iter, Callable>, Collection>::from_iter(*this);
  }

  [[nodiscard]] constexpr auto count_impl() const -> size_type {
    return iterator_.count();
  }

  [[nodiscard]] auto enumerate_impl() const -> enumerate_iterator<inspect_iterator<Iter, Callable>> {
    return { *this };
  }

  template<typename NewCallable>
  [[nodiscard]] auto inspect_impl(NewCallable &&callable) const
    -> inspect_iterator<inspect_iterator<Iter, Callable>, NewCallable> {
    return { *this, std::forward<NewCallable>(callable) };
  }

  template<typename NewCallable>
  [[nodiscard]] auto map_impl(NewCallable &&callable) const -> map_iterator<inspect_iterator<Iter, Callable>, NewCallable> {
    return { *this, std::forward<NewCallable>(callable) };
  }

  [[nodiscard]] constexpr auto begin_impl() const noexcept -> inspect_iterator<Iter, Callable> {
    return { iterator_.cbegin(), callable_ };
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> inspect_iterator<Iter, Callable> {
    return { iterator_.cbegin(), callable_ };
  }

  [[nodiscard]] constexpr auto end_impl() const noexcept -> inspect_iterator<Iter, Callable> {
    return { iterator_.cend(), callable_ };
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> inspect_iterator<Iter, Callable> {
    return { iterator_.cend(), callable_ };
  }

  [[nodiscard]] constexpr auto const_deref_impl() const -> decltype(std::declval<const Iter&>().operator*()) {
    callable_(*iterator_);
    return *static_cast<const Iter&>(iterator_);
  }

  auto preincrement_impl() const -> void {
    ++iterator_;
  }

  [[nodiscard]] friend constexpr auto operator+=(const inspect_iterator<Iter, Callable> &lhs, size_type n)
    -> inspect_iterator<Iter, Callable> & {
    return lhs.iterator_ += n;
  }

  [[nodiscard]] friend constexpr auto operator+(const inspect_iterator<Iter, Callable> &lhs, size_type n)
    -> inspect_iterator<Iter, Callable> {
    return lhs.iterator_ += n;
  }

  [[nodiscard]] friend constexpr auto operator+(size_type n, const inspect_iterator<Iter, Callable> &rhs)
    -> inspect_iterator<Iter, Callable> {
    return rhs.iterator_ += n;
  }

  [[nodiscard]] friend constexpr auto operator-=(const inspect_iterator<Iter, Callable> &lhs, size_type n)
    -> inspect_iterator<Iter, Callable> & {
    return lhs.iterator_ += -n;
  }

  [[nodiscard]] friend constexpr auto operator-(const inspect_iterator<Iter, Callable> &lhs, size_type n)
    -> inspect_iterator<Iter, Callable> {
    return lhs.iterator_ -= n;
  }

  [[nodiscard]] friend constexpr auto operator-(const inspect_iterator<Iter, Callable> &lhs,
    const inspect_iterator<Iter, Callable> &rhs) -> difference_type {
    return lhs.iterator_ - rhs.iterator_;
  }

  [[nodiscard]] friend constexpr auto operator==(const inspect_iterator<Iter, Callable> &lhs,
    const inspect_iterator<Iter, Callable> &rhs) noexcept -> bool {
    return lhs.iterator_ == rhs.iterator_;
  }

  [[nodiscard]] friend constexpr auto operator!=(const inspect_iterator<Iter, Callable> &lhs,
    const inspect_iterator<Iter, Callable> &rhs) noexcept -> bool {
    return lhs.iterator_ != rhs.iterator_;
  }

  [[nodiscard]] friend constexpr auto operator<(const inspect_iterator<Iter, Callable> &lhs,
    const inspect_iterator<Iter, Callable> &rhs) noexcept -> bool {
    return rhs.iterator_ - lhs.iterator_ > 0;
  }

  [[nodiscard]] friend constexpr auto operator<=(const inspect_iterator<Iter, Callable> &lhs,
    const inspect_iterator<Iter, Callable> &rhs) noexcept -> bool {
    return !(rhs.iterator_ < lhs.iterator_);
  }

  [[nodiscard]] friend constexpr auto operator>(const inspect_iterator<Iter, Callable> &lhs,
    const inspect_iterator<Iter, Callable> &rhs) noexcept -> bool {
    return rhs.iterator_ < lhs.iterator_;
  }

  [[nodiscard]] friend constexpr auto operator>=(const inspect_iterator<Iter, Callable> &lhs,
    const inspect_iterator<Iter, Callable> &rhs) noexcept -> bool {
    return !(lhs.iterator_ < rhs.iterator_);
  }

private:
  Iter iterator_;
  Callable callable_;
};

}// namespace ftl

template<typename Iter, typename Callable>
struct std::iterator_traits<ftl::inspect_iterator<Iter, Callable>> {
  using difference_type = typename ftl::inspect_iterator<Iter, Callable>::difference_type;
  using value_type = typename ftl::inspect_iterator<Iter, Callable>::value_type;
  using pointer = typename ftl::inspect_iterator<Iter, Callable>::pointer;
  using reference = typename ftl::inspect_iterator<Iter, Callable>::reference;
  using iterator_category = typename ftl::inspect_iterator<Iter, Callable>::iterator_category;
};
