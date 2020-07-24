#pragma once

#include <ftl/iterator.hpp>

namespace ftl {

template<typename Item, std::size_t N>
class array_const_iterator final : public const_iterator_interface<Item>
{
public:
  using iterator_category = /* */ void;
  using value_type = std::remove_cv_t<Item>;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using reference = value_type &;
  using const_reference = value_type &;
  using size_type = std::size_t;
  constexpr static size_type size = N;

  constexpr array_const_iterator(const_pointer const begin, const_pointer const end) : position_{ 0 }, begin_{ begin }, end_{ end } {}

  [[nodiscard]] std::optional<value_type> next() const override
  {
    ++position_;

    if (begin_ + position_ != end_) {
      return { begin_[position_] };
    }

    return std::nullopt;
  }

  template<typename Collection>
  [[nodiscard]] Collection collect() const
  {
    return from_iterator_trait<array_const_iterator, Collection>::from_iter(*this);
  }

  [[nodiscard]] constexpr const_pointer begin() const noexcept { return begin_; }

  [[nodiscard]] constexpr const_pointer cbegin() const noexcept { return begin_; }

  [[nodiscard]] constexpr const_pointer end() const noexcept { return end_; }

  [[nodiscard]] constexpr const_pointer cend() const noexcept { return end_; }

private:
  mutable size_type position_;
  const_pointer const begin_;
  const_pointer const end_;
};

}// namespace ftl
