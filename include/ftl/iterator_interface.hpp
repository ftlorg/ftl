#pragma once

#include <ftl/from_iterator_trait.hpp>
#include <memory>
#include <cassert>
#include <tuple>
#include <optional>

namespace ftl {

template<typename Derived, typename Item, typename Size>
class iterator_interface;

template<typename Iter, typename Callable>
class map_iterator;

template<typename Iter, typename Callable>
class filter_iterator;

template<typename Iter>
class flatten_iterator : public iterator_interface<flatten_iterator<Iter>, Iter, std::size_t> {};

template<typename Iter>
class enumerate_iterator;

template<typename Iter, typename Callable>
class inspect_iterator;

template<typename Iter>
class take_iterator : public iterator_interface<take_iterator<Iter>, Iter, std::size_t> {};

template<typename Iter>
class rev_iterator : public iterator_interface<rev_iterator<Iter>, Iter, std::size_t> {};

/**
 * Interface for iterators.

 * @tparam Derived The type of iterator implementing this interface.
 * @tparam Item The type of the underlying item.
 * @tparam SizeType The size type.
 */
template<typename Derived, typename Item, typename SizeType>
class iterator_interface {
public:
  using size_type = SizeType;
  using value_type = std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;

  virtual ~iterator_interface() = default;

  /**
   * Checks if all of the items matche a predicate.
   *
   * @tparam Predicate
   * @param predicate
   */
  template<typename Predicate>
  [[nodiscard]] auto all(Predicate &&predicate) const -> bool;

  /**
   * Checks if any of the items matches a predicate.
   *
   * @tparam Predicate
   * @param predicate
   */
  template<typename Predicate>
  [[nodiscard]] auto any(Predicate &&predicate) const -> bool;

  /**
   * Transforms an iterator into collection.
   *
   * @tparam Collection
   */
  template<typename Collection>
  [[nodiscard]] auto collect() -> Collection {
    return static_cast<Derived &>(*this).template collect_impl<Collection>();
  }

  /**
   * Counts number of iterations.
   */
  [[nodiscard]] auto count() const -> size_type {
    return static_cast<const Derived &>(*this).count_impl();
  }

  /**
   * Creates an iterator which gives the current iteration count as well as
   * the next value
   */
  [[nodiscard]] auto enumerate() -> enumerate_iterator<Derived> {
    return static_cast<Derived &>(*this).enumerate_impl();
  }

  /**
   * Creates an iterator which uses a predicate to determine if an element
   * should be yielded.
   *
   * @tparam Predicate
   * @param predicate
   */
  template<typename Predicate>
  [[nodiscard]] auto filter(Predicate &&predicate) const -> filter_iterator<Derived, Predicate> {
    return static_cast<const Derived &>(*this).filter_impl(std::forward<Predicate>(predicate));
  }

  /**
   * Searches for an element of an iterator that satisfies a predicate.
   *
   * @tparam Predicate
   * @param predicate
   */
  template<typename Predicate>
  [[nodiscard]] auto find(Predicate &&predicate) const -> std::optional<value_type>;

  /**
   * Creates an iterator that flattens nested structure.
   */
  [[nodiscard]] auto flatten() const -> flatten_iterator<Derived>;

  /**
   * Applies a function, producing a single, final value.
   *
   * @tparam Operator
   * @param initial
   * @param op
   */
  template<typename Operator>
  [[nodiscard]] auto fold(value_type initial, Operator &&op) -> value_type;

  /**
   * Calls a callable on each element of an iterator.
   *
   * @tparam Callable
   * @param callable
   */
  template<typename Callable>
  auto for_each(Callable &&callable) -> void;

  /**
   * Does something with each element of an iterator, passing the value on.
   *
   * @tparam Callable
   * @param callable
   */
  template<typename Callable>
  [[nodiscard]] auto inspect(Callable &&callable) const -> inspect_iterator<Derived, Callable> {
    return static_cast<const Derived &>(*this).inspect_impl(std::forward<Callable>(callable));
  }

  /**
   * Takes a callable and creates an iterator which calls that callable on
   * each element.
   *
   * @tparam Callable
   * @param callable
   */
  template<typename Callable>
  [[nodiscard]] auto map(Callable &&callable) -> map_iterator<Derived, Callable> {
    return static_cast<Derived &>(*this).map_impl(std::forward<Callable>(callable));
  }

  /**
   * Returns the maximum element of an iterator.
   */
  [[nodiscard]] auto max() const -> std::optional<value_type>;

