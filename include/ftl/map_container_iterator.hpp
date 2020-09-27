#pragma once

#include <ftl/iterator_interface.hpp>
#include <ftl/iterator_member_provider.hpp>
#include <ftl/map.hpp>

namespace ftl {

template<typename Key, typename T, typename Item = std::pair<const Key, T>>
class map_container_iterator final
  : public iterator_interface<map_container_iterator<Key, T>, Item, std::size_t>
  , public container_iterator_member_provider<map_container_iterator<Key, T>,
      typename std::iterator_traits<ftl::map_container_iterator<Key, T>>::iterator_category> {

  friend container_iterator_member_provider<map_container_iterator<Key, T>, std::random_access_iterator_tag>;
  friend container_iterator_member_provider<map_container_iterator<Key, T>, std::bidirectional_iterator_tag>;
  friend container_iterator_member_provider<map_container_iterator<Key, T>, std::forward_iterator_tag>;
  friend container_iterator_member_provider<map_container_iterator<Key, T>, std::input_iterator_tag>;
  friend container_iterator_member_provider<map_container_iterator<Key, T>>;
  friend const_iterator_interface<map_container_iterator<Key, T>, Item, std::size_t>;

  friend iterator_interface<map_container_iterator<Key, T>, Item, std::size_t>;
  friend const_iterator_interface<map_container_iterator<Key, T>, Item, std::size_t>;
  friend iterator_member_provider<map_container_iterator<Key, T>, std::bidirectional_iterator_tag>;

public:
  using difference_type = typename std::iterator_traits<ftl::map_container_iterator<Key, T, Item>>::difference_type;
  using value_type = typename std::iterator_traits<ftl::map_container_iterator<Key, T, Item>>::value_type;
  using pointer = typename std::iterator_traits<ftl::map_container_iterator<Key, T, Item>>::pointer;
  using reference = typename std::iterator_traits<ftl::map_container_iterator<Key, T, Item>>::reference;
  using const_pointer = typename std::iterator_traits<ftl::map_container_iterator<Key, T, Item>>::const_pointer;
  using const_reference = typename std::iterator_traits<ftl::map_container_iterator<Key, T, Item>>::const_reference;
  using iterator_category = typename std::iterator_traits<ftl::map_container_iterator<Key, T, Item>>::iterator_category;
  using size_type = typename std::iterator_traits<ftl::map_container_iterator<Key, T, Item>>::size_type;
  using std_map_container_iterator =
    typename std::iterator_traits<ftl::map_container_iterator<Key, T, Item>>::std_map_container_iterator;

  map_container_iterator(std_map_container_iterator begin, std_map_container_iterator end)
    : current_{ begin }, begin_{ begin }, end_{ end } {
  }

  map_container_iterator(std_map_container_iterator current,
    std_map_container_iterator begin,
    std_map_container_iterator end)
    : current_{ current }, begin_{ begin }, end_{ end } {
  }

private:
  [[nodiscard]] constexpr auto count_impl() const -> size_type {
    return static_cast<size_type>(std::distance(begin_, end_));
  }

  [[nodiscard]] constexpr auto begin_impl() noexcept -> map_container_iterator<Key, T> {
    return { begin_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto begin_impl() const noexcept -> map_container_iterator<Key, T> {
    return cbegin_impl();
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> map_container_iterator<Key, T> {
    return { begin_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto end_impl() noexcept -> map_container_iterator<Key, T> {
    return { end_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto end_impl() const noexcept -> map_container_iterator<Key, T> {
    return cend_impl();
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

  auto const_preincrement_impl() const -> const map_container_iterator<Key, T> & {
    ++current_;

    return *this;
  }

  mutable std_map_container_iterator current_;
  std_map_container_iterator begin_;
  std_map_container_iterator end_;
};

}// namespace ftl
