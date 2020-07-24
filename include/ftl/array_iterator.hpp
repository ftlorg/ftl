#pragma once

#include <ftl/iterator.hpp>

namespace ftl {

template<typename Item, std::size_t N>
class array_iterator final : public iterator_interface<Item>
{
public:
  using iterator_category = /* */ void;
  using value_type = std::remove_cv_t<Item>;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  constexpr static size_type size = N;

  constexpr array_iterator(pointer const begin, pointer const end) : position_{ 0 }, begin_{ begin }, end_{ end } {}

  constexpr array_iterator(size_type position, pointer const begin, pointer const end) : position_{ position }, begin_{ begin }, end_{ end } {}

  [[nodiscard]] std::optional<value_type> next() override
  {
    ++position_;

    if (begin_ + position_ != end_) {
      return { begin_[position_] };
    }
    return std::nullopt;
  }

  template<typename Collection>
  [[nodiscard]] Collection collect()
  {
    return from_iterator_trait<array_iterator, Collection>::from_iter(*this);
  }

  template<typename Callable>
  [[nodiscard]] auto map(Callable &&callable) -> map_iterator<array_iterator<Item, N>, Callable>
  {
    return { array_iterator<Item, N>{ begin_, end_ }, std::forward<Callable>(callable) };
  }

  [[nodiscard]] constexpr array_iterator<Item, N> begin() noexcept { return { 0, begin_, end_ }; }

  [[nodiscard]] constexpr array_iterator<Item, N> cbegin() const noexcept { return { 0, begin_, end_ }; }

  [[nodiscard]] constexpr array_iterator<Item, N> end() noexcept { return { N, begin_, end_ }; }

  [[nodiscard]] constexpr array_iterator<Item, N> cend() const noexcept { return { N, begin_, end_ }; }

  [[nodiscard]] constexpr value_type operator*() override { return begin_[position_]; }

  [[nodiscard]] constexpr size_type count() const override { return std::distance(cbegin(), cend()); }

  void operator++() { position_++; }

  [[nodiscard]] friend constexpr bool operator!=(const array_iterator<Item, N> &lhs, const array_iterator<Item, N> &rhs)
  {
    return lhs.position_ != rhs.position_;
  }

private:
  mutable size_type position_;
  pointer const begin_;
  pointer const end_;
};

}// namespace ftl