  /**
   * Returns the minimum element of an iterator.
   */
  [[nodiscard]] auto min() const -> std::optional<value_type>;

  /**
   * Consumes an iterator, creating two collections from it.
   *
   * @tparam Collection
   * @tparam Predicate
   * @param predicate
   */
  template<typename Collection, typename Predicate>
  [[nodiscard]] auto partition(Predicate &&predicate) const -> std::tuple<Collection, Collection>;

  /**
   * Iterates over the entire iterator, multiplying all the elements.
   */
  [[nodiscard]] auto product() const -> value_type;


  /**
   * Iterates over the entire iterator, summing all the elements.
   */
  [[nodiscard]] auto sum() const -> value_type;

  /**
   * Creates an iterator that reverses traversal direction.
   */
  [[nodiscard]] auto rev() const -> rev_iterator<Derived>;

  /**
   * Creates an iterator that yields its first n elements.
   */
  [[nodiscard]] auto take(size_type n) const -> take_iterator<Derived>;

  /**
   * Returns currently pointed-to value.
   */
  [[nodiscard]] auto operator*() -> decltype(auto) {
    return static_cast<Derived &>(*this).deref_impl();
  }

  /**
   * Returns currently pointed-to value.
   */
  [[nodiscard]] auto operator*() const -> decltype(auto) {
    return static_cast<const Derived &>(*this).const_deref_impl();
  }

  /**
   * Advances the iterator.
   */
  auto operator++() -> decltype(auto) {
    return static_cast<Derived &>(*this).preincrement_impl();
  }

  /**
   * Advances the iterator.
   */
  auto operator++(int) const -> decltype(auto) {
    return static_cast<const Derived &>(*this).postincrement_impl();
  }

  /**
   * Decreases the iterator.
   */
  auto operator--() const -> void {
    static_cast<const Derived &>(*this).predecrement_impl();
  }

  /**
   * Returns begin iterator.
   */
  [[nodiscard]] constexpr auto begin() noexcept -> Derived {
    return static_cast<Derived &>(*this).begin_impl();
  }

  /**
   * Returns begin iterator.
   */
  [[nodiscard]] constexpr auto begin() const noexcept -> Derived {
    return cbegin();
  }

  /**
   * Returns cbegin iterator.
   */
  [[nodiscard]] constexpr auto cbegin() const noexcept -> Derived {
    return static_cast<const Derived &>(*this).cbegin_impl();
  }

  /**
   * Returns end iterator.
   */
  [[nodiscard]] constexpr auto end() noexcept -> Derived {
    return static_cast<Derived &>(*this).end_impl();
  }

  /**
   * Returns end iterator.
   */
  [[nodiscard]] constexpr auto end() const noexcept -> Derived {
    return cend();
  }

  /**
   * Returns cend iterator.
   */
  [[nodiscard]] constexpr auto cend() const noexcept -> Derived {
    return static_cast<const Derived &>(*this).cend_impl();
  }
};

/**
 * Interface for const iterators.

 * @tparam Derived The type of iterator implementing this interface.
 * @tparam Item The type of the underlying item.
 * @tparam SizeType The size type.
 */
template<typename Derived, typename Item, typename SizeType>
class const_iterator_interface {
public:
  using size_type = SizeType;
  using value_type = std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;

  virtual ~const_iterator_interface() = default;

  /**
   * Checks if all of the items matche a predicate.
   *
   * @tparam Predicate
   * @param predicate
   */
  template<typename Predicate>
  [[nodiscard]] auto all(Predicate &&predicate) const -> bool;

  /**
   * Checks if any of the items matches a predicate.
   *
   * @tparam Predicate
   * @param predicate
   */
  template<typename Predicate>
  [[nodiscard]] auto any(Predicate &&predicate) const -> bool;

  /**
   * Transforms an iterator into collection.
   *
   * @tparam Collection
   */
  template<typename Collection>
  [[nodiscard]] auto collect() const -> Collection {
    return static_cast<const Derived &>(*this).template collect_impl<Collection>();
  }

  /**
   * Counts number of iterations.
   */
  [[nodiscard]] auto count() const -> size_type {
    return static_cast<const Derived &>(*this).count_impl();
  }

  /**
   * Creates an iterator which gives the current iteration count as well as
   * the next value
   */
  [[nodiscard]] auto enumerate() const -> enumerate_iterator<Derived> {
    return static_cast<const Derived &>(*this).enumerate_impl();
  }

