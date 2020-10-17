
// Copyright Grzegorz Litarowicz and Lukasz Gut 2020 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <ftl/iterator_interface.hpp>
#include <ftl/iterator_member_provider.hpp>
#include <ftl/iterator_traits.hpp>

namespace ftl {

template<typename Item>
class vector_container_iterator final
  : public iterator_interface<vector_container_iterator<Item>>
  , public container_iterator_member_provider<vector_container_iterator<Item>,
      typename std::iterator_traits<ftl::vector_container_iterator<Item>>::iterator_category> {

  friend container_iterator_member_provider<vector_container_iterator<Item>, std::random_access_iterator_tag>;
  friend container_iterator_member_provider<vector_container_iterator<Item>, std::bidirectional_iterator_tag>;
  friend container_iterator_member_provider<vector_container_iterator<Item>, std::forward_iterator_tag>;
  friend container_iterator_member_provider<vector_container_iterator<Item>, std::input_iterator_tag>;
  friend container_iterator_member_provider<vector_container_iterator<Item>>;
  friend iterator_interface<vector_container_iterator<Item>>;

public:
  using difference_type = typename std::iterator_traits<ftl::vector_container_iterator<Item>>::difference_type;
  using value_type = typename std::iterator_traits<ftl::vector_container_iterator<Item>>::value_type;
  using pointer = typename std::iterator_traits<ftl::vector_container_iterator<Item>>::pointer;
  using reference = typename std::iterator_traits<ftl::vector_container_iterator<Item>>::reference;
  using const_pointer = typename std::iterator_traits<ftl::vector_container_iterator<Item>>::const_pointer;
  using const_reference = typename std::iterator_traits<ftl::vector_container_iterator<Item>>::const_reference;
  using iterator_category = typename std::iterator_traits<ftl::vector_container_iterator<Item>>::iterator_category;
  using size_type = typename std::iterator_traits<ftl::vector_container_iterator<Item>>::size_type;
  using std_vector_container_iterator =
    typename std::iterator_traits<ftl::vector_container_iterator<Item>>::std_vector_container_iterator;

  constexpr vector_container_iterator(std_vector_container_iterator current, std_vector_container_iterator begin,
    std_vector_container_iterator end)
    : current_{ std::move(current) }, begin_{ std::move(begin) }, end_{ std::move(end) } {
  }

  vector_container_iterator() = default;

private:

  mutable std_vector_container_iterator current_;
  std_vector_container_iterator begin_;
  std_vector_container_iterator end_;
};

}// namespace ftl
