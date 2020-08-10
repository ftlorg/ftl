#pragma once
#include <iterator>
#include "iterator_interface.hpp"

namespace ftl {

template<typename Item, typename Allocator = std::allocator<Item>>
class vector_const_iterator final
  : public const_iterator_interface<vector_const_iterator<Item, Allocator>, Item, std::size_t> {

  friend const_iterator_interface<vector_const_iterator<Item, Allocator>, Item, std::size_t>;

public:
  using difference_type = std::ptrdiff_t;
  using value_type = typename std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::random_access_iterator_tag;
  using size_type = std::size_t;
  using std_vector_iterator = typename std::vector<value_type, Allocator>::const_iterator;

  constexpr vector_const_iterator() = default;
  constexpr vector_const_iterator(std_vector_iterator begin, std_vector_iterator end)
    : begin_{ std::move(begin) }, end_{ std::move(end) } {
  }

  [[nodiscard]] auto next_impl() const -> std::optional<value_type> {
    if (++begin_ != end_) { return { *begin_ }; }

    return std::nullopt;
  }

private:
  mutable std_vector_iterator begin_;
  std_vector_iterator end_;
};

}// namespace ftl