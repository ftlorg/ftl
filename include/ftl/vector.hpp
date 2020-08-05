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

  vector(std::vector<T, Allocator> vec) : vector_(std::move(vec)) {
  }

  vector(std::initializer_list<T> vec) : vector(std::move(vec)) {
  }

  [[nodiscard]] constexpr reference operator[](std::size_t pos) {
    if (pos >= vector_.size()) std::terminate();
    return vector_[pos];
  }

  [[nodiscard]] constexpr const_reference operator[](std::size_t pos) const {
    if (pos >= vector_.size()) std::terminate();
    return vector_[pos];
  }

  [[nodiscard]] constexpr reference front() {
    return vector_.front();
  }

  [[nodiscard]] constexpr const_reference front() const {
    return vector_.front();
  }

  [[nodiscard]] constexpr reference back() {
    return vector_.back();
  }

  [[nodiscard]] constexpr const_reference back() const {
    return vector_.back();
  }


private:
  std::vector<T, Allocator> vector_;
};

template<typename T, typename Allocator = std::allocator<T>>
[[nodiscard]] constexpr auto to_vector(std::vector<T, Allocator> vec) -> vector<T, Allocator> {
  return vector{ std::move(vec) };
}

}// namespace ftl