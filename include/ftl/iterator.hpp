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
class filter_iterator : public iterator_interface<filter_iterator<Item>, Item, std::size_t>
{
};

template<typename Item>
class flatten_iterator : public iterator_interface<flatten_iterator<Item>, Item, std::size_t>
{
};

template<typename Item>
class enumerate_iterator : public iterator_interface<enumerate_iterator<Item>, Item, std::size_t>
{
};

template<typename Item>
class inspect_iterator : public iterator_interface<inspect_iterator<Item>, Item, std::size_t>
{
};

template<typename Item>
class take_iterator : public iterator_interface<take_iterator<Item>, Item, std::size_t>
{
};

template<typename Derived, typename Item, typename SizeType>
class iterator_interface
{
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
  [[nodiscard]] bool all(Predicate &&predicate) const;

  /**
   * @brief Checks if any of the items matches a predicate.
  */
  template<typename Predicate>
  [[nodiscard]] bool any(Predicate &&predicate) const;

  /**
   * @brief Transforms an iterator into collection.
  */
  template<typename Collection>
  [[nodiscard]] Collection collect()
  {
    return static_cast<Derived &>(*this).template collect_impl<Collection>();
  }

  /**
   * @brief Counts number of iterations.
  */
  [[nodiscard]] size_type count() const
  {
    return static_cast<Derived &>(*this).count_impl();
  }

  /**
   * @brief Creates an iterator which gives the current iteration count as well as the next value
  */
  [[nodiscard]] enumerate_iterator<value_type> enumerate();

  /**
   * @brief Creates an iterator which uses a predicate to determine if an element should be yielded.
   * @tparam Predicate 
   * @param predicate 
  */
  template<typename Predicate>
  [[nodiscard]] filter_iterator<value_type> filter(Predicate &&predicate) const;

  /**
   * @brief Searches for an element of an iterator that satisfies a predicate.
   * @tparam Predicate 
   * @param predicate 
  */
  template<typename Predicate>
  [[nodiscard]] std::optional<value_type> find(Predicate &&predicate) const;

  /**
   * @brief Creates an iterator that flattens nested structure.
  */
  [[nodiscard]] flatten_iterator<value_type> flatten() const;

  /**
   * @brief Applies a function, producing a single, final value.
   * @tparam Operator 
   * @param initial 
   * @param op 
  */
  template<typename Operator>
  [[nodiscard]] value_type fold(value_type initial, Operator &&op);

  /**
   * @brief Calls a callable on each element of an iterator.
   * @tparam Callable 
   * @param callable 
  */
  template<typename Callable>
  void for_each(Callable &&callable);

  /**
   * @brief Does something with each element of an iterator, passing the value on.
   * @tparam Callable 
   * @param callable 
  */
  template<typename Callable>
  [[nodiscard]] inspect_iterator<value_type> inspect(Callable &&callable) const;

  /**
   * @brief Takes a callable and creates an iterator which calls that callable on each element.
   * @tparam Callable 
   * @param callable 
  */
  template<typename Callable>
  [[nodiscard]] map_iterator<Derived, Callable> map(Callable &&callable)
  {
    return static_cast<Derived &>(*this).map_impl(std::forward<Callable>(callable));
  }

  /**
   * @brief Returns the maximum element of an iterator.
  */
  [[nodiscard]] std::optional<value_type> max() const;

  /**
   * @brief Returns the minimum element of an iterator.
  */
  [[nodiscard]] std::optional<value_type> min() const;

  /**
   * @brief Consumes an iterator, creating two collections from it.
   * @tparam Collection 
   * @tparam Predicate 
   * @param predicate 
  */
  template<typename Collection, typename Predicate>
  [[nodiscard]] std::tuple<Collection, Collection> partition(Predicate &&predicate) const;

  /**
   * @brief Iterates over the entire iterator, multiplying all the elements.
  */
  [[nodiscard]] value_type product() const;


  /**
   * @brief Iterates over the entire iterator, summing all the elements.
  */
  [[nodiscard]] value_type sum() const;

  /**
   * @brief Reverses an iterator's direction.
   * @tparam Iterator 
  */
  template<typename Iterator>
  [[nodiscard]] Iterator rev() const;

