#pragma once

#include <ftl/iterator_interface.hpp>
#include <ftl/enumerate_iterator.hpp>
#include <ftl/map_iterator.hpp>
#include <ftl/inspect_iterator.hpp>
#include <ftl/container_iterator_member_provider.hpp>

namespace ftl {

template<typename Item, std::size_t N>
class array_container_iterator final
  : public iterator_interface<array_container_iterator<Item, N>, Item, std::size_t>
  , public container_iterator_member_provider<array_container_iterator<Item, N>, std::random_access_iterator_tag> {

  friend iterator_interface<array_container_iterator<Item, N>, Item, std::size_t>;
  friend const_iterator_interface<array_container_iterator<Item, N>, Item, std::size_t>;

public:
  using difference_type = typename std::iterator_traits<ftl::array_container_iterator<Item, N>>::difference_type;
  using value_type = typename std::iterator_traits<ftl::array_container_iterator<Item, N>>::value_type;
  using pointer = typename std::iterator_traits<ftl::array_container_iterator<Item, N>>::pointer;
  using reference = typename std::iterator_traits<ftl::array_container_iterator<Item, N>>::reference;
  using const_pointer = typename std::iterator_traits<ftl::array_container_iterator<Item, N>>::const_pointer;
  using const_reference = typename std::iterator_traits<ftl::array_container_iterator<Item, N>>::const_reference;
  using iterator_category = typename std::iterator_traits<ftl::array_container_iterator<Item, N>>::iterator_category;
  using size_type = typename std::iterator_traits<ftl::array_container_iterator<Item, N>>::size_type;
  using std_array_container_iterator =
    typename std::iterator_traits<ftl::array_container_iterator<Item, N>>::std_array_container_iterator;

  constexpr array_container_iterator(std_array_container_iterator begin, std_array_container_iterator end)
    : current_{ begin }, begin_{ begin }, end_{ end } {
  }

  constexpr array_container_iterator(std_array_container_iterator current,
    std_array_container_iterator begin,
    std_array_container_iterator end)
    : current_{ current }, begin_{ begin }, end_{ end } {
  }

  // private:

  [[nodiscard]] constexpr auto count_impl() const -> size_type {
    return static_cast<size_type>(end_ - begin_);
  }

  [[nodiscard]] constexpr auto begin_impl() noexcept -> array_container_iterator<Item, N> {
    return { begin_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto begin_impl() const noexcept -> array_container_iterator<Item, N> {
    return cbegin_impl();
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> array_container_iterator<Item, N> {
    return { begin_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto end_impl() noexcept -> array_container_iterator<Item, N> {
    return { end_, begin_, end_ };
  }

  [[nodiscard]] constexpr auto end_impl() const noexcept -> array_container_iterator<Item, N> {
    return cend_impl();
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> array_container_iterator<Item, N> {
    return { end_, begin_, end_ };
  }

  auto preincrement_impl() -> array_container_iterator<Item, N> & {
    ++current_;

    return *current_;
  }

  auto const_preincrement_impl() const -> const array_container_iterator<Item, N> & {
    ++current_;

    return *current_;
  }

  mutable std_array_container_iterator current_;
  std_array_container_iterator begin_;
  std_array_container_iterator end_;
};

}// namespace ftl
