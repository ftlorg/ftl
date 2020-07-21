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
  constexpr static std::size_t size = N;
  using const_pointer = const value_type *;
  using reference = value_type &;
  using const_reference = value_type &;
  using size_type = std::size_t;

  constexpr array_iterator(pointer const begin, pointer const end) : iterator_interface<Item>{ begin }, position_{ 0 }, begin_{ begin }, end_{ end } {}

  [[nodiscard]] std::optional<value_type> next() override
  {
    ++position_;

    if (begin_ + position_ != end_) {
      iterator_interface<Item>::item_ = begin_ + position_;
      return { begin_[position_] };
    }

    iterator_interface<Item>::item_ = nullptr;
    return std::nullopt;
  }

  template<typename Collection>
  [[nodiscard]] Collection collect()
  {
    return from_iterator_trait<typename Collection::iterator>::from_iter(*this);
  }

  template<typename Callable>
  [[nodiscard]] auto map(Callable &&callable)
  {
    return map_iterator<array_iterator<Item, N>, Callable>{ array_iterator<Item, N>{begin(), end()}, std::forward<Callable>(callable) };
  }

  [[nodiscard]] constexpr pointer begin() noexcept { return begin_; }

  [[nodiscard]] constexpr const_pointer cbegin() const noexcept { return begin_; }

  [[nodiscard]] constexpr pointer end() noexcept { return end_; }

  [[nodiscard]] constexpr const_pointer cend() const noexcept { return end_; }

  [[nodiscard]] constexpr value_type operator*() { return begin_[position_]; }

private:
  mutable size_type position_;
  pointer const begin_;
  pointer const end_;
};

}// namespace ftl
