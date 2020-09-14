#pragma once

#include <ftl/iterator_interface.hpp>
#include <ftl/enumerate_iterator.hpp>
#include <ftl/map_iterator.hpp>
#include <ftl/inspect_iterator.hpp>

namespace ftl {

template<typename Item, std::size_t N>
class array_container_iterator final
  : public iterator_interface<array_container_iterator<Item, N>, Item, std::size_t>
  , public iterator_member_provider<array_container_iterator<Item, N>, std::random_access_iterator_tag> {

  friend iterator_interface<array_container_iterator<Item, N>, Item, std::size_t>;
  friend const_iterator_interface<array_container_iterator<Item, N>, Item, std::size_t>;
  friend iterator_member_provider<array_container_iterator<Item, N>, std::random_access_iterator_tag>;

public:
  using difference_type = std::ptrdiff_t;
  using value_type = std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::random_access_iterator_tag;
  using size_type = std::size_t;

  constexpr array_container_iterator(pointer const begin, pointer const end) : position_{ 0 }, begin_{ begin }, end_{ end } {
  }

  constexpr array_container_iterator(size_type position, pointer const begin, pointer const end)
    : position_{ position }, begin_{ begin }, end_{ end } {
  }

  constexpr auto operator=(const array_container_iterator &) -> array_container_iterator & = default;

//private:
  template<typename Collection>
  [[nodiscard]] auto collect_impl() -> Collection {
    return from_iterator_trait<array_container_iterator<Item, N>, Collection>::from_iter(*this);
  }

  [[nodiscard]] auto enumerate_impl() const -> enumerate_iterator<array_container_iterator<Item, N>> {
    return { *this };
  }

  template<typename NewCallable>
  [[nodiscard]] auto inspect_impl(NewCallable &&callable) const
    -> inspect_iterator<array_container_iterator<Item, N>, NewCallable> {
    return { *this, std::forward<NewCallable>(callable) };
  }

  template<typename Callable>
  [[nodiscard]] auto map_impl(Callable &&callable) const -> map_iterator<array_container_iterator<Item, N>, Callable> {
    return { *this, std::forward<Callable>(callable) };
  }

  template<typename Callable>
  [[nodiscard]] auto filter_impl(Callable &&callable) const -> filter_iterator<array_container_iterator<Item, N>, Callable> {
    return { *this, std::forward<Callable>(callable) };
  }

  [[nodiscard]] constexpr auto count_impl() const -> size_type {
    return static_cast<size_type>(end_ - begin_);
  }

  [[nodiscard]] constexpr auto begin_impl() noexcept -> array_container_iterator<Item, N> {
    return { 0, begin_, end_ };
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> array_container_iterator<Item, N> {
    return { 0, begin_, end_ };
  }

  [[nodiscard]] constexpr auto end_impl() noexcept -> array_container_iterator<Item, N> {
    return { N, begin_, end_ };
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> array_container_iterator<Item, N> {
    return { N, begin_, end_ };
  }

  [[nodiscard]] constexpr auto deref_impl() -> reference {
    return begin_[position_];
  }

  [[nodiscard]] constexpr auto const_deref_impl() const -> const_reference {
    return begin_[position_];
  }

  auto preincrement_impl() -> array_container_iterator<Item, N> & {
    ++position_;

    return *this;
  }

  auto predecrement_impl() const -> const array_container_iterator<Item, N> & {
    --position_;
    return *this;
  }

  mutable size_type position_;
  pointer begin_;
  pointer end_;
};

}// namespace ftl

template<typename Item, std::size_t N>
struct std::iterator_traits<ftl::array_container_iterator<Item, N>> {
  using difference_type = typename ftl::array_container_iterator<Item, N>::difference_type;
  using value_type = typename ftl::array_container_iterator<Item, N>::value_type;
  using pointer = typename ftl::array_container_iterator<Item, N>::pointer;
  using reference = typename ftl::array_container_iterator<Item, N>::reference;
  using iterator_category = typename ftl::array_container_iterator<Item, N>::iterator_category;
};
