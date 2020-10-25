
// Copyright Grzegorz Litarowicz and Lukasz Gut 2020 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <ftl/iterator_interface.hpp>
#include <ftl/container_iterator_member_provider.hpp>
#include <ftl/array_container_const_iterator.hpp>

namespace ftl {

template<typename Item, std::size_t N>
class array_container_iterator final
  : public iterator_interface<array_container_iterator<Item, N>>
  , public container_iterator_member_provider<array_container_iterator<Item, N>, std::random_access_iterator_tag> {

  friend container_iterator_member_provider<array_container_iterator<Item, N>, std::random_access_iterator_tag>;
  friend container_iterator_member_provider<array_container_iterator<Item, N>, std::bidirectional_iterator_tag>;
  friend container_iterator_member_provider<array_container_iterator<Item, N>, std::forward_iterator_tag>;
  friend container_iterator_member_provider<array_container_iterator<Item, N>, std::input_iterator_tag>;
  friend container_iterator_member_provider<array_container_iterator<Item, N>>;
  friend iterator_interface<array_container_iterator<Item, N>>;

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

  constexpr array_container_iterator() = default;

  constexpr operator array_container_const_iterator<Item, N>() const {
    return { current_, begin_, end_ };
  }

private:
  mutable std_array_container_iterator current_;
  std_array_container_iterator begin_;
  std_array_container_iterator end_;
};

}// namespace ftl
