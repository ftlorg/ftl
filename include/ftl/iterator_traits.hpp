
// Copyright Grzegorz Litarowicz and Lukasz Gut 2020 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <iterator>
#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <functional>
#include <ftl/is_container.hpp>

namespace ftl {

template<typename Iter, typename Callable>
class map_iterator;

template<typename Iter, typename Callable>
class filter_iterator;

template<typename Iter>
class enumerate_iterator;

template<typename Iter, bool is_container = ftl::is_container<typename std::iterator_traits<Iter>::value_type>::value>
class flatten_iterator;

template<typename Iter, typename Callable>
class inspect_iterator;

template<typename Iter>
class take_iterator;

template<typename Item>
class vector_container_const_iterator;

template<typename Item>
class vector_container_iterator;

template<typename Item>
class deque_container_const_iterator;

template<typename Item>
class deque_container_iterator;

template<typename Key, typename T, typename Item>
class map_container_iterator;

template<typename Key>
class set_container_iterator;

template<typename Key>
class set_container_const_iterator;

template<typename Key, typename T, typename Item>
class map_container_const_iterator;

template<typename Key, typename T, typename Item>
class unordered_map_container_iterator;

template<typename Key, typename T, typename Item>
class unordered_map_container_const_iterator;

template<typename Item>
class forward_list_container_iterator;

template<typename Item>
class forward_list_container_const_iterator;

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
  using std_vector_container_const_iterator = typename std::vector<value_type>::const_iterator;
};

template<typename Item>
struct std::iterator_traits<ftl::deque_container_iterator<Item>> {
  using difference_type = std::ptrdiff_t;
  using value_type = typename std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::random_access_iterator_tag;
  using size_type = std::size_t;
  using std_deque_container_iterator = typename std::deque<value_type>::iterator;
};

template<typename Item>
struct std::iterator_traits<ftl::deque_container_const_iterator<Item>> {
  using difference_type = std::ptrdiff_t;
  using value_type = typename std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::random_access_iterator_tag;
  using size_type = std::size_t;
  using std_deque_container_const_iterator = typename std::deque<value_type>::const_iterator;
};

template<typename Iter, typename Callable>
struct std::iterator_traits<ftl::map_iterator<Iter, Callable>> {
  using difference_type = typename Iter::difference_type;
  using value_type = typename std::invoke_result_t<Callable, typename Iter::value_type>;
  using pointer = typename Iter::pointer;
  using reference = typename Iter::reference;
  using const_pointer = typename Iter::const_pointer;
  using const_reference = typename Iter::const_reference;
  using inherited_iterator_category = typename Iter::iterator_category;
  using iterator_category = inherited_iterator_category;
  using size_type = typename Iter::size_type;
  using callable_t = std::function<value_type(typename Iter::value_type)>;
};

