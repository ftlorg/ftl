#pragma once
#include <iterator>
#include <vector>
#include <list>
#include <map>

namespace ftl {

template<typename Derived, typename Item, typename Size>
class iterator_interface;

template<typename Iter, typename Callable>
class map_iterator;

template<typename Iter, typename Callable>
class filter_iterator;

template<typename Iter>
class enumerate_iterator;

template<typename Iter, typename Callable>
class inspect_iterator;

template<typename Item>
class vector_container_const_iterator;

template<typename Item>
class vector_container_iterator;

template<typename Key, typename T, typename Item>
class map_container_iterator;

template<typename Key, typename T, typename Item>
class map_container_const_iterator;

template<typename Item>
class list_container_iterator;

template<typename Item>
class list_container_const_iterator;

template<typename Item, std::size_t N>
class array_container_const_iterator;

template<typename Item, std::size_t N>
class array_container_iterator;

}// namespace ftl

template<typename Item>
struct std::iterator_traits<ftl::vector_container_const_iterator<Item>> {
  using difference_type = std::ptrdiff_t;
  using value_type = typename std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::random_access_iterator_tag;
  using size_type = std::size_t;
  using std_vector_container_iterator = typename std::vector<value_type>::const_iterator;
};

template<typename Item>
struct std::iterator_traits<ftl::vector_container_iterator<Item>> {
  using difference_type = std::ptrdiff_t;
  using value_type = typename std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::random_access_iterator_tag;
  using size_type = std::size_t;
  using std_vector_container_iterator = typename std::vector<value_type>::iterator;
};

template<typename Iter, typename Callable>
struct std::iterator_traits<ftl::map_iterator<Iter, Callable>> {
  using difference_type = typename Iter::difference_type;
  using value_type = typename Iter::value_type;
  using pointer = typename Iter::pointer;
  using reference = typename Iter::reference;
  using const_pointer = typename Iter::const_pointer;
  using const_reference = typename Iter::const_reference;
  using inherited_iterator_category = typename Iter::iterator_category;
  using iterator_category = inherited_iterator_category;
  using size_type = typename Iter::size_type;
};

template<typename Key, typename T, typename Item>
struct std::iterator_traits<ftl::map_container_const_iterator<Key, T, Item>> {
  using difference_type = typename std::map<Key, T>::difference_type;
  using value_type = typename std::map<Key, T>::value_type;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::bidirectional_iterator_tag;
  using size_type = std::size_t;
  using std_map_container_const_iterator = typename std::map<Key, T>::const_iterator;
};

template<typename Item>
struct std::iterator_traits<ftl::list_container_iterator<Item>> {
  using difference_type = std::ptrdiff_t;
  using value_type = typename std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = typename ftl::list_container_iterator<Item>::iterator_category;
  using size_type = std::size_t;
  using std_list_container_iterator = typename std::list<value_type>::iterator;
};

template<typename Item>
struct std::iterator_traits<ftl::list_container_const_iterator<Item>> {
  using difference_type = std::ptrdiff_t;
  using value_type = typename std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = typename ftl::list_container_iterator<Item>::iterator_category;
  using size_type = std::size_t;
  using std_list_container_const_iterator = typename std::list<value_type>::const_iterator;
};


template<typename Iter, typename Callable>
struct std::iterator_traits<ftl::inspect_iterator<Iter, Callable>> {
  using difference_type = typename Iter::difference_type;
  using value_type = typename Iter::value_type;
  using pointer = typename Iter::pointer;
  using reference = typename Iter::reference;
  using const_pointer = typename Iter::const_pointer;
  using const_reference = typename Iter::const_reference;
  using inherited_iterator_category = typename Iter::iterator_category;
  using iterator_category = inherited_iterator_category;
  using size_type = typename Iter::size_type;
};

template<typename Iter, typename Callable>
struct std::iterator_traits<ftl::filter_iterator<Iter, Callable>> {
  using difference_type = typename Iter::difference_type;
  using value_type = typename Iter::value_type;
  using pointer = typename Iter::pointer;
  using reference = typename Iter::reference;
  using const_pointer = typename Iter::const_pointer;
  using const_reference = typename Iter::const_reference;
  using iterator_category = std::forward_iterator_tag;
  using inherited_iterator_category = typename Iter::iterator_category;
  using size_type = typename Iter::size_type;
};


template<typename Item, std::size_t N>
struct std::iterator_traits<ftl::array_container_const_iterator<Item, N>> {
  using difference_type = std::ptrdiff_t;
  using value_type = std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::random_access_iterator_tag;
  using std_array_container_iterator = typename std::array<value_type, N>::const_iterator;
  using size_type = std::size_t;
};

template<typename Item, std::size_t N>
struct std::iterator_traits<ftl::array_container_iterator<Item, N>> {
  using difference_type = std::ptrdiff_t;
  using value_type = std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::random_access_iterator_tag;
  using std_array_container_iterator = typename std::array<value_type, N>::iterator;
  using size_type = std::size_t;
};