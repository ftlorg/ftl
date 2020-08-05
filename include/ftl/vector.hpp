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

  vector() = default;

  vector(size_type size) : vector_(size) {
  }

  vector(std::vector<T> vec) : vector_(std::move(vec)) {
  }

  vector(std::initializer_list<T> list) : vector_(std::move(list)) {
  }

  [[nodiscard]] constexpr auto operator[](const std::size_t pos) -> reference {
    if (pos >= vector_.size()) std::terminate();
    return vector_[pos];
  }

  [[nodiscard]] constexpr auto operator[](const std::size_t pos) const -> const_reference {
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

  [[nodiscard]] constexpr auto size() const noexcept -> size_type {
    return vector_.size();
  }

  constexpr auto resize(const size_type size) -> void {
    vector_.resize(size);
  }

  [[nodiscard]] constexpr auto empty() const noexcept -> bool {
    return vector_.empty();
  }

  constexpr auto fill(const_reference val) -> void {
    std::fill(vector_.begin(), vector_.end(), val);
  }

  [[nodiscard]] constexpr auto operator==(const vector<T> &rhs) const noexcept -> bool {
    return vector_ == rhs.vector_;
  }

  constexpr auto swap(vector<T> &other) noexcept -> void {
    std::swap(vector_, other.vector_);
  }

private:
  std::vector<T, Allocator> vector_;
};

template<typename T, typename Allocator = std::allocator<T>>
[[nodiscard]] constexpr auto to_vector(std::vector<T> vec) -> vector<T, Allocator> {
  return vector<T, Allocator>{ std::move(vec) };
}

}// namespace ftl