#pragma once

#include <ftl/iterator_interface.hpp>

namespace ftl {

template<typename Item>
class array_reverse_iterator final : public iterator_interface<Item>
{
public:
  using iterator_category = /* */ void;
  using value_type = std::remove_cv_t<Item>;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type *;
  using reference = value_type &;
  using size_type = std::size_t;

  array_reverse_iterator(pointer const rbegin, pointer const rend) : position_{ std::distance(rbegin, rend) }, rbegin_{ rbegin }, rend_{ rend } {}

  [[nodiscard]] virtual std::optional<value_type> next() override
  {
    --position_;

    if (rbegin_ + position_ != rend_)
      return { rbegin_[position_] };

    return std::nullopt;
  }

private:
  mutable size_type position_;
  value_type *const rbegin_;
  value_type *const rend_;
};

}// namespace ftl
