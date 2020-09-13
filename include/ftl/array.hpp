#pragma once

#include <algorithm>
#include <array>

#include <ftl/array_container_iterator.hpp>
#include <ftl/array_container_const_iterator.hpp>
#include <ftl/from_iterator_trait.hpp>
#include <ftl/into_iterator_trait.hpp>

namespace ftl {

template<typename T, std::size_t N>
class array : public std::array<T, N> {
public:
  using value_type = typename std::array<T, N>::value_type;
  using size_type = typename std::array<T, N>::size_type;
  using difference_type = typename std::array<T, N>::difference_type;
  using pointer = typename std::array<T, N>::pointer;
  using reference = typename std::array<T, N>::reference;
  using const_pointer = typename std::array<T, N>::const_pointer;
  using const_reference = typename std::array<T, N>::const_reference;
  using ftl_iterator = array_container_iterator<T, N>;
  using ftl_const_iterator = array_container_const_iterator<T, N>;
  using iterator = typename std::array<T, N>::iterator;
  using const_iterator = typename std::array<T, N>::const_iterator;
  using reverse_iterator = typename std::array<T, N>::reverse_iterator;
  using const_reverse_iterator = typename std::array<T, N>::const_reverse_iterator;

  [[nodiscard]] auto iter() noexcept -> ftl_iterator {
    return into_iterator_trait<array<T, N>, ftl_iterator>::into_iter(*this);
  }

  [[nodiscard]] auto iter() const noexcept -> ftl_const_iterator {
    return into_iterator_trait<array<T, N>, ftl_const_iterator>::into_iter(*this);
  }
};

template<typename T, std::size_t N>
[[nodiscard]] constexpr auto to_array(const std::array<T, N> &arr) -> array<T, N> {
  array<T, N> result = {};
  std::copy(arr.data(), arr.data() + arr.size(), result.data());
  return result;
}

}// namespace ftl

template<typename Item, std::size_t N>
struct ftl::from_iterator_trait<ftl::array_container_iterator<Item, N>, ftl::array<Item, N>> {
  [[nodiscard]] constexpr static auto from_iter(array_container_iterator<Item, N> &iter) {
    array<Item, N> result{};
    std::size_t i = 0;
    for (auto &&item : iter) {
      result[i] = item;
      ++i;
    }

    return result;
  }
};

template<typename Item, std::size_t N>
struct ftl::from_iterator_trait<ftl::array_container_const_iterator<Item, N>, ftl::array<Item, N>> {
  [[nodiscard]] constexpr static auto from_iter(const array_container_const_iterator<Item, N> &iter) {
    array<Item, N> result{};
    std::size_t i = 0;
    for (auto &&item : iter) {
      result[i] = item;
      ++i;
    }

    return result;
  }
};

template<typename Iter, typename Callable, typename Item, std::size_t N>
struct ftl::from_iterator_trait<ftl::map_iterator<Iter, Callable>, ftl::array<Item, N>> {
  [[nodiscard]] constexpr static auto from_iter(const map_iterator<Iter, Callable> &iter) -> array<Item, N> {
    array<Item, N> result{};
    std::size_t i = 0;
    for (auto &&item : iter) {
      result[i] = item;
      ++i;
    }

    return result;
  }
};

template<typename Iter, typename Item, std::size_t N>
struct ftl::from_iterator_trait<ftl::enumerate_iterator<Iter>, ftl::array<std::tuple<std::size_t, Item>, N>> {
  [[nodiscard]] constexpr static auto from_iter(const enumerate_iterator<Iter> &iter)
  -> array<std::tuple<std::size_t, Item>, N> {
    array<std::tuple<std::size_t, Item>, N> result{};
    std::size_t i = 0;
    for (auto &&item : iter) {
      result[i] = item;
      ++i;
    }

    return result;
  }
};

template<typename Iter, typename Callable, typename Item, std::size_t N>
struct ftl::from_iterator_trait<ftl::inspect_iterator<Iter, Callable>, ftl::array<Item, N>> {
  [[nodiscard]] constexpr static auto from_iter(const inspect_iterator<Iter, Callable> &iter) -> ftl::array<Item, N> {
    array<Item, N> result{};
    std::size_t i = 0;
    for (auto &&item : iter) {
      result[i] = item;
      ++i;
    }

    return result;
  }
};

template<typename T, std::size_t N>
struct ftl::into_iterator_trait<ftl::array<T, N>, typename ftl::array<T, N>::ftl_iterator> {
  using iterator = typename ftl::array<T, N>::ftl_iterator;

  [[nodiscard]] constexpr static auto into_iter(ftl::array<T, N> &arr) -> iterator {
    return iterator{ arr.data(), arr.data() + arr.size() };
  }
};

template<typename T, std::size_t N>
struct ftl::into_iterator_trait<ftl::array<T, N>, typename ftl::array<T, N>::ftl_const_iterator> {
  using const_iterator = typename ftl::array<T, N>::ftl_const_iterator;

  [[nodiscard]] constexpr static auto into_iter(const ftl::array<T, N> &arr) -> const_iterator {
    return const_iterator{ arr.data(), arr.data() + arr.size() };
  }
};
