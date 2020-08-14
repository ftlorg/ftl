#pragma once

#include <algorithm>
#include <array>

#include <ftl/array_iterator.hpp>
#include <ftl/array_const_iterator.hpp>
#include <ftl/from_iterator_trait.hpp>
#include <ftl/into_iterator_trait.hpp>

namespace ftl {

template<typename T, std::size_t N>
class array {
  static_assert(N > 0, "N must be larger than 0!");

public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator = array_iterator<T, N>;
  using const_iterator = array_const_iterator<T, N>;

  [[nodiscard]] constexpr auto operator[](size_type pos) noexcept -> reference {
    if (pos >= N) std::terminate();

    return data_[pos];
  }

  [[nodiscard]] constexpr auto operator[](size_type pos) const noexcept -> const_reference {
    if (pos >= N) std::terminate();

    return data_[pos];
  }

  [[nodiscard]] constexpr auto front() noexcept -> reference {
    return data_[0];
  }

  [[nodiscard]] constexpr auto front() const noexcept -> const_reference {
    return data_[0];
  }

  [[nodiscard]] constexpr auto back() noexcept -> reference {
    return data_[N - 1];
  }

  [[nodiscard]] constexpr auto back() const noexcept -> const_reference {
    return data_[N - 1];
  }

  [[nodiscard]] constexpr auto data() noexcept -> pointer {
    return data_;
  }

  [[nodiscard]] constexpr auto data() const noexcept -> const_pointer {
    return data_;
  }

  [[nodiscard]] constexpr auto iter() noexcept -> iterator {
    return into_iterator_trait<array<T, N>, iterator>::into_iter(*this);
  }

  [[nodiscard]] constexpr auto iter() const noexcept -> const_iterator {
    return into_iterator_trait<array<T, N>, const_iterator>::into_iter(*this);
  }

  [[nodiscard]] constexpr auto begin() noexcept -> iterator {
    return iter().begin();
  }

  [[nodiscard]] constexpr auto begin() const noexcept -> const_iterator {
    return cbegin();
  }

  [[nodiscard]] constexpr auto cbegin() const noexcept -> const_iterator {
    return iter().cbegin();
  }

  [[nodiscard]] constexpr auto end() noexcept -> iterator {
    return iter().end();
  }

  [[nodiscard]] constexpr auto end() const noexcept -> const_iterator {
    return cend();
  }

  [[nodiscard]] constexpr auto cend() const noexcept -> const_iterator {
    return iter().cend();
  }

  [[nodiscard]] constexpr auto size() const noexcept -> size_type {
    return N;
  }

  [[nodiscard]] constexpr auto max_size() const noexcept -> size_type {
    return N;
  }

  [[nodiscard]] constexpr auto empty() const noexcept -> bool {
    return false;
  }

  constexpr auto fill(const T &value) -> void {
    std::fill_n(data_, N, value);
  }

  constexpr auto swap(array &other) -> void {
    std::swap_ranges(data(), data() + size(), other.data());
  }

  T data_[N];
};

template<typename T, std::size_t N>
[[nodiscard]] constexpr auto operator==(const array<T, N> &lhs, const array<T, N> &rhs) noexcept -> bool {
  return std::equal(lhs.data(), lhs.data() + lhs.size(), rhs.data());
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr auto operator!=(const array<T, N> &lhs, const array<T, N> &rhs) noexcept -> bool {
  return !(lhs == rhs);
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr auto operator<(const array<T, N> &lhs, const array<T, N> &rhs) noexcept -> bool {
  return std::lexicographical_compare(lhs.data(), lhs.data() + lhs.size(), rhs.data(), rhs.data() + rhs.size());
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr auto operator<=(const array<T, N> &lhs, const array<T, N> &rhs) noexcept -> bool {
  return !(rhs < lhs);
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr auto operator>(const array<T, N> &lhs, const array<T, N> &rhs) noexcept -> bool {
  return rhs < lhs;
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr auto operator>=(const array<T, N> &lhs, const array<T, N> &rhs) noexcept -> bool {
  return !(lhs < rhs);
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr auto to_array(const std::array<T, N> &arr) -> array<T, N> {
  array<T, N> result = {};
  std::copy(arr.data(), arr.data() + arr.size(), result.data());
  return result;
}

}// namespace ftl

template<typename Item, std::size_t N>
struct ftl::from_iterator_trait<ftl::array_iterator<Item, N>, ftl::array<Item, N>> {
  [[nodiscard]] constexpr static auto from_iter(array_iterator<Item, N> &iter) {
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
struct ftl::from_iterator_trait<ftl::array_const_iterator<Item, N>, ftl::array<Item, N>> {
  [[nodiscard]] constexpr static auto from_iter(const array_const_iterator<Item, N> &iter) {
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

template<typename T, std::size_t N>
struct ftl::into_iterator_trait<ftl::array<T, N>, typename ftl::array<T, N>::iterator> {
  using iterator = typename array<T, N>::iterator;

  [[nodiscard]] constexpr static auto into_iter(array<T, N> &arr) -> iterator {
    return iterator{ arr.data(), arr.data() + arr.size() };
  }
};

template<typename T, std::size_t N>
struct ftl::into_iterator_trait<ftl::array<T, N>, typename ftl::array<T, N>::const_iterator> {
  using const_iterator = typename array<T, N>::const_iterator;

  [[nodiscard]] constexpr static auto into_iter(const array<T, N> &arr) -> const_iterator {
    return const_iterator{ arr.data(), arr.data() + arr.size() };
  }
};
