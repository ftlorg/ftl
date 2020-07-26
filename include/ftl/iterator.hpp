#pragma once

#include <cassert>
#include <tuple>
#include <optional>
#include <ftl/from_iterator_trait.hpp>

namespace ftl {

template<typename Derived, typename Item, typename Size>
class iterator_interface;

template<typename Iter, typename Callable>
class map_iterator;

template<typename Item>
class filter_iterator : public iterator_interface<filter_iterator<Item>, Item, std::size_t> {};

template<typename Item>
class flatten_iterator : public iterator_interface<flatten_iterator<Item>, Item, std::size_t> {};

template<typename Item>
class enumerate_iterator : public iterator_interface<enumerate_iterator<Item>, Item, std::size_t> {};

template<typename Item>
class inspect_iterator : public iterator_interface<inspect_iterator<Item>, Item, std::size_t> {};

template<typename Item>
class take_iterator : public iterator_interface<take_iterator<Item>, Item, std::size_t> {};

template<typename Item>
class rev_iterator : public iterator_interface<rev_iterator<Item>, Item, std::size_t> {};

template<typename Derived, typename Item, typename SizeType>
class iterator_interface {
public:
  using size_type = SizeType;
  using value_type = typename std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;

  virtual ~iterator_interface() = default;

  /**
   * @brief Checks if all of the items matche a predicate.
   */
  template<typename Predicate>
  [[nodiscard]] auto all(Predicate &&predicate) const -> bool;

  /**
   * @brief Checks if any of the items matches a predicate.
   */
  template<typename Predicate>
  [[nodiscard]] auto any(Predicate &&predicate) const -> bool;

  /**
   * @brief Transforms an iterator into collection.
   */
  template<typename Collection>
  [[nodiscard]] auto collect() -> Collection {
    return static_cast<Derived &>(*this).template collect_impl<Collection>();
  }

  /**
   * @brief Counts number of iterations.
   */
  [[nodiscard]] auto count() const -> size_type {
    return static_cast<const Derived &>(*this).count_impl();
  }

  /**
   * @brief Creates an iterator which gives the current iteration count as well as
   * the next value
   */
  [[nodiscard]] auto enumerate() -> enumerate_iterator<value_type>;

  /**
   * @brief Creates an iterator which uses a predicate to determine if an element
   * should be yielded.
   * @tparam Predicate
   * @param predicate
   */
  template<typename Predicate>
  [[nodiscard]] auto filter(Predicate &&predicate) const -> filter_iterator<value_type>;

  /**
   * @brief Searches for an element of an iterator that satisfies a predicate.
   * @tparam Predicate
   * @param predicate
   */
  template<typename Predicate>
  [[nodiscard]] auto find(Predicate &&predicate) const -> std::optional<value_type>;

  /**
   * @brief Creates an iterator that flattens nested structure.
   */
  [[nodiscard]] auto flatten() const -> flatten_iterator<value_type>;

  /**
   * @brief Applies a function, producing a single, final value.
   * @tparam Operator
   * @param initial
   * @param op
   */
  template<typename Operator>
  [[nodiscard]] auto fold(value_type initial, Operator &&op) -> value_type;

  /**
   * @brief Calls a callable on each element of an iterator.
   * @tparam Callable
   * @param callable
   */
  template<typename Callable>
  auto for_each(Callable &&callable) -> void;

  /**
   * @brief Does something with each element of an iterator, passing the value on.
   * @tparam Callable
   * @param callable
   */
  template<typename Callable>
  [[nodiscard]] auto inspect(Callable &&callable) const -> inspect_iterator<value_type>;

  /**
   * @brief Takes a callable and creates an iterator which calls that callable on
   * each element.
   * @tparam Callable
   * @param callable
   */
  template<typename Callable>
  [[nodiscard]] auto map(Callable &&callable) -> map_iterator<Derived, Callable> {
    return static_cast<Derived &>(*this).map_impl(std::forward<Callable>(callable));
  }

  /**
   * @brief Returns the maximum element of an iterator.
   */
  [[nodiscard]] auto max() const -> std::optional<value_type>;

  /**
   * @brief Returns the minimum element of an iterator.
   */
  [[nodiscard]] auto min() const -> std::optional<value_type>;

  /**
   * @brief Consumes an iterator, creating two collections from it.
   * @tparam Collection
   * @tparam Predicate
   * @param predicate
   */
  template<typename Collection, typename Predicate>
  [[nodiscard]] auto partition(Predicate &&predicate) const -> std::tuple<Collection, Collection>;

  /**
   * @brief Iterates over the entire iterator, multiplying all the elements.
   */
  [[nodiscard]] auto product() const -> value_type;


  /**
   * @brief Iterates over the entire iterator, summing all the elements.
   */
  [[nodiscard]] auto sum() const -> value_type;

  /**
   * @brief Reverses an iterator's direction.
   * @tparam Iterator
   */
  [[nodiscard]] auto rev() const -> rev_iterator<Item>;

  /**
   * @brief Creates an iterator that yields its first n elements.
   */
  [[nodiscard]] auto take(size_type n) const -> take_iterator<value_type>;