  /**
   * @brief Creates an iterator that yields its first n elements.
  */
  [[nodiscard]] take_iterator<value_type> take(size_type n) const;

  /**
   * @brief Advances the iterator and returns the next value.
  */
  [[nodiscard]] std::optional<value_type> next()
  {
    return static_cast<Derived &>(*this).next_impl();
  }

  /**
   * @brief Returns currently pointed-to value.
  */

  [[nodiscard]] value_type operator*()
  {
    return static_cast<Derived &>(*this).deref_impl();
  };

  void operator++()
  {
    static_cast<Derived &>(*this).preincrement_impl();
  }

  [[nodiscard]] constexpr Derived begin() noexcept { return static_cast<Derived &>(*this).begin_impl(); }

  [[nodiscard]] constexpr Derived cbegin() const noexcept { return static_cast<Derived &>(*this).cbegin_impl(); }

  [[nodiscard]] constexpr Derived end() noexcept { return static_cast<Derived &>(*this).end_impl(); }

  [[nodiscard]] constexpr Derived cend() const noexcept { return static_cast<Derived &>(*this).cend_impl(); }
};

template<typename Derived, typename Item, typename SizeType>
class const_iterator_interface
{
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
  [[nodiscard]] bool all(Predicate &&predicate) const;

  /**
   * @brief Checks if any of the items matches a predicate.
  */
  template<typename Predicate>
  [[nodiscard]] bool any(Predicate &&predicate) const;

  /**
   * @brief Transforms an iterator into collection.
  */
  template<typename Collection>
  [[nodiscard]] Collection collect()
  {
    return static_cast<const Derived &>(*this).template collect_impl<Collection>();
  }

  /**
   * @brief Counts number of iterations.
  */
  [[nodiscard]] size_type count() const
  {
    return static_cast<const Derived &>(*this).count_impl();
  }

  /**
   * @brief Creates an iterator which gives the current iteration count as well as the next value
  */
  [[nodiscard]] enumerate_iterator<value_type> enumerate() const;

  /**
   * @brief Creates an iterator which uses a predicate to determine if an element should be yielded.
   * @tparam Predicate 
   * @param predicate 
  */
  template<typename Predicate>
  [[nodiscard]] filter_iterator<value_type> filter(Predicate &&predicate) const;

  /**
   * @brief Searches for an element of an iterator that satisfies a predicate.
   * @tparam Predicate 
   * @param predicate 
  */
  template<typename Predicate>
  [[nodiscard]] std::optional<value_type> find(Predicate &&predicate) const;

  /**
   * @brief Creates an iterator that flattens nested structure.
  */
  [[nodiscard]] flatten_iterator<value_type> flatten() const;

  /**
   * @brief Applies a function, producing a single, final value.
   * @tparam Operator 
   * @param initial 
   * @param op 
  */
  template<typename Operator>
  [[nodiscard]] value_type fold(value_type initial, Operator &&op) const;

  /**
   * @brief Calls a callable on each element of an iterator.
   * @tparam Callable 
   * @param callable 
  */
  template<typename Callable>
  void for_each(Callable &&callable) const;

  /**
   * @brief Does something with each element of an iterator, passing the value on.
   * @tparam Callable 
   * @param callable 
  */
  template<typename Callable>
  [[nodiscard]] inspect_iterator<value_type> inspect(Callable &&callable) const;

  /**
   * @brief Takes a callable and creates an iterator which calls that callable on each element.
   * @tparam Callable 
   * @param callable 
  */
  template<typename Callable>
  [[nodiscard]] map_iterator<Derived, Callable> map(Callable &&callable) const
  {
    return static_cast<const Derived &>(*this).map_impl(std::forward<Callable>(callable));
  }

  /**
   * @brief Returns the maximum element of an iterator.
  */
  [[nodiscard]] std::optional<value_type> max() const;

  /**
   * @brief Returns the minimum element of an iterator.
  */
  [[nodiscard]] std::optional<value_type> min() const;

  /**
   * @brief Consumes an iterator, creating two collections from it.
   * @tparam Collection 
   * @tparam Predicate 
   * @param predicate 
  */
  template<typename Collection, typename Predicate>
  [[nodiscard]] std::tuple<Collection, Collection> partition(Predicate &&predicate) const;

