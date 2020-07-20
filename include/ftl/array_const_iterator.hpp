#pragma once

#include <ftl/iterator_interface.hpp>

namespace ftl {

template<typename Item>
class array_const_iterator : public const_iterator_interface<Item>
{
public:
  using iterator_category = /* */ void;
  using value_type = std::remove_cv_t<Item>;
  using difference_type = std::ptrdiff_t;
  using pointer = const value_type *;
  using reference = const value_type &;
  using size_type = std::size_t;

  array_const_iterator(pointer const begin, pointer const end) : position_{ 0 }, begin_{ begin }, end_{ end } {}

  [[nodiscard]] std::optional<Item> next() const override
  {
    ++position_;

    if (begin_ + position_ != end_)
      return { begin_[position_] };

    return std::nullopt;
  }

private:
  mutable size_type position_;
  const value_type *const begin_;
  const value_type *const end_;
};

}// namespace ftl
