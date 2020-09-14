#pragma once

#include <ftl/iterator_interface.hpp>
#include <ftl/iterator_member_provider.hpp>
#include <iterator>

namespace ftl {

template<typename Item>
class vector_container_iterator final
  : public iterator_interface<vector_container_iterator<Item>, Item, std::size_t>
  , public iterator_member_provider<vector_container_iterator<Item>, std::random_access_iterator_tag> {

  friend iterator_interface<vector_container_iterator<Item>, Item, std::size_t>;
  friend const_iterator_interface<vector_container_iterator<Item>, Item, std::size_t>;
  friend iterator_member_provider<vector_container_iterator<Item>, std::random_access_iterator_tag>;

public:
  using difference_type = std::ptrdiff_t;
  using value_type = typename std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::random_access_iterator_tag;
  using size_type = std::size_t;
  using std_vector_container_iterator = typename std::vector<value_type>::iterator;

  constexpr vector_container_iterator(std_vector_container_iterator begin, std_vector_container_iterator end)
    : current_{ begin }, begin_{ std::move(begin) }, end_{ std::move(end) } {
  }

  // private:
  template<typename Collection>
  [[nodiscard]] auto collect_impl() -> Collection {
    return from_iterator_trait<vector_container_iterator<Item>, Collection>::from_iter(*this);
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> vector_container_iterator<Item> {
    return { begin_, end_ };
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> vector_container_iterator<Item> {
    return { end_, end_ };
  }

  [[nodiscard]] constexpr auto begin_impl() const noexcept -> vector_container_iterator<Item> {
    return { begin_, end_ };
  }

  [[nodiscard]] constexpr auto end_impl() const noexcept -> vector_container_iterator<Item> {
    return { end_, end_ };
  }

  [[nodiscard]] constexpr auto deref_impl() -> reference {
    return *current_;
  }

  [[nodiscard]] constexpr auto const_deref_impl() const -> const_reference {
    return *current_;
  }

  auto preincrement_impl() const -> const vector_container_iterator<Item> & {
    ++current_;
    return *this;
  }

  auto predecrement_impl() const -> vector_container_iterator<Item> & {
    --current_;
    return *this;
  }

  [[nodiscard]] constexpr auto count_impl() const -> size_type {
    return static_cast<size_type>(end_ - begin_);
  }

  template<typename Callable>
  [[nodiscard]] auto map_impl(Callable &&callable) const -> map_iterator<vector_container_iterator<Item>, Callable> {
    return { *this, std::forward<Callable>(callable) };
  }

  template<typename Callable>
  [[nodiscard]] auto filter_impl(Callable &&callable) const -> filter_iterator<vector_container_iterator<Item>, Callable> {
    return { *this, std::forward<Callable>(callable) };
  }

  mutable std_vector_container_iterator current_;
  std_vector_container_iterator begin_;
  std_vector_container_iterator end_;
};

}// namespace ftl

template<typename Item>
struct std::iterator_traits<ftl::vector_container_iterator<Item>> {
  using difference_type = typename ftl::vector_container_iterator<Item>::difference_type;
  using value_type = typename ftl::vector_container_iterator<Item>::value_type;
  using pointer = typename ftl::vector_container_iterator<Item>::pointer;
  using reference = typename ftl::vector_container_iterator<Item>::reference;
  using iterator_category = typename ftl::vector_container_iterator<Item>::iterator_category;
};