  /**
   * @brief Advances the iterator and returns the next value.
   */
  [[nodiscard]] auto next() -> std::optional<value_type> {
    return static_cast<Derived &>(*this).next_impl();
  }

  /**
   * @brief Returns currently pointed-to value.
   */
  [[nodiscard]] auto operator*() -> decltype(auto) {
    return static_cast<Derived &>(*this).deref_impl();
  };

  /**
   * @brief Returns currently pointed-to value.
   */
  [[nodiscard]] auto operator*() const -> decltype(auto) {
    return static_cast<const Derived &>(*this).const_deref_impl();
  };

  /**
   * @brief Advances the iterator.
   */
  auto operator++() const -> void {
    static_cast<const Derived &>(*this).preincrement_impl();
  }

  /**
   * @brief Returns begin iterator.
   */
  [[nodiscard]] constexpr auto begin() noexcept -> Derived {
    return static_cast<Derived &>(*this).begin_impl();
  }

  /**
   * @brief Returns begin iterator.
   */
  [[nodiscard]] constexpr auto begin() const noexcept -> Derived {
    return cbegin();
  }

  /**
   * @brief Returns cbegin iterator.
   */
  [[nodiscard]] constexpr auto cbegin() const noexcept -> Derived {
    return static_cast<const Derived &>(*this).cbegin_impl();
  }

  /**
   * @brief Returns end iterator.
   */
  [[nodiscard]] constexpr auto end() noexcept -> Derived {
    return static_cast<Derived &>(*this).end_impl();
  }

  /**
   * @brief Returns end iterator.
   */
  [[nodiscard]] constexpr auto end() const noexcept -> Derived {
    return cend();
  }

  /**
   * @brief Returns cend iterator.
   */
  [[nodiscard]] constexpr auto cend() const noexcept -> Derived {
    return static_cast<const Derived &>(*this).cend_impl();
  }
};

template<typename Derived, typename Item, typename SizeType>
class const_iterator_interface {
public:
  using size_type = SizeType;
  using value_type = typename std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;

  virtual ~const_iterator_interface() = default;

  /**
   * @brief Checks if all of the items matche a predicate.
   */
  template<typename Predicate>
  [[nodiscard]] auto all(Predicate &&predicate) const -> bool;

  /**
   * @brief Checks if any of the items matches a predicate.
   */
  template<typename Predicate>
  [[nodiscard]] auto any(Predicate &&predicate) const -> bool;

  /**
   * @brief Transforms an iterator into collection.
   */
  template<typename Collection>
  [[nodiscard]] auto collect() const -> Collection {
    return static_cast<const Derived &>(*this).template collect_impl<Collection>();
  }

  /**
   * @brief Counts number of iterations.
   */
  [[nodiscard]] auto count() const -> size_type {
    return static_cast<const Derived &>(*this).count_impl();
  }

  /**
   * @brief Creates an iterator which gives the current iteration count as well as
   * the next value
   */
  [[nodiscard]] auto enumerate() const -> enumerate_iterator<value_type>;

  /**
   * @brief Creates an iterator which uses a predicate to determine if an element
   * should be yielded.
   * @tparam Predicate
   * @param predicate
   */
  template<typename Predicate>
  [[nodiscard]] auto filter(Predicate &&predicate) const -> filter_iterator<value_type>;

  /**
   * @brief Searches for an element of an iterator that satisfies a predicate.
   * @tparam Predicate
   * @param predicate
   */
  template<typename Predicate>
  [[nodiscard]] auto find(Predicate &&predicate) const -> std::optional<value_type>;

  /**
   * @brief Creates an iterator that flattens nested structure.
   */
  [[nodiscard]] auto flatten() const -> flatten_iterator<value_type>;

  /**
   * @brief Applies a function, producing a single, final value.
   * @tparam Operator
   * @param initial
   * @param op
   */
  template<typename Operator>
  [[nodiscard]] auto fold(value_type initial, Operator &&op) const -> value_type;

  /**
   * @brief Calls a callable on each element of an iterator.
   * @tparam Callable
   * @param callable
   */
  template<typename Callable>
  auto for_each(Callable &&callable) const -> void;

  /**
   * @brief Does something with each element of an iterator, passing the value on.
   * @tparam Callable
   * @param callable
   */
  template<typename Callable>
  [[nodiscard]] auto inspect(Callable &&callable) const -> inspect_iterator<value_type>;

  /**
   * @brief Takes a callable and creates an iterator which calls that callable on
   * each element.
   * @tparam Callable
   * @param callable
   */
  template<typename Callable>
  [[nodiscard]] auto map(Callable &&callable) const -> map_iterator<Derived, Callable> {
    return static_cast<const Derived &>(*this).map_impl(std::forward<Callable>(callable));
  }

  /**
   * @brief Returns the maximum element of an iterator.
   */
  [[nodiscard]] auto max() const -> std::optional<value_type>;

  /**
   * @brief Returns the minimum element of an iterator.
   */
  [[nodiscard]] auto min() const -> std::optional<value_type>;