template<typename Key, typename T, typename Item>
struct std::iterator_traits<ftl::map_container_iterator<Key, T, Item>> {
  using difference_type = std::ptrdiff_t;
  using value_type = std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::bidirectional_iterator_tag;
  using std_map_container_iterator = typename std::map<Key, T, Item>::iterator;
  using size_type = std::size_t;
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
struct std::iterator_traits<ftl::forward_list_container_iterator<Item>> {
  using difference_type = std::ptrdiff_t;
  using value_type = typename std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::forward_iterator_tag;
  using size_type = std::size_t;
  using std_forward_list_container_iterator = typename std::forward_list<value_type>::iterator;
};

template<typename Item>
struct std::iterator_traits<ftl::forward_list_container_const_iterator<Item>> {
  using difference_type = std::ptrdiff_t;
  using value_type = typename std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::forward_iterator_tag;
  using size_type = std::size_t;
  using std_forward_list_container_const_iterator = typename std::forward_list<value_type>::const_iterator;
};

template<typename Item>
struct std::iterator_traits<ftl::list_container_iterator<Item>> {
  using difference_type = std::ptrdiff_t;
  using value_type = typename std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::bidirectional_iterator_tag;
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
  using iterator_category = std::bidirectional_iterator_tag;
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
  using callable_t = std::function<void(typename Iter::value_type)>;
};

template<typename Iter>
struct std::iterator_traits<ftl::enumerate_iterator<Iter>> {
  using difference_type = typename Iter::difference_type;
  using size_type = typename Iter::size_type;
  using value_type = typename std::tuple<size_type, typename Iter::value_type>;
  using pointer = typename Iter::pointer;
  using reference = typename Iter::reference;
  using const_pointer = typename Iter::const_pointer;
  using const_reference = typename Iter::const_reference;
  using inherited_iterator_category = typename Iter::iterator_category;
  using iterator_category = inherited_iterator_category;
};

template<typename Iter>
struct std::iterator_traits<ftl::flatten_iterator<Iter, false>> {
  using difference_type = typename Iter::difference_type;
  using size_type = typename Iter::size_type;
  using value_type = typename Iter::value_type;
  using pointer = typename Iter::pointer;
  using reference = typename Iter::reference;
  using const_pointer = typename Iter::const_pointer;
  using const_reference = typename Iter::const_reference;
  using inherited_iterator_category = std::forward_iterator_tag;
  using iterator_category = std::forward_iterator_tag;
};

template<typename Iter>
struct std::iterator_traits<ftl::flatten_iterator<Iter, true>> {
  using difference_type = typename Iter::difference_type;
  using size_type = typename Iter::size_type;
  using value_type =
    typename std::iterator_traits<ftl::flatten_iterator<typename Iter::value_type::ftl_iterator>>::value_type;
  using pointer = typename std::iterator_traits<ftl::flatten_iterator<typename Iter::value_type::ftl_iterator>>::pointer;
  using reference = typename std::iterator_traits<ftl::flatten_iterator<typename Iter::value_type::ftl_iterator>>::reference;
  using const_pointer =
    typename std::iterator_traits<ftl::flatten_iterator<typename Iter::value_type::ftl_iterator>>::const_pointer;
  using const_reference =
    typename std::iterator_traits<ftl::flatten_iterator<typename Iter::value_type::ftl_iterator>>::const_reference;
  using inherited_iterator_category = std::forward_iterator_tag;
  using iterator_category = std::forward_iterator_tag;
};

template<typename Iter>
struct std::iterator_traits<ftl::take_iterator<Iter>> {
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
  using callable_t = std::function<std::invoke_result_t<Callable, typename Iter::value_type>(typename Iter::value_type)>;
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

template<typename Item, std::size_t N>
struct std::iterator_traits<ftl::array_container_const_iterator<Item, N>> {
  using difference_type = std::ptrdiff_t;
  using value_type = std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::random_access_iterator_tag;
  using std_array_container_const_iterator = typename std::array<value_type, N>::const_iterator;
  using size_type = std::size_t;
};

template<typename Key>
struct std::iterator_traits<ftl::set_container_iterator<Key>> {
  using difference_type = std::ptrdiff_t;
  using value_type = std::remove_cv_t<Key>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::bidirectional_iterator_tag;
  using std_set_container_iterator = typename std::set<Key>::iterator;
  using size_type = std::size_t;
};

template<typename Key>
struct std::iterator_traits<ftl::set_container_const_iterator<Key>> {
  using difference_type = std::ptrdiff_t;
  using value_type = std::remove_cv_t<Key>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::bidirectional_iterator_tag;
  using std_set_container_const_iterator = typename std::set<Key>::const_iterator;
  using size_type = std::size_t;
};


template<typename Key, typename T, typename Item>
struct std::iterator_traits<ftl::unordered_map_container_iterator<Key, T, Item>> {
  using difference_type = std::ptrdiff_t;
  using value_type = std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::forward_iterator_tag;
  using std_unordered_map_container_iterator = typename std::unordered_map<Key, T>::iterator;
  using size_type = std::size_t;
};

template<typename Key, typename T, typename Item>
struct std::iterator_traits<ftl::unordered_map_container_const_iterator<Key, T, Item>> {
  using difference_type = std::ptrdiff_t;
  using value_type = std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator_category = std::forward_iterator_tag;
  using std_unordered_map_container_const_iterator = typename std::unordered_map<Key, T>::const_iterator;
  using size_type = std::size_t;
};