#pragma once
#include <iterator>

namespace ftl {

template<typename Item, typename Allocator = std::allocator<Item>>
class vector_iterator final : public iterator_interface<vector_iterator<Item, Allocator>, Item, std::size_t> {

  friend iterator_interface<vector_iterator<Item, Allocator>, Item, std::size_t>;

public:
  using difference_type = std::ptrdiff_t;
  using value_type = typename std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::random_access_iterator_tag;
  using size_type = std::size_t;
  using std_vector_iterator = typename std::vector<value_type, Allocator>::iterator;

  constexpr vector_iterator() = default;
  constexpr vector_iterator(std_vector_iterator begin, std_vector_iterator end) : begin_{ std::move(begin) }, end_{ std::move(end) } {
  }

  [[nodiscard]] auto next_impl() -> std::optional<value_type> {
    if (++begin_ != end_) { return { *begin_ }; }

    return std::nullopt;
  }

  template<typename Collection>
  [[nodiscard]] auto collect_impl() -> Collection {
    return from_iterator_trait<vector<Item, Allocator>, Collection>::from_iter(*this);
  }

private:
  std_vector_iterator begin_;
  std_vector_iterator end_;
};

}// namespace ftl
