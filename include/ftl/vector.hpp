#pragma once

#include <vector>

namespace ftl {
template<typename T, typename Allocator = std::allocator<T>>
class vector {
public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using iterator = void;      // TODO: vector_iterator
  using const_iterator = void;// TODO: const_vector_iterator

  vector(std::vector<T> vec) : vector_(std::move(vec)) {
  }

  vector(std::initializer_list<T> list) : vector_(std::move(list)) {
  }

  [[nodiscard]] constexpr auto operator[](std::size_t pos) -> reference {
    if (pos >= vector_.size()) std::terminate();
    return vector_[pos];
  }

  [[nodiscard]] constexpr auto operator[](std::size_t pos) const -> const_reference  {
    if (pos >= vector_.size()) std::terminate();
    return vector_[pos];
  }

  [[nodiscard]] constexpr auto front() -> reference {
    return vector_.front();
  }

  [[nodiscard]] constexpr auto front() const -> const_reference {
    return vector_.front();
  }

  [[nodiscard]] constexpr auto back() -> reference {
    return vector_.back();
  }

  [[nodiscard]] constexpr auto back() const -> const_reference {
    return vector_.back();
  }

  [[nodiscard]] constexpr auto data() -> pointer {
    return vector_.data();
  }

  [[nodiscard]] constexpr auto data() const -> const_pointer {
    return vector_.data();
  }

private:
  std::vector<T, Allocator> vector_;
};

template<typename T, typename Allocator = std::allocator<T>>
[[nodiscard]] constexpr auto to_vector(std::vector<T> vec) -> vector<T, Allocator> {
  return vector<T, Allocator>{ std::move(vec) };
}

}// namespace ftl