  /**
   * @brief Consumes an iterator, creating two collections from it.
   * @tparam Collection
   * @tparam Predicate
   * @param predicate
   */
  template<typename Collection, typename Predicate>
  [[nodiscard]] auto partition(Predicate &&predicate) const -> std::tuple<Collection, Collection>;

  /**
   * @brief Iterates over the entire iterator, multiplying all the elements.
   */
  [[nodiscard]] auto product() const -> value_type;


  /**
   * @brief Iterates over the entire iterator, summing all the elements.
   */
  [[nodiscard]] auto sum() const -> value_type;

  /**
   * @brief Creates an iterator that reverses traversal direction.
   */
  [[nodiscard]] auto rev() const -> rev_iterator<Item>;

  /**
   * @brief Creates an iterator that yields its first n elements.
   */
  [[nodiscard]] auto take(size_type n) const -> take_iterator<value_type>;

  /**
   * @brief Advances the iterator and returns the next value.
   */
  [[nodiscard]] auto next() const -> std::optional<value_type> {
    return static_cast<const Derived &>(*this).next_impl();
  }

  /**
   * @brief Returns currently pointed-to value.
   */
  [[nodiscard]] auto operator*() const -> decltype(auto) {
    return static_cast<const Derived &>(*this).const_deref_impl();
  };

  /**
   * @brief Advances the iterator.
   */
  auto operator++() const -> void {
    static_cast<const Derived &>(*this).preincrement_impl();
  }

  /**
   * @brief Returns begin iterator.
   */
  [[nodiscard]] constexpr auto begin() const noexcept -> Derived {
    return static_cast<const Derived &>(*this).begin_impl();
  }

  /**
   * @brief Returns cbegin iterator.
   */
  [[nodiscard]] constexpr auto cbegin() const noexcept -> Derived {
    return static_cast<const Derived &>(*this).cbegin_impl();
  }

  /**
   * @brief Returns end iterator.
   */
  [[nodiscard]] constexpr auto end() const noexcept -> Derived {
    return static_cast<const Derived &>(*this).end_impl();
  }

  /**
   * @brief Returns cend iterator.
   */
  [[nodiscard]] constexpr auto cend() const noexcept -> Derived {
    return static_cast<const Derived &>(*this).cend_impl();
  }
};

template<typename Iter, typename Callable>
class map_iterator
  : public const_iterator_interface<map_iterator<Iter, Callable>, typename Iter::value_type, typename Iter::size_type> {

  friend const_iterator_interface<map_iterator<Iter, Callable>, typename Iter::value_type, typename Iter::size_type>;

public:
  using size_type = typename Iter::size_type;
  using value_type = typename Iter::value_type;
  using pointer = typename Iter::pointer;
  using reference = typename Iter::reference;
  using const_pointer = typename Iter::const_pointer;
  using const_reference = typename Iter::const_reference;

  map_iterator(Iter iterator, Callable callable) : iterator_{ std::move(iterator) }, callable_{ std::move(callable) } {
  }

private:
  template<typename Collection>
  [[nodiscard]] auto collect_impl() const -> Collection {
    return from_iterator_trait<map_iterator<Iter, Callable>, Collection>::from_iter(*this);
  }

  [[nodiscard]] constexpr auto count_impl() const -> size_type {
    return iterator_.count();
  }

  template<typename NewCallable>
  [[nodiscard]] auto map_impl(NewCallable &&callable) const -> map_iterator<map_iterator<Iter, Callable>, NewCallable> {
    return { *this, std::forward<NewCallable>(callable) };
  }

  [[nodiscard]] constexpr auto begin_impl() const noexcept -> map_iterator<Iter, Callable> {
    return { iterator_.cbegin(), callable_ };
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> map_iterator<Iter, Callable> {
    return { iterator_.cbegin(), callable_ };
  }

  [[nodiscard]] constexpr auto end_impl() const noexcept -> map_iterator<Iter, Callable> {
    return { iterator_.cend(), callable_ };
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> map_iterator<Iter, Callable> {
    return { iterator_.cend(), callable_ };
  }

  [[nodiscard]] constexpr auto const_deref_impl() const -> value_type {
    return callable_(*iterator_);
  }

  auto preincrement_impl() const -> void {
    ++iterator_;
  }

  [[nodiscard]] friend constexpr auto operator!=(const map_iterator<Iter, Callable> &lhs,
    const map_iterator<Iter, Callable> &rhs) -> bool {
    return lhs.iterator_ != rhs.iterator_;
  }

private:
  Iter iterator_;
  Callable callable_;
};

}// namespace ftl

template<typename Iter, typename Callable, typename Collection>
struct ftl::from_iterator_trait<ftl::map_iterator<Iter, Callable>, Collection> {
  [[nodiscard]] constexpr static auto from_iter(const ftl::map_iterator<Iter, Callable> &iter) -> Collection {
    Collection result{};

    std::size_t i = 0;
    for (auto &&item : iter) {
      result[i] = item;
      ++i;
    }

    return result;
  }
};
