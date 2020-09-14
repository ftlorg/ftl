#pragma once

#include <ftl/iterator_interface.hpp>
#include <ftl/inspect_iterator.hpp>
#include <ftl/map_iterator.hpp>
#include <tuple>
#include <utility>

namespace ftl {

template<typename Iter>
class enumerate_iterator final
  : public iterator_interface<enumerate_iterator<Iter>, typename Iter::value_type, typename Iter::size_type> {

  friend iterator_interface<enumerate_iterator<Iter>, typename Iter::value_type, typename Iter::size_type>;
  friend const_iterator_interface<enumerate_iterator<Iter>, typename Iter::value_type, typename Iter::size_type>;

public:
  using difference_type = typename Iter::difference_type;
  using pointer = typename Iter::pointer;
  using reference = typename Iter::reference;
  using const_pointer = typename Iter::const_pointer;
  using const_reference = typename Iter::const_reference;
  using inherited_iterator_category = typename Iter::iterator_category;
  using iterator_category = inherited_iterator_category;
  using size_type = typename Iter::size_type;
  using value_type = typename Iter::value_type;

  enumerate_iterator(Iter iterator) : iterator_{ std::move(iterator) }, index_{ 0 } {
  }

// private:
  template<typename Collection>
  [[nodiscard]] auto collect_impl() const -> Collection {
    return from_iterator_trait<enumerate_iterator<Iter>, Collection>::from_iter(*this);
  }

  [[nodiscard]] constexpr auto count_impl() const -> size_type {
    return iterator_.count();
  }

  [[nodiscard]] auto enumerate_impl() const -> enumerate_iterator<enumerate_iterator<Iter>> {
    return { *this };
  }

  template<typename NewCallable>
  [[nodiscard]] auto inspect_impl(NewCallable &&callable) const -> inspect_iterator<enumerate_iterator<Iter>, NewCallable> {
    return { *this, std::forward<NewCallable>(callable) };
  }

  template<typename NewCallable>
  [[nodiscard]] auto map_impl(NewCallable &&callable) const -> map_iterator<enumerate_iterator<Iter>, NewCallable> {
    return { *this, std::forward<NewCallable>(callable) };
  }

  template<typename NewCallable>
  [[nodiscard]] auto filter_impl(NewCallable &&callable) const -> filter_iterator<enumerate_iterator<Iter>, NewCallable> {
    return { *this, std::forward<NewCallable>(callable) };
  }

  [[nodiscard]] constexpr auto begin_impl() const noexcept -> enumerate_iterator<Iter> {
    return { iterator_.cbegin() };
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> enumerate_iterator<Iter> {
    return { iterator_.cbegin() };
  }

  [[nodiscard]] constexpr auto end_impl() const noexcept -> enumerate_iterator<Iter> {
    return { iterator_.cend() };
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> enumerate_iterator<Iter> {
    return { iterator_.cend() };
  }

  // TODO: Think about return type
  [[nodiscard]] constexpr auto deref_impl() -> std::tuple<size_type, decltype(std::declval<Iter>().operator*())> {
    return { index_, *iterator_ };
  }

  [[nodiscard]] constexpr auto const_deref_impl() const
    -> std::tuple<size_type, decltype(std::declval<Iter>().operator*())> {
    return { index_, *iterator_ };
  }

  auto preincrement_impl() -> enumerate_iterator<Iter> & {
    ++iterator_;
    ++index_;

    return *this;
  }

  mutable Iter iterator_;
  mutable size_type index_;
};

}// namespace ftl

template<typename Iter>
struct std::iterator_traits<ftl::enumerate_iterator<Iter>> {
  using difference_type = typename ftl::enumerate_iterator<Iter>::difference_type;
  using value_type = typename ftl::enumerate_iterator<Iter>::value_type;
  using pointer = typename ftl::enumerate_iterator<Iter>::pointer;
  using reference = typename ftl::enumerate_iterator<Iter>::reference;
  using iterator_category = typename ftl::enumerate_iterator<Iter>::iterator_category;
};
