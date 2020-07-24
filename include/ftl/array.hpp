#pragma once

#include <algorithm>

#include <ftl/array_iterator.hpp>
#include <ftl/array_const_iterator.hpp>
#include <ftl/from_iterator_trait.hpp>
#include <ftl/into_iterator_trait.hpp>

namespace ftl {

template<typename T, std::size_t N> class array {
  static_assert(N > 0, "N must be larger than 0!");

public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator = typename ftl::array_iterator<T, N>;
  using const_iterator = typename ftl::array_const_iterator<T, N>;

  [[nodiscard]] constexpr reference operator[](size_type pos) noexcept {
    if (pos >= N) std::terminate();

    return data_[pos];
  }

  [[nodiscard]] constexpr const_reference operator[](size_type pos) const noexcept {
    if (pos >= N) std::terminate();

    return data_[pos];
  }

  [[nodiscard]] constexpr reference front() noexcept {
    return data_[0];
  }

  [[nodiscard]] constexpr const_reference front() const noexcept {
    return data_[0];
  }

  [[nodiscard]] constexpr reference back() noexcept {
    return data_[N - 1];
  }

  [[nodiscard]] constexpr const_reference back() const noexcept {
    return data_[N - 1];
  }

  [[nodiscard]] constexpr pointer data() noexcept {
    return data_;
  }

  [[nodiscard]] constexpr const_pointer data() const noexcept {
    return data_;
  }

  [[nodiscard]] constexpr iterator iter() noexcept {
    return into_iterator_trait<array<T, N>, iterator>::into_iter(*this);
  }

  [[nodiscard]] constexpr const_iterator iter() const noexcept {
    return into_iterator_trait<array<T, N>, const_iterator>::into_iter(*this);
  }

  [[nodiscard]] constexpr iterator begin() noexcept {
    return iter().begin();
  }

  [[nodiscard]] constexpr const_iterator cbegin() const noexcept {
    return iter().cbegin();
  }

  [[nodiscard]] constexpr iterator end() noexcept {
    return iter().end();
  }

  [[nodiscard]] constexpr const_iterator cend() const noexcept {
    return iter().cend();
  }

  [[nodiscard]] constexpr size_type size() const noexcept {
    return N;
  }

  [[nodiscard]] constexpr size_type max_size() const noexcept {
    return N;
  }

  [[nodiscard]] constexpr bool empty() const noexcept {
    return false;
  }

  constexpr void fill(const T &value) {
    // TODO: Use begin() instead of data once we sort out iterators.
    std::fill_n(data_, N, value);
  }

  constexpr void swap(array &other) {
    // TODO: Use begin() and end() instead of raw once we sort out
    // iterators.
    std::swap_ranges(data(), data() + size(), other.data());
  }

  T data_[N];
};

template<typename T, std::size_t N>
[[nodiscard]] constexpr bool operator==(const array<T, N> &lhs, const array<T, N> &rhs) noexcept {
  // TODO: Use begin() and end() instead of raw once we sort out iterators.
  return std::equal(lhs.data(), lhs.data() + lhs.size(), rhs.data());
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr bool operator!=(const array<T, N> &lhs, const array<T, N> &rhs) noexcept {
  return !(lhs == rhs);
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr bool operator<(const array<T, N> &lhs, const array<T, N> &rhs) noexcept {
  // TODO: Use begin() and end() instead of raw once we sort out iterators.
  return std::lexicographical_compare(lhs.data(), lhs.data() + lhs.size(), rhs.data(), rhs.data() + rhs.size());
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr bool operator<=(const array<T, N> &lhs, const array<T, N> &rhs) noexcept {
  return !(rhs < lhs);
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr bool operator>(const array<T, N> &lhs, const array<T, N> &rhs) noexcept {
  return rhs < lhs;
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr bool operator>=(const array<T, N> &lhs, const array<T, N> &rhs) noexcept {
  return !(lhs < rhs);
}

template<typename T, std::size_t N>[[nodiscard]] constexpr ftl::array<T, N> to_array(const std::array<T, N> &arr) {
  array<T, N> result;
  std::copy(arr.data(), arr.data() + arr.size(), result.data());
  return result;
}

}// namespace ftl

template<typename Item, std::size_t N> struct ftl::from_iterator_trait<ftl::array_iterator<Item, N>, ftl::array<Item, N>> {
  [[nodiscard]] constexpr static auto from_iter(ftl::array_iterator<Item, N> &iter) {
    ftl::array<Item, N> result{};
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
  [[nodiscard]] constexpr static auto from_iter(const ftl::array_const_iterator<Item, N> &iter) {
    ftl::array<Item, N> result{};
    std::size_t i = 0;
    for (auto &&item : iter) {
      result[i] = item;
      ++i;
    }

    return result;
  }
};

template<typename T, std::size_t N> struct ftl::into_iterator_trait<ftl::array<T, N>, typename ftl::array<T, N>::iterator> {
  using iterator = typename array<T, N>::iterator;

  [[nodiscard]] constexpr static iterator into_iter(array<T, N> &arr) {
    return iterator{ arr.data(), arr.data() + arr.size() };
  }
};

template<typename T, std::size_t N>
struct ftl::into_iterator_trait<ftl::array<T, N>, typename ftl::array<T, N>::const_iterator> {
  using const_iterator = typename array<T, N>::const_iterator;

  [[nodiscard]] constexpr static const_iterator into_iter(const array<T, N> &arr) {
    return const_iterator{ arr.data(), arr.data() + arr.size() };
  }
};