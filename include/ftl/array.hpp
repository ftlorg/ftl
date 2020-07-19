#pragma once

#include <algorithm>

#include <ftl/iterator.hpp>

namespace ftl {

template<typename T, std::size_t N>
class array
{
public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using iterator = ftl::iterator_trait<T>;
  using const_iterator = const ftl::iterator_trait<T>;
  using reverse_iterator = ftl::reverse_iterator_trait<T>;
  using const_reverse_iterator = const ftl::reverse_iterator_trait<T>;


  [[nodiscard]] constexpr reference operator[](size_type pos) noexcept
  {
    if (pos >= N)
      std::terminate();

    return data_[pos];
  }

  [[nodiscard]] constexpr const_reference operator[](size_type pos) const noexcept
  {
    if (pos >= N)
      std::terminate();

    return data_[pos];
  }

  [[nodiscard]] constexpr reference front() noexcept
  {
    if constexpr (N < 1) {
      std::terminate();
    }

    return data_[0];
  }

  [[nodiscard]] constexpr const_reference front() const noexcept
  {
    if constexpr (N < 1) {
      std::terminate();
    }

    return data_[0];
  }

  [[nodiscard]] constexpr reference back() noexcept
  {
    if constexpr (N < 1) {
      std::terminate();
    }

    return data_[N - 1];
  }

  [[nodiscard]] constexpr const_reference back() const noexcept
  {
    if constexpr (N < 1) {
      std::terminate();
    }

    return data_[N - 1];
  }

  [[nodiscard]] constexpr pointer data() noexcept
  {
    return data_;
  }

  [[nodiscard]] constexpr const_pointer data() const noexcept
  {
    return data_;
  }

  [[nodiscard]] constexpr iterator begin() noexcept;

  [[nodiscard]] constexpr const_iterator cbegin() const noexcept;

  [[nodiscard]] constexpr iterator end() noexcept;

  [[nodiscard]] constexpr const_iterator cend() const noexcept;

  [[nodiscard]] constexpr iterator rbegin() noexcept;

  [[nodiscard]] constexpr const_iterator rcbegin() const noexcept;

  [[nodiscard]] constexpr iterator rend() noexcept;

  [[nodiscard]] constexpr const_iterator rcend() const noexcept;

  [[nodiscard]] constexpr size_type size() const noexcept { return N; }

  [[nodiscard]] constexpr size_type max_size() const noexcept { return N; }

  [[nodiscard]] constexpr bool empty() const noexcept { return false; }

  constexpr void fill(const T &value)
  {
    // TODO: Use begin() instead of data once we sort out iterators.
    std::fill_n(data_, N, value);
  }

  constexpr void swap(array &other)
  {
    // TODO: Use begin() and end() instead of raw once we sort out iterators.
    std::swap_ranges(data(), data() + size(), other.data());
  }

  T data_[N];
};

template<typename T, std::size_t N>
[[nodiscard]] constexpr bool operator==(const array<T, N> &lhs, const array<T, N> &rhs) noexcept
{
  // TODO: Use begin() and end() instead of raw once we sort out iterators.
  return std::equal(lhs.data(), lhs.data() + lhs.size(), rhs.data());
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr bool operator!=(const array<T, N> &lhs, const array<T, N> &rhs) noexcept
{
  return !(lhs == rhs);
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr bool operator<(const array<T, N> &lhs, const array<T, N> &rhs) noexcept
{
  // TODO: Use begin() and end() instead of raw once we sort out iterators.
  return std::lexicographical_compare(lhs.data(), lhs.data() + lhs.size(), rhs.data(), rhs.data() + rhs.size());
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr bool operator<=(const array<T, N> &lhs, const array<T, N> &rhs) noexcept
{
  return !(rhs < lhs);
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr bool operator>(const array<T, N> &lhs, const array<T, N> &rhs) noexcept
{
  return rhs < lhs;
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr bool operator>=(const array<T, N> &lhs, const array<T, N> &rhs) noexcept
{
  return !(lhs < rhs);
}

template<typename T, std::size_t N>
[[nodiscard]] constexpr static ftl::array<T, N> to_array(const std::array<T, N> &arr)
{
  array<T, N> result;
  std::copy(arr.data(), arr.data() + arr.size(), result.data());
  return result;
}

}// namespace ftl