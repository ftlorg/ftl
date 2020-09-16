#pragma once

#include <ftl/iterator_interface.hpp>
#include <type_traits>

namespace ftl {

template<typename Iter>
class take_iterator
  : public const_iterator_interface<take_iterator<Iter>, typename Iter::value_type, typename Iter::size_type> {

  friend const_iterator_interface<take_iterator<Iter>, typename Iter::value_type, typename Iter::size_type>;

public:
  using difference_type = typename Iter::difference_type;
  using value_type = typename Iter::value_type;
  using pointer = typename Iter::pointer;
  using reference = typename Iter::reference;
  using const_pointer = typename Iter::const_pointer;
  using const_reference = typename Iter::const_reference;
  using inherited_iterator_category = typename Iter::iterator_category;
  using iterator_category = std::forward_iterator_tag;
  using size_type = typename Iter::size_type;

  take_iterator(Iter iterator, size_type n) : iterator_{ std::move(iterator) }, n_{ n } {
  }

  template<typename Collection>
  [[nodiscard]] auto collect_impl() const -> Collection {
    return from_iterator_trait<take_iterator<Iter>, Collection>::from_iter(*this);
  }

  [[nodiscard]] constexpr auto count_impl() const -> size_type {
    return iterator_.count();
  }

  [[nodiscard]] auto enumerate_impl() const -> enumerate_iterator<take_iterator<Iter>> {
    return { *this };
  }

  template<typename NewCallable>
  [[nodiscard]] auto inspect_impl(NewCallable &&callable) const -> inspect_iterator<take_iterator<Iter>, NewCallable> {
    return { *this, std::forward<NewCallable>(callable) };
  }

  template<typename NewCallable>
  [[nodiscard]] auto map_impl(NewCallable &&callable) const -> map_iterator<take_iterator<Iter>, NewCallable> {
    return { *this, std::forward<NewCallable>(callable) };
  }

  template<typename NewCallable>
  [[nodiscard]] auto filter_impl(NewCallable &&callable) const -> filter_iterator<take_iterator<Iter>, NewCallable> {
    return { *this, std::forward<NewCallable>(callable) };
  }

  [[nodiscard]] constexpr auto begin_impl() const noexcept -> take_iterator<Iter> {
    return { iterator_.cbegin(), n_ };
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> take_iterator<Iter> {
    return { iterator_.cbegin(), n_ };
  }

  [[nodiscard]] constexpr auto end_impl() const noexcept -> take_iterator<Iter> {
    return { iterator_.cend(), n_ };
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> take_iterator<Iter> {
    return { iterator_.cend(), n_ };
  }

  [[nodiscard]] constexpr auto const_deref_impl() const -> decltype(std::declval<const Iter &>().operator*()) {
    return *iterator_;
  }

  // TODO: const_preincrement_impl after new interfaces are merged...
  auto preincrement_impl() const -> const take_iterator<Iter> & {
    if (counter_ < n_ - 1) {
      ++iterator_;
      ++counter_;
    } else {
      while (++iterator_ != iterator_.end())
        ;
    }

    return *this;
  }

  [[nodiscard]] friend constexpr auto operator==(const take_iterator<Iter> &lhs, const take_iterator<Iter> &rhs) noexcept
    -> bool {
    return lhs.iterator_ == rhs.iterator_;
  }

  [[nodiscard]] friend constexpr auto operator!=(const take_iterator<Iter> &lhs, const take_iterator<Iter> &rhs) noexcept
    -> bool {
    return lhs.iterator_ != rhs.iterator_;
  }

  mutable Iter iterator_;
  const size_type n_ = 0;
  mutable size_type counter_ = 0;
};

}// namespace ftl