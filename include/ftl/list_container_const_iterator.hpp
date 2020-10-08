#pragma once

#include <ftl/iterator_interface.hpp>
#include <ftl/iterator_member_provider.hpp>
#include <ftl/map_iterator.hpp>
#include <list>

namespace ftl {

template<typename Item>
class list_container_const_iterator final
  : public iterator_interface<list_container_const_iterator<Item>>
  , public container_iterator_member_provider<list_container_const_iterator<Item>,
      typename std::iterator_traits<ftl::list_container_const_iterator<Item>>::iterator_category> {

  friend container_iterator_member_provider<list_container_const_iterator<Item>, std::random_access_iterator_tag>;
  friend container_iterator_member_provider<list_container_const_iterator<Item>, std::bidirectional_iterator_tag>;
  friend container_iterator_member_provider<list_container_const_iterator<Item>, std::forward_iterator_tag>;
  friend container_iterator_member_provider<list_container_const_iterator<Item>, std::input_iterator_tag>;
  friend container_iterator_member_provider<list_container_const_iterator<Item>>;
  friend iterator_interface<list_container_const_iterator<Item>>;

public:
  using difference_type = typename std::iterator_traits<ftl::list_container_const_iterator<Item>>::difference_type;
  using value_type = typename std::iterator_traits<ftl::list_container_const_iterator<Item>>::value_type;
  using pointer = typename std::iterator_traits<ftl::list_container_const_iterator<Item>>::pointer;
  using reference = typename std::iterator_traits<ftl::list_container_const_iterator<Item>>::reference;
  using const_pointer = typename std::iterator_traits<ftl::list_container_const_iterator<Item>>::const_pointer;
  using const_reference = typename std::iterator_traits<ftl::list_container_const_iterator<Item>>::const_reference;
  using iterator_category = typename std::iterator_traits<ftl::list_container_const_iterator<Item>>::iterator_category;
  using size_type = typename std::iterator_traits<ftl::list_container_const_iterator<Item>>::size_type;
  using std_list_container_const_iterator =
    typename std::iterator_traits<ftl::list_container_const_iterator<Item>>::std_list_container_const_iterator;

  list_container_const_iterator(std_list_container_const_iterator begin, std_list_container_const_iterator end)
    : current_{ begin }, begin_{ std::move(begin) }, end_{ std::move(end) } {
  }

  list_container_const_iterator(std_list_container_const_iterator current,
    std_list_container_const_iterator begin,
    std_list_container_const_iterator end)
    : current_{ current }, begin_{ std::move(begin) }, end_{ std::move(end) } {
  }

private:
  mutable std_list_container_const_iterator current_;
  std_list_container_const_iterator begin_;
  std_list_container_const_iterator end_;
};

}// namespace ftl
