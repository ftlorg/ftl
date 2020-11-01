#pragma once
#include <cstddef>

namespace ftl {

enum class flatten_level { zero, one, two_or_more };

template<typename T, std::size_t N>
class array;

template<typename T, typename Allocator>
class vector;

template<typename T, typename Allocator>
class deque;

template<typename T, typename Allocator>
class list;

template<typename T, typename Allocator>
class forward_list;

template<class Key, class T, class Compare, class Allocator>
class map;

template<class Key, class Compare, class Allocator>
class set;

template<typename Key, typename T, typename Hash, typename KeyEqual, typename Allocator>
class unordered_map;

template<typename T>
struct is_container {
  static constexpr bool value = false;
};

template<typename Key, typename T, typename Hash, typename KeyEqual, typename Allocator>
struct is_container<ftl::unordered_map<Key, T, Hash, KeyEqual, Allocator>> {
  static constexpr bool value = true;
};

template<class Key, class Compare, class Allocator>
struct is_container<ftl::set<Key, Compare, Allocator>> {
  static constexpr bool value = true;
};

template<typename T, std::size_t N>
struct is_container<ftl::array<T, N>> {
  static constexpr bool value = true;
};

template<typename T, typename Allocator>
struct is_container<ftl::vector<T, Allocator>> {
  static constexpr bool value = true;
};

template<typename T, typename Allocator>
struct is_container<ftl::deque<T, Allocator>> {
  static constexpr bool value = true;
};

template<typename T, typename Allocator>
struct is_container<ftl::list<T, Allocator>> {
  static constexpr bool value = true;
};

template<typename T, typename Allocator>
struct is_container<ftl::forward_list<T, Allocator>> {
  static constexpr bool value = true;
};

template<class Key, class T, class Compare, class Allocator>
struct is_container<ftl::map<Key, T, Compare, Allocator>> {
  static constexpr bool value = true;
};

enum class level { zero, one, two };

template<typename T>
struct contains_container {
  static constexpr level value = level::zero;
};

template<typename T, std::size_t N>
struct contains_container<ftl::array<T, N>> {
  static constexpr level value = is_container<T>::value ? level::two : level::one;
};

template<typename T, typename Allocator>
struct contains_container<ftl::vector<T, Allocator>> {
  static constexpr level value = is_container<T>::value ? level::two : level::one;
};

template<typename T, typename Allocator>
struct contains_container<ftl::deque<T, Allocator>> {
  static constexpr level value = is_container<T>::value ? level::two : level::one;
};

template<typename T, typename Allocator>
struct contains_container<ftl::list<T, Allocator>> {
  static constexpr level value = is_container<T>::value ? level::two : level::one;
};

template<typename T, typename Allocator>
struct contains_container<ftl::forward_list<T, Allocator>> {
  static constexpr level value = is_container<T>::value ? level::two : level::one;
};

template<class Key, class T, class Compare, class Allocator>
struct contains_container<ftl::map<Key, T, Compare, Allocator>> {
  static constexpr level value = is_container<T>::value ? level::two : level::one;
};

template<class Key, class Compare, class Allocator>
struct contains_container<ftl::set<Key, Compare, Allocator>> {
  static constexpr level value = is_container<Key>::value ? level::two : level::one;
};

template<typename Key, typename T, typename Hash, typename KeyEqual, typename Allocator>
struct contains_container<ftl::unordered_map<Key, T, Hash, KeyEqual, Allocator>> {
  static constexpr level value = is_container<T>::value ? level::two : level::one;
};

}// namespace ftl