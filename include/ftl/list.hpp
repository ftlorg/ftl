#pragma once

#include <list>

namespace ftl {

template<typename T, typename Allocator = std::allocator<T>>
class list {
public:
  using value_type = typename std::list<T, Allocator>::value_type;
  using allocator_type = typename std::list<T, Allocator>::allocator_type;
  using size_type = typename std::list<T, Allocator>::size_type;
  using difference_type = typename std::list<T, Allocator>::difference_type;
  using pointer = typename std::list<T, Allocator>::pointer;
  using reference = typename std::list<T, Allocator>::reference;
  using const_pointer = typename std::list<T, Allocator>::const_pointer;
  using const_reference = typename std::list<T, Allocator>::const_reference;
  using iterator = typename std::list<T, Allocator>::iterator;
  using const_iterator = typename std::list<T, Allocator>::const_iterator;
  using reverse_iterator = typename std::list<T, Allocator>::reverse_iterator;
  using const_reverse_iterator = typename std::list<T, Allocator>::const_reverse_iterator;

  list() = default;

  explicit list(const Allocator &alloc) : list_{ alloc } {
  }

  explicit list(size_type count, const T &value, const Allocator &alloc = Allocator{}) : list_{ count, value, alloc } {
  }

  explicit list(size_type count, const Allocator &alloc = Allocator{}) : list_{ count, alloc } {
  }

  template<typename InputIt>
  list(InputIt first, InputIt last, const Allocator &alloc = Allocator()) : list_{ first, last, alloc } {
  }

  list(const list &rhs) = default;

  list(const list &rhs, const Allocator &alloc) : list_{ rhs, alloc } {
  }

  list(list &&rhs) = default;

  list(list &&rhs, const Allocator &alloc) : list_{ rhs, alloc } {
  }

  list(std::initializer_list<T> init, const Allocator &alloc = Allocator()) : list_{ std::move(init), alloc } {
  }

  ~list() = default;

  list &operator=(const list &rhs) = default;

  list &operator=(list &&rhs) noexcept(std::allocator_traits<Allocator>::is_always_equal::value) = default;

  list &operator=(std::initializer_list<T> init) {
    return list_ = std::move(init);
  }

  void assign(size_type count, const value_type &value) {
    list_.assign(count, value);
  }

  template<typename InputIt>
  void assign(InputIt first, InputIt last) {
    list_.assign(std::move(first), std::move(last));
  }

  void assign(std::initializer_list<value_type> init) {
    list_.assign(std::move(init));
  }

  [[nodiscard]] auto get_allocator() const noexcept -> allocator_type {
    return list_.get_allocator();
  }

  [[nodiscard]] auto front() -> reference {
    return list_.front();
  }

  [[nodiscard]] auto front() const -> const_reference {
    return list_.front();
  }

  [[nodiscard]] auto back() -> reference {
    return list_.back();
  }

  [[nodiscard]] auto back() const -> const_reference {
    return list_.back();
  }

  [[nodiscard]] auto begin() noexcept -> iterator {
    return list_.begin();
  }

  [[nodiscard]] auto begin() const noexcept -> const_iterator {
    return list_.begin();
  }

  [[nodiscard]] auto cbegin() const noexcept -> const_iterator {
    return list_.cbegin();
  }

  [[nodiscard]] auto end() noexcept -> iterator {
    return list_.end();
  }

  [[nodiscard]] auto end() const noexcept -> const_iterator {
    return list_.end();
  }

  [[nodiscard]] auto cend() const noexcept -> const_iterator {
    return list_.cend();
  }

  [[nodiscard]] auto rbegin() noexcept -> reverse_iterator {
    return list_.rbegin();
  }

  [[nodiscard]] auto rbegin() const noexcept -> const_reverse_iterator {
    return list_.rbegin();
  }

  [[nodiscard]] auto crbegin() const noexcept -> const_reverse_iterator {
    return list_.crbegin();
  }

  [[nodiscard]] auto rend() noexcept -> reverse_iterator {
    return list_.rend();
  }

  [[nodiscard]] auto rend() const noexcept -> const_reverse_iterator {
    return list_.rend();
  }

  [[nodiscard]] auto crend() const noexcept -> const_reverse_iterator {
    return list_.crend();
  }

  [[nodiscard]] auto empty() const noexcept -> bool {
    return list_.empty();
  }

  [[nodiscard]] auto size() const noexcept -> size_type {
    return list_.size();
  }

  [[nodiscard]] auto max_size() const noexcept -> size_type {
    return list_.max_size();
  }

  auto clear() noexcept -> void {
    list_.clear();
  }

  auto insert(const_iterator pos, const value_type &value) -> iterator {
    return list_.insert(std::move(pos), value);
  }

  auto insert(const_iterator pos, value_type &&value) -> iterator {
    return list_.insert(std::move(pos), std::move(value));
  }

  auto insert(const_iterator pos, size_type count, const value_type &value) -> iterator {
    return list_.insert(std::move(pos), count, value);
  }

  template<class InputIt>
  auto insert(const_iterator pos, InputIt first, InputIt last) -> void {
    return list_.insert(std::move(pos), std::move(first), std::move(last));
  }

