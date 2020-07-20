#pragma once

#include <ftl/iterator_interface.hpp>

namespace ftl {

template<typename Item>
class array_iterator final : public iterator_interface<Item>
{
public:
  using iterator_category = /* */ void;
  using value_type = std::remove_cv_t<Item>;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type *;
  using reference = value_type &;
  using size_type = std::size_t;

  array_iterator(pointer const begin, pointer const end) : iterator_interface<Item>{ begin }, position_{ 0 }, begin_{ begin }, end_{ end } {}

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

private:
  mutable size_type position_;
  pointer const begin_;
  pointer const end_;
};

}// namespace ftl
