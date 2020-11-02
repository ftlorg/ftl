
// Copyright Grzegorz Litarowicz and Lukasz Gut 2020 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <ftl/iterator_interface.hpp>
#include <ftl/iterator_member_provider.hpp>
#include <ftl/map_iterator.hpp>
#include <ftl/iterator_interface.hpp>
#include <forward_list>

namespace ftl {

template<typename Item>
class forward_list_container_iterator final
  : public iterator_interface<forward_list_container_iterator<Item>>
  , public container_iterator_member_provider<forward_list_container_iterator<Item>,
      typename std::iterator_traits<ftl::forward_list_container_iterator<Item>>::iterator_category> {

  friend container_iterator_member_provider<forward_list_container_iterator<Item>, std::forward_iterator_tag>;
  friend container_iterator_member_provider<forward_list_container_iterator<Item>, std::input_iterator_tag>;
  friend container_iterator_member_provider<forward_list_container_iterator<Item>>;
  friend iterator_interface<forward_list_container_iterator<Item>>;
  friend iterator_interface<forward_list_container_iterator<Item>>;

public:
  using difference_type = typename std::iterator_traits<ftl::forward_list_container_iterator<Item>>::difference_type;
  using value_type = typename std::iterator_traits<ftl::forward_list_container_iterator<Item>>::value_type;
  using pointer = typename std::iterator_traits<ftl::forward_list_container_iterator<Item>>::pointer;
  using reference = typename std::iterator_traits<ftl::forward_list_container_iterator<Item>>::reference;
  using const_pointer = typename std::iterator_traits<ftl::forward_list_container_iterator<Item>>::const_pointer;
  using const_reference = typename std::iterator_traits<ftl::forward_list_container_iterator<Item>>::const_reference;
  using iterator_category = typename std::iterator_traits<ftl::forward_list_container_iterator<Item>>::iterator_category;
  using size_type = typename std::iterator_traits<ftl::forward_list_container_iterator<Item>>::size_type;
  using std_forward_list_container_iterator =
    typename std::iterator_traits<ftl::forward_list_container_iterator<Item>>::std_forward_list_container_iterator;

  forward_list_container_iterator(std_forward_list_container_iterator begin, std_forward_list_container_iterator end)
    : current_{ begin }, begin_{ std::move(begin) }, end_{ std::move(end) } {
  }

  forward_list_container_iterator(std_forward_list_container_iterator current,
    std_forward_list_container_iterator begin,
    std_forward_list_container_iterator end)
    : current_{ current }, begin_{ std::move(begin) }, end_{ std::move(end) } {
  }

  constexpr forward_list_container_iterator() = default;

  constexpr operator forward_list_container_const_iterator<Item>() const {
    return { current_, begin_, end_ };
  }

private:
  mutable std_forward_list_container_iterator current_;
  std_forward_list_container_iterator begin_;
  std_forward_list_container_iterator end_;
};

}// namespace ftl