  /**
   * @brief Iterates over the entire iterator, multiplying all the elements.
  */
  [[nodiscard]] value_type product() const;


  /**
   * @brief Iterates over the entire iterator, summing all the elements.
  */
  [[nodiscard]] value_type sum() const;

  /**
   * @brief Reverses an iterator's direction.
   * @tparam Iterator 
  */
  template<typename Iterator>
  [[nodiscard]] Iterator rev() const;

  /**
   * @brief Creates an iterator that yields its first n elements.
  */
  [[nodiscard]] take_iterator<value_type> take(size_type n) const;

  /**
   * @brief Advances the iterator and returns the next value.
  */
  [[nodiscard]] std::optional<value_type> next() const
  {
    return static_cast<const Derived &>(*this).next_impl();
  }

  /**
   * @brief Returns currently pointed-to value.
  */

  [[nodiscard]] value_type operator*() const
  {
    return static_cast<const Derived &>(*this).deref_impl();
  };

  void operator++() const
  {
    static_cast<const Derived &>(*this).preincrement_impl();
  }

  [[nodiscard]] constexpr Derived begin() const noexcept { return static_cast<const Derived &>(*this).begin_impl(); }

  [[nodiscard]] constexpr Derived cbegin() const noexcept { return static_cast<const Derived &>(*this).cbegin_impl(); }

  [[nodiscard]] constexpr Derived end() const noexcept { return static_cast<const Derived &>(*this).end_impl(); }

  [[nodiscard]] constexpr Derived cend() const noexcept { return static_cast<const Derived &>(*this).cend_impl(); }
};

template<typename Iter, typename Callable>
class map_iterator : public iterator_interface<map_iterator<Iter, Callable>, typename Iter::value_type, typename Iter::size_type>
{
  friend iterator_interface<map_iterator<Iter, Callable>, typename Iter::value_type, typename Iter::size_type>;

public:
  using size_type = typename Iter::size_type;
  using value_type = typename Iter::value_type;
  using pointer = typename Iter::pointer;
  using reference = typename Iter::reference;
  using const_pointer = typename Iter::const_pointer;
  using const_reference = typename Iter::const_reference;

  map_iterator(Iter iterator, Callable callable)
    : iterator_{ std::move(iterator) },
      callable_{ std::move(callable) }
  {}

private:
  template<typename Collection>
  [[nodiscard]] Collection collect_impl() { return from_iterator_trait<map_iterator<Iter, Callable>, Collection>::from_iter(*this); }

  [[nodiscard]] constexpr size_type count_impl() const { return iterator_.count(); }

  template<typename NewCallable>
  [[nodiscard]] auto map_impl(NewCallable &&callable) -> map_iterator<map_iterator<Iter, Callable>, NewCallable>
  {
    return { *this, std::forward<NewCallable>(callable) };
  }

  [[nodiscard]] constexpr map_iterator<Iter, Callable> begin_impl() noexcept { return { iterator_.begin(), callable_ }; }

  [[nodiscard]] constexpr map_iterator<Iter, Callable> cbegin_impl() const noexcept { return { iterator_.begin(), callable_ }; }

  [[nodiscard]] constexpr map_iterator<Iter, Callable> end_impl() noexcept { return { iterator_.end(), callable_ }; }

  [[nodiscard]] constexpr map_iterator<Iter, Callable> cend_impl() const noexcept { return { iterator_.end(), callable_ }; }

  [[nodiscard]] constexpr value_type deref_impl() { return callable_(*iterator_); }

  void preincrement_impl() { ++iterator_; }

  [[nodiscard]] friend constexpr bool operator!=(const map_iterator<Iter, Callable> &lhs, const map_iterator<Iter, Callable> &rhs) { return lhs.iterator_ != rhs.iterator_; }

private:
  Iter iterator_;
  Callable callable_;
};

}// namespace ftl

template<typename Iter, typename Callable, typename Collection>
struct ftl::from_iterator_trait<ftl::map_iterator<Iter, Callable>, Collection>
{
  [[nodiscard]] constexpr static auto from_iter(ftl::map_iterator<Iter, Callable> &iter)
  {
    Collection result{};

    std::size_t i = 0;
    for (auto &&item : iter) {
      result[i] = item;
      ++i;
    }

    return result;
  }
};
