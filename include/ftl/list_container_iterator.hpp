#pragma once

#include <ftl/iterator_interface.hpp>
#include <ftl/iterator_member_provider.hpp>
#include <ftl/map_iterator.hpp>
#include <ftl/iterator_interface.hpp>
#include <list>

namespace ftl {

template<typename Item>
class list_container_iterator final
  : public iterator_interface<list_container_iterator<Item>, Item, std::size_t>
  , public container_iterator_member_provider<list_container_iterator<Item>,
      typename std::iterator_traits<ftl::list_container_iterator<Item>>::iterator_category> {

  friend container_iterator_member_provider<list_container_iterator<Item>, std::random_access_iterator_tag>;
  friend container_iterator_member_provider<list_container_iterator<Item>, std::bidirectional_iterator_tag>;
  friend container_iterator_member_provider<list_container_iterator<Item>, std::forward_iterator_tag>;
  friend container_iterator_member_provider<list_container_iterator<Item>, std::input_iterator_tag>;
  friend container_iterator_member_provider<list_container_iterator<Item>>;
  friend const_iterator_interface<list_container_iterator<Item>, Item, std::size_t>;
  friend iterator_interface<list_container_iterator<Item>, Item, std::size_t>;

public:
  using difference_type = typename std::iterator_traits<ftl::list_container_iterator<Item>>::difference_type;
  using value_type = typename std::iterator_traits<ftl::list_container_iterator<Item>>::value_type;
  using pointer = typename std::iterator_traits<ftl::list_container_iterator<Item>>::pointer;
  using reference = typename std::iterator_traits<ftl::list_container_iterator<Item>>::reference;
  using const_pointer = typename std::iterator_traits<ftl::list_container_iterator<Item>>::const_pointer;
  using const_reference = typename std::iterator_traits<ftl::list_container_iterator<Item>>::const_reference;
  using iterator_category = typename std::iterator_traits<ftl::list_container_iterator<Item>>::iterator_category;
  using size_type = typename std::iterator_traits<ftl::list_container_iterator<Item>>::size_type;
  using std_list_container_iterator =
    typename std::iterator_traits<ftl::list_container_iterator<Item>>::std_list_container_iterator;

  list_container_iterator(std_list_container_iterator begin, std_list_container_iterator end)
    : current_{ begin }, begin_{ begin }, end_{ end } {
  }

  list_container_iterator(std_list_container_iterator current,
    std_list_container_iterator begin,
    std_list_container_iterator end)
    : current_{ current }, begin_{ begin }, end_{ end } {
  }

private:
  [[nodiscard]] constexpr auto count_impl() const -> size_type {
    return static_cast<size_type>(std::distance(begin_, end_));
  }

  [[nodiscard]] constexpr auto begin_impl() noexcept -> list_container_iterator<Item> {
    return { begin_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto begin_impl() const noexcept -> list_container_iterator<Item> {
    return cbegin_impl();
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> list_container_iterator<Item> {
    return { begin_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto end_impl() noexcept -> list_container_iterator<Item> {
    return { end_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto end_impl() const noexcept -> list_container_iterator<Item> {
    return cend_impl();
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> list_container_iterator<Item> {
    return { end_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto deref_impl() -> reference {
    return *current_;
  }

  [[nodiscard]] constexpr auto const_deref_impl() const -> const_reference {
    return *current_;
  }

  auto preincrement_impl() -> list_container_iterator<Item> & {
    ++current_;

    return *this;
  }

  auto const_preincrement_impl() const -> const list_container_iterator<Item> & {
    ++current_;

    return *this;
  }

  mutable std_list_container_iterator current_;
  std_list_container_iterator begin_;
  std_list_container_iterator end_;
};

}// namespace ftl