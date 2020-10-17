#pragma once
#include <cstddef>

namespace ftl {

template<typename T, std::size_t N>
class array;

template<typename T, typename Allocator>
class vector;

template<typename T>
struct is_container {
  static constexpr bool value = false;
};

template<typename T, std::size_t N>
struct is_container<ftl::array<T, N>> {
  static constexpr bool value = true;
};

template<typename T, typename Allocator>
struct is_container<ftl::vector<T, Allocator>> {
  static constexpr bool value = true;
};

template<typename T>
struct contains_container {
  static constexpr bool value = false;
};

template<typename T, std::size_t N>
struct contains_container<ftl::array<T, N>> {
  static constexpr bool value = is_container<T>::value;
};

template<typename T, typename Allocator>
struct contains_container<ftl::vector<T, Allocator>> {
  static constexpr bool value = is_container<T>::value;
};



}// namespace ftl