  /**
   * Creates an iterator which uses a predicate to determine if an element
   * should be yielded.
   *
   * @tparam Predicate
   * @param predicate
   */
  template<typename Predicate>
  [[nodiscard]] auto filter(Predicate &&predicate) const -> filter_iterator<Derived, Predicate> {
    return static_cast<const Derived &>(*this).filter_impl(std::forward<Predicate>(predicate));
  }
  /**
   * Searches for an element of an iterator that satisfies a predicate.
   *
   * @tparam Predicate
   * @param predicate
   */
  template<typename Predicate>
  [[nodiscard]] auto find(Predicate &&predicate) const -> std::optional<value_type>;

  /**
   * Creates an iterator that flattens nested structure.
   */
  [[nodiscard]] auto flatten() const -> flatten_iterator<Derived>;

  /**
   * Applies a function, producing a single, final value.
   *
   * @tparam Operator
   * @param initial
   * @param op
   */
  template<typename Operator>
  [[nodiscard]] auto fold(value_type initial, Operator &&op) const -> value_type;

  /**
   * Calls a callable on each element of an iterator.
   *
   * @tparam Callable
   * @param callable
   */
  template<typename Callable>
  auto for_each(Callable &&callable) const -> void;

  /**
   * Does something with each element of an iterator, passing the value on.
   *
   * @tparam Callable
   * @param callable
   */
  template<typename Callable>
  [[nodiscard]] auto inspect(Callable &&callable) const -> inspect_iterator<Derived, Callable> {
    return static_cast<const Derived &>(*this).inspect_impl(std::forward<Callable>(callable));
  }

  /**
   * Takes a callable and creates an iterator which calls that callable on
   * each element.
   *
   * @tparam Callable
   * @param callable
   */
  template<typename Callable>
  [[nodiscard]] auto map(Callable &&callable) const -> map_iterator<Derived, Callable> {
    return static_cast<const Derived &>(*this).map_impl(std::forward<Callable>(callable));
  }

  /**
   * Returns the maximum element of an iterator.
   */
  [[nodiscard]] auto max() const -> std::optional<value_type>;

  /**
   * Returns the minimum element of an iterator.
   */
  [[nodiscard]] auto min() const -> std::optional<value_type>;

  /**
   * Consumes an iterator, creating two collections from it.
   *
   * @tparam Collection
   * @tparam Predicate
   * @param predicate
   */
  template<typename Collection, typename Predicate>
  [[nodiscard]] auto partition(Predicate &&predicate) const -> std::tuple<Collection, Collection>;

  /**
   * Iterates over the entire iterator, multiplying all the elements.
   */
  [[nodiscard]] auto product() const -> value_type;


  /**
   * Iterates over the entire iterator, summing all the elements.
   */
  [[nodiscard]] auto sum() const -> value_type;

  /**
   * Creates an iterator that reverses traversal direction.
   */
  [[nodiscard]] auto rev() const -> rev_iterator<Derived>;

  /**
   * Creates an iterator that yields its first n elements.
   */
  [[nodiscard]] auto take(size_type n) const -> take_iterator<Derived>;

  /**
   * Returns currently pointed-to value.
   */
  [[nodiscard]] auto operator*() const -> decltype(auto) {
    return static_cast<const Derived &>(*this).const_deref_impl();
  }

  /**
   * Advances the iterator.
   */
  auto operator++() const -> decltype(auto) {
    return static_cast<const Derived &>(*this).preincrement_impl();
  }

  /**
   * Advances the iterator.
   */
  auto operator++(int) const -> decltype(auto) {
    return static_cast<const Derived &>(*this).postincrement_impl();
  }

  /**
   * Returns begin iterator.
   */
  [[nodiscard]] constexpr auto begin() const noexcept -> Derived {
    return static_cast<const Derived &>(*this).begin_impl();
  }

  /**
   * Returns cbegin iterator.
   */
  [[nodiscard]] constexpr auto cbegin() const noexcept -> Derived {
    return static_cast<const Derived &>(*this).cbegin_impl();
  }

  /**
   * Returns end iterator.
   */
  [[nodiscard]] constexpr auto end() const noexcept -> Derived {
    return static_cast<const Derived &>(*this).end_impl();
  }

  /**
   * Returns cend iterator.
   */
  [[nodiscard]] constexpr auto cend() const noexcept -> Derived {
    return static_cast<const Derived &>(*this).cend_impl();
  }
};

}// namespace ftl
