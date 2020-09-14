#pragma once

#include <ftl/iterator_interface.hpp>
#include <ftl/iterator_member_provider.hpp>
#include <ftl/map.hpp>

namespace ftl {

template<typename Key, typename T, typename Item = std::pair<const Key, T>>
class map_container_iterator final : public iterator_interface<map_container_iterator<Key, T>, Item, std::size_t> {

  friend iterator_interface<map_container_iterator<Key, T>, Item, std::size_t>;
  friend const_iterator_interface<map_container_iterator<Key, T>, Item, std::size_t>;
  friend iterator_member_provider<map_container_iterator<Key, T>, std::bidirectional_iterator_tag>;

public:
  using difference_type = typename std::map<Key, T>::difference_type;
  using value_type = typename std::map<Key, T>::value_type;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::bidirectional_iterator_tag;
  using size_type = std::size_t;
  using std_map_container_iterator = typename std::map<Key, T>::iterator;

  map_container_iterator(std_map_container_iterator begin, std_map_container_iterator end)
    : current_{ begin }, begin_{ begin }, end_{ end } {
  }

  map_container_iterator(std_map_container_iterator current,
    std_map_container_iterator begin,
    std_map_container_iterator end)
    : current_{ current }, begin_{ begin }, end_{ end } {
  }

// private:
  template<typename Collection>
  [[nodiscard]] auto collect_impl() -> Collection {
    return from_iterator_trait<map_container_iterator<Key, T>, Collection>::from_iter(*this);
  }

  [[nodiscard]] auto enumerate_impl() const -> enumerate_iterator<map_container_iterator<Key, T>> {
    return { *this };
  }

  template<typename NewCallable>
  [[nodiscard]] auto inspect_impl(NewCallable &&callable) const
    -> inspect_iterator<map_container_iterator<Key, T>, NewCallable> {
    return { *this, std::forward<NewCallable>(callable) };
  }

  template<typename Callable>
  [[nodiscard]] auto map_impl(Callable &&callable) -> map_iterator<map_container_iterator<Key, T>, Callable> {
    return { *this, std::forward<Callable>(callable) };
  }

  [[nodiscard]] constexpr auto count_impl() const -> size_type {
    return static_cast<size_type>(std::distance(begin_, end_));
  }

  [[nodiscard]] constexpr auto begin_impl() noexcept -> map_container_iterator<Key, T> {
    return { begin_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> map_container_iterator<Key, T> {
    return { begin_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto end_impl() noexcept -> map_container_iterator<Key, T> {
    return { end_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> map_container_iterator<Key, T> {
    return { end_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto deref_impl() -> reference {
    return *current_;
  }

  [[nodiscard]] constexpr auto const_deref_impl() const -> const_reference {
    return *current_;
  }

  auto preincrement_impl() -> map_container_iterator<Key, T> & {
    ++current_;

    return *this;
  }

  mutable std_map_container_iterator current_;
  std_map_container_iterator begin_;
  std_map_container_iterator end_;
};

}// namespace ftl
