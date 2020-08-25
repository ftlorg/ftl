#pragma once

#include <vector>
#include "vector_iterator.hpp"
#include "vector_const_iterator.hpp"

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
  using allocator_type = Allocator;
  using iterator = ftl::vector_iterator<T>;
  using const_iterator = ftl::vector_const_iterator<T>;

  vector() = default;

  vector(size_type size) : vector_(size) {
  }

  vector(std::vector<T> vec) : vector_(std::move(vec)) {
  }

  vector(std::initializer_list<T> list) : vector_(std::move(list)) {
  }

  template<typename Iter>
  vector(Iter begin, Iter end) : vector_{ begin, end } {
  }

  constexpr auto operator=(const vector<T, Allocator> &rhs) -> vector<T, Allocator> & {
    if (this == &rhs) return *this;
    vector_ = rhs.vector_;
    return *this;
  }

  constexpr auto operator=(vector<T, Allocator> &&rhs) -> vector<T, Allocator> & {
    if (this == &rhs) return *this;
    vector_ = std::move(rhs.vector_);
    return *this;
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

  constexpr auto begin() -> iterator {
    return iterator{ vector_.begin(), vector_.end() };
  }

  constexpr auto end() -> iterator {
    return iterator{ vector_.end(), vector_.end() };
  }

  constexpr auto begin() const -> const_iterator {
    return cbegin();
  }

  constexpr auto end() const -> const_iterator {
    return cend();
  }

  constexpr auto cbegin() const -> const_iterator {
    return const_iterator{ vector_.begin(), vector_.end() };
  }

  constexpr auto cend() const -> const_iterator {
    return const_iterator{ vector_.end(), vector_.end() };
  }

  [[nodiscard]] constexpr auto operator==(const vector<T> &rhs) const noexcept -> bool {
    return vector_ == rhs.vector_;
  }

  constexpr auto swap(vector<T> &other) noexcept -> void {
    std::swap(vector_, other.vector_);
  }

  constexpr auto push_back(const_reference value) -> void {
    vector_.push_back(value);
  }

  constexpr auto push_back(value_type &&value) -> void {
    vector_.push_back(std::move(value));
  }

  template<typename... Args>
  constexpr auto emplace_back(Args &&... args) -> void {
    vector_.emplace_back(std::forward<Args...>(args...));
  }

  constexpr auto assign(size_type size, const_reference value) -> void {
    vector_.assign(size, value);
  }

  constexpr auto assign(std::initializer_list<value_type> list) -> void {
    vector_.assign(list);
  }

  template<class InputIt>
  constexpr auto assign(InputIt first, InputIt last) -> void {
    vector_.assign(first, last);
  }

  [[nodiscard]] constexpr auto get_allocator() const noexcept -> allocator_type {
    return vector_.get_allocator();
  }

  [[nodiscard]] constexpr auto at(const size_type pos) -> reference {
    return vector_.at(pos);
  }

  [[nodiscard]] constexpr auto at(const size_type pos) const -> const_reference {
    return vector_.at(pos);
  }

  [[nodiscard]] constexpr auto iter() noexcept -> iterator {
    return into_iterator_trait<ftl::vector<T, Allocator>, iterator>::into_iter(*this);
  }

  [[nodiscard]] constexpr auto iter() const noexcept -> const_iterator {
    return into_iterator_trait<ftl::vector<T, Allocator>, const_iterator>::into_iter(*this);
  }

public:
  std::vector<T, Allocator> vector_;
};

template<typename T, typename Allocator = std::allocator<T>>
[[nodiscard]] constexpr auto to_vector(std::vector<T> vec) -> vector<T, Allocator> {
  return vector<T, Allocator>{ std::move(vec) };
}

}// namespace ftl

template<typename Item, typename Allocator>
struct ftl::into_iterator_trait<ftl::vector<Item, Allocator>, ftl::vector_iterator<Item>> {
  using iterator = typename ftl::vector<Item, Allocator>::iterator;
  [[nodiscard]] constexpr static auto into_iter(ftl::vector<Item, Allocator> &vec) {
    return iterator{ vec.vector_.begin(), vec.vector_.end() };
  }
};

template<typename Item, typename Allocator>
struct ftl::into_iterator_trait<ftl::vector<Item, Allocator>, ftl::vector_const_iterator<Item>> {
  using const_iterator = typename ftl::vector<Item, Allocator>::const_iterator;
  [[nodiscard]] constexpr static auto into_iter(const ftl::vector<Item, Allocator> &vec) {
    return const_iterator{ vec.vector_.begin(), vec.vector_.end() };
  }
};