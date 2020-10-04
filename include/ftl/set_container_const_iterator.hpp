#pragma once

#include <ftl/container_iterator_member_provider.hpp>
#include <ftl/iterator_traits.hpp>
#include <ftl/iterator_interface.hpp>

namespace ftl {

template<typename Key>
class set_container_const_iterator final
  : public iterator_interface<set_container_const_iterator<Key>>
  , public container_iterator_member_provider<set_container_const_iterator<Key>,
      typename std::iterator_traits<set_container_const_iterator<Key>>::iterator_category> {

  friend container_iterator_member_provider<set_container_const_iterator<Key>, std::random_access_iterator_tag>;
  friend container_iterator_member_provider<set_container_const_iterator<Key>, std::bidirectional_iterator_tag>;
  friend container_iterator_member_provider<set_container_const_iterator<Key>, std::forward_iterator_tag>;
  friend container_iterator_member_provider<set_container_const_iterator<Key>, std::input_iterator_tag>;
  friend container_iterator_member_provider<set_container_const_iterator<Key>>;
  friend iterator_interface<set_container_const_iterator<Key>>;

public:
  using difference_type = typename std::iterator_traits<ftl::set_container_const_iterator<Key>>::difference_type;
  using value_type = typename std::iterator_traits<ftl::set_container_const_iterator<Key>>::value_type;
  using pointer = typename std::iterator_traits<ftl::set_container_const_iterator<Key>>::pointer;
  using reference = typename std::iterator_traits<ftl::set_container_const_iterator<Key>>::reference;
  using const_pointer = typename std::iterator_traits<ftl::set_container_const_iterator<Key>>::const_pointer;
  using const_reference = typename std::iterator_traits<ftl::set_container_const_iterator<Key>>::const_reference;
  using iterator_category = typename std::iterator_traits<ftl::set_container_const_iterator<Key>>::iterator_category;
  using size_type = typename std::iterator_traits<ftl::set_container_const_iterator<Key>>::size_type;
  using std_set_container_const_iterator =
    typename std::iterator_traits<ftl::set_container_const_iterator<Key>>::std_set_container_const_iterator;

  set_container_const_iterator(std_set_container_const_iterator begin, std_set_container_const_iterator end)
    : current_{ begin }, begin_{ begin }, end_{ end } {
  }

  set_container_const_iterator(std_set_container_const_iterator current,
    std_set_container_const_iterator begin,
    std_set_container_const_iterator end)
    : current_{ current }, begin_{ begin }, end_{ end } {
  }

private:
  mutable std_set_container_const_iterator current_;
  std_set_container_const_iterator begin_;
  std_set_container_const_iterator end_;
};

}// namespace ftl