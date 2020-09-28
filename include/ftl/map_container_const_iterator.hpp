#pragma once

#include <ftl/iterator_interface.hpp>
#include <ftl/iterator_member_provider.hpp>
#include <ftl/iterator_traits.hpp>
#include <ftl/map.hpp>
#include <iterator>

namespace ftl {

template<typename Key, typename T, typename Item = std::pair<const Key, T>>
class map_container_const_iterator final
  : public iterator_interface<map_container_const_iterator<Key, T>>
  , public container_iterator_member_provider<map_container_const_iterator<Key, T>,
      typename std::iterator_traits<ftl::map_container_const_iterator<Key, T>>::iterator_category> {

  friend container_iterator_member_provider<map_container_const_iterator<Key, T>, std::random_access_iterator_tag>;
  friend container_iterator_member_provider<map_container_const_iterator<Key, T>, std::bidirectional_iterator_tag>;
  friend container_iterator_member_provider<map_container_const_iterator<Key, T>, std::forward_iterator_tag>;
  friend container_iterator_member_provider<map_container_const_iterator<Key, T>, std::input_iterator_tag>;
  friend container_iterator_member_provider<map_container_const_iterator<Key, T>>;
  friend iterator_interface<map_container_const_iterator<Key, T>>;

public:
  using difference_type = typename std::iterator_traits<ftl::map_container_const_iterator<Key, T, Item>>::difference_type;
  using value_type = typename std::iterator_traits<ftl::map_container_const_iterator<Key, T, Item>>::value_type;
  using pointer = typename std::iterator_traits<ftl::map_container_const_iterator<Key, T, Item>>::pointer;
  using reference = typename std::iterator_traits<ftl::map_container_const_iterator<Key, T, Item>>::reference;
  using const_pointer = typename std::iterator_traits<ftl::map_container_const_iterator<Key, T, Item>>::const_pointer;
  using const_reference = typename std::iterator_traits<ftl::map_container_const_iterator<Key, T, Item>>::const_reference;
  using iterator_category =
    typename std::iterator_traits<ftl::map_container_const_iterator<Key, T, Item>>::iterator_category;
  using size_type = typename std::iterator_traits<ftl::map_container_const_iterator<Key, T, Item>>::size_type;
  using std_map_container_const_iterator =
    typename std::iterator_traits<ftl::map_container_const_iterator<Key, T, Item>>::std_map_container_const_iterator;

  map_container_const_iterator(std_map_container_const_iterator begin, std_map_container_const_iterator end)
    : current_{ begin }, begin_{ begin }, end_{ end } {
  }

  map_container_const_iterator(std_map_container_const_iterator current,
    std_map_container_const_iterator begin,
    std_map_container_const_iterator end)
    : current_{ current }, begin_{ begin }, end_{ end } {
  }

private:

  mutable std_map_container_const_iterator current_;
  std_map_container_const_iterator begin_;
  std_map_container_const_iterator end_;
};

}// namespace ftl