  auto insert(const_iterator pos, std::initializer_list<value_type> init) -> iterator {
    return list_.insert(std::move(pos), std::move(init));
  }

  template<class... Args>
  auto emplace(const_iterator pos, Args &&... args) -> iterator {
    return list_.template emplace<Args...>(std::move(pos), std::forward<Args>(args)...);
  }

  auto erase(const_iterator pos) -> iterator {
    return list_.erase(std::move(pos));
  }

  auto erase(const_iterator first, const_iterator last) -> iterator {
    return list_.erase(std::move(first), std::move(last));
  }

  auto push_back(const value_type &value) -> void {
    return list_.push_back(value);
  }

  auto push_back(value_type &&value) -> void {
    return list_.push_back(std::move(value));
  }

  template<class... Args>
  auto emplace_back(Args &&... args) -> reference {
    return list_.template emplace_back<Args...>(std::forward<Args>(args)...);
  }

  auto pop_back() -> void {
    list_.pop_back();
  }

  auto push_front(const value_type &value) -> void {
    list_.push_front(value);
  }

  auto push_front(value_type &&value) -> void {
    list_.push_front(std::move(value));
  }

  template<class... Args>
  auto emplace_front(Args &&... args) -> reference {
    return list_.template emplace_front<Args...>(std::forward<Args>(args)...);
  }

  auto pop_front() -> void {
    list_.pop_front();
  }

  auto resize(size_type count) -> void {
    list_.resize(count);
  }

  auto resize(size_type count, const value_type &value) -> void {
    list_.resize(count, value);
  }

  auto swap(list &other) noexcept(std::allocator_traits<allocator_type>::is_always_equal::value) -> void {
    list_.swap(other.list_);
  }

  auto merge(list &other) -> void {
    list_.merge(other.list_);
    list_.merge(other.list_);
  }

  auto merge(list &&other) -> void {
    list_.merge(std::move(other));
  }

  template<class Compare>
  auto merge(list &other, Compare comp) -> void {
    list_.merge(other, std::move(comp));
  }

  template<class Compare>
  auto merge(list &&other, Compare comp) -> void {
    list_.merge(std::move(other), std::move(comp));
  }

  auto splice(const_iterator pos, list &other) -> void {
    list_.splice(std::move(pos), other.list_);
  }

  auto splice(const_iterator pos, list &&other) -> void {
    list_.splice(std::move(pos), std::move(other));
  }

  auto splice(const_iterator pos, list &other, const_iterator it) -> void {
    list_.splice(std::move(pos), other.list_, std::move(it));
  }

  auto splice(const_iterator pos, list &&other, const_iterator it) -> void {
    list_.splice(std::move(pos), std::move(other), std::move(it));
  }

  auto splice(const_iterator pos, list &other, const_iterator first, const_iterator last) -> void {
    list_.splice(std::move(pos), other.list_, std::move(first), std::move(last));
  }

  auto splice(const_iterator pos, list &&other, const_iterator first, const_iterator last) -> void {
    list_.splice(std::move(pos), std::move(other), std::move(first), std::move(last));
  }

  auto remove(const T &value) -> void {
    list_.remove(value);
  }

  template<class UnaryPredicate>
  auto remove_if(UnaryPredicate p) -> void {
    list_.remove_if(std::move(p));
  }

  auto reverse() noexcept -> void {
    list_.reverse();
  }

  auto unique() -> void {
    list_.unique();
  }

  template<class BinaryPredicate>
  auto unique(BinaryPredicate p) -> void {
    list_.unique(std::move(p));
  }

  auto sort() -> void {
    list_.sort();
  }

  template<class Compare>
  auto sort(Compare comp) -> void {
    list_.sort(std::move(comp));
  }

  [[nodiscard]] friend auto operator==(const list<T, Allocator> &lhs, const list<T, Allocator> &rhs) -> bool {
    return lhs.list_ == rhs.list_;
  }

  [[nodiscard]] friend auto operator!=(const list<T, Allocator> &lhs, const list<T, Allocator> &rhs) -> bool {
    return lhs.list_ != rhs.list_;
  }

  [[nodiscard]] friend auto operator<(const list<T, Allocator> &lhs, const list<T, Allocator> &rhs) -> bool {
    return lhs.list_ < rhs.list_;
  }

  [[nodiscard]] friend auto operator<=(const list<T, Allocator> &lhs, const list<T, Allocator> &rhs) -> bool {
    return lhs.list_ <= rhs.list_;
  }

  [[nodiscard]] friend auto operator>(const list<T, Allocator> &lhs, const list<T, Allocator> &rhs) -> bool {
    return lhs.list_ > rhs.list_;
  }

  [[nodiscard]] friend auto operator>=(const list<T, Allocator> &lhs, const list<T, Allocator> &rhs) -> bool {
    return lhs.list_ >= rhs.list_;
  }

private:
  std::list<value_type, allocator_type> list_{};
};

template<class T, class Alloc>
void swap(std::list<T, Alloc> &lhs, std::list<T, Alloc> &rhs) noexcept(noexcept(lhs.swap(rhs))) {
  lhs.swap(rhs);
}

}// namespace ftl
