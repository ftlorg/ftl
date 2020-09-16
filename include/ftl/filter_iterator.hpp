#pragma once

#include <ftl/iterator_interface.hpp>

namespace ftl {

template<typename Iter, typename Callable>
class filter_iterator final
  : public const_iterator_interface<filter_iterator<Iter, Callable>, typename Iter::value_type, typename Iter::size_type> {

  friend const_iterator_interface<filter_iterator<Iter, Callable>, typename Iter::value_type, typename Iter::size_type>;

public:
  using difference_type = typename Iter::difference_type;
  using value_type = typename Iter::value_type;
  using pointer = typename Iter::pointer;
  using reference = typename Iter::reference;
  using const_pointer = typename Iter::const_pointer;
  using const_reference = typename Iter::const_reference;
  using iterator_category = std::forward_iterator_tag;
  using inherited_iterator_category = typename Iter::iterator_category;
  using size_type = typename Iter::size_type;

  filter_iterator(Iter iterator, Callable callable) : iterator_{ std::move(iterator) }, callable_{ std::move(callable) } {
    while (iterator_ != iterator_.cend() && !callable_(*iterator_)) { ++iterator_; }
  }

private:
  template<typename Collection>
  [[nodiscard]] auto collect_impl() const -> Collection {
    return from_iterator_trait<filter_iterator<Iter, Callable>, Collection>::from_iter(*this);
  }

  [[nodiscard]] auto enumerate_impl() const -> enumerate_iterator<filter_iterator<Iter, Callable>> {
    return { *this };
  }

  template<typename NewCallable>
  [[nodiscard]] auto filter_impl(NewCallable &&callable) const
    -> filter_iterator<filter_iterator<Iter, Callable>, NewCallable> {
    return { *this, std::forward<NewCallable>(callable) };
  }

  template<typename NewCallable>
  [[nodiscard]] auto map_impl(NewCallable &&callable) const -> map_iterator<filter_iterator<Iter, Callable>, NewCallable> {
    return { *this, std::forward<NewCallable>(callable) };
  }

  [[nodiscard]] constexpr auto begin_impl() const noexcept -> filter_iterator<Iter, Callable> {
    return { iterator_.cbegin(), callable_ };
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> filter_iterator<Iter, Callable> {
    return { iterator_.cbegin(), callable_ };
  }

  [[nodiscard]] constexpr auto end_impl() const noexcept -> filter_iterator<Iter, Callable> {
    return { iterator_.cend(), callable_ };
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> filter_iterator<Iter, Callable> {
    return { iterator_.cend(), callable_ };
  }

  [[nodiscard]] constexpr auto const_deref_impl() const -> decltype(std::declval<Iter>().operator*()) {
    return *iterator_;
  }

  auto preincrement_impl() const -> const filter_iterator<Iter, Callable> & {
    while (++iterator_ != iterator_.cend() && !callable_(*iterator_)) {}
    return *this;
  }

  auto postincrement_impl() const -> const filter_iterator<Iter, Callable> & {
    while (iterator_ != iterator_.cend() && !callable_(*iterator_)) { iterator_++; }
    return *this;
  }

  [[nodiscard]] friend constexpr auto operator==(const filter_iterator<Iter, Callable> &lhs,
    const filter_iterator<Iter, Callable> &rhs) noexcept -> bool {
    return lhs.iterator_ == rhs.iterator_;
  }

  [[nodiscard]] friend constexpr auto operator!=(const filter_iterator<Iter, Callable> &lhs,
    const filter_iterator<Iter, Callable> &rhs) noexcept -> bool {
    return lhs.iterator_ != rhs.iterator_;
  }

private:
  mutable Iter iterator_;
  Callable callable_;
};

}// namespace ftl

template<typename Iter, typename Callable>
struct std::iterator_traits<ftl::filter_iterator<Iter, Callable>> {
  using difference_type = typename ftl::filter_iterator<Iter, Callable>::difference_type;
  using value_type = typename ftl::filter_iterator<Iter, Callable>::value_type;
  using pointer = typename ftl::filter_iterator<Iter, Callable>::pointer;
  using reference = typename ftl::filter_iterator<Iter, Callable>::reference;
  using iterator_category = typename ftl::filter_iterator<Iter, Callable>::iterator_category;
};