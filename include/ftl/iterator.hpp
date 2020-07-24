#pragma once

#include <cassert>
#include <tuple>
#include <optional>
#include <ftl/from_iterator_trait.hpp>

namespace ftl {

template<typename Item>
class iterator_interface;

template<typename Iter, typename Callable>
class map_iterator;

template<typename Item>
class filter_iterator : public iterator_interface<Item>
{
};

template<typename Item>
class flatten_iterator : public iterator_interface<Item>
{
};

template<typename Item>
class enumerate_iterator : public iterator_interface<Item>
{
};

template<typename Item>
class inspect_iterator : public iterator_interface<Item>
{
};

template<typename Item>
class take_iterator : public iterator_interface<Item>
{
};

template<typename Item>
class iterator_interface
{
public:
  using size_type = std::size_t;
  using value_type = std::remove_cv_t<Item>;
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
  [[nodiscard]] Collection collect();

  /**
   * @brief Counts number of iterations.
  */
  [[nodiscard]] virtual size_type count() const = 0;

  /**
   * @brief Creates an iterator which gives the current iteration count as well as the next value
  */
  [[nodiscard]] enumerate_iterator<Item> enumerate();

  /**
   * @brief Creates an iterator which uses a predicate to determine if an element should be yielded.
   * @tparam Predicate 
   * @param predicate 
  */
  template<typename Predicate>
  [[nodiscard]] filter_iterator<Item> filter(Predicate &&predicate) const;

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
  [[nodiscard]] flatten_iterator<Item> flatten() const;

  /**
   * @brief Applies a function, producing a single, final value.
   * @tparam Operator 
   * @param initial 
   * @param op 
  */
  template<typename Operator>
  [[nodiscard]] Item fold(Item initial, Operator &&op);

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
  [[nodiscard]] inspect_iterator<Item> inspect(Callable &&callable) const;

  /**
   * @brief Takes a callable and creates an iterator which calls that callable on each element.
   * @tparam Callable 
   * @param callable 
  */
  template<typename Callable>
  [[nodiscard]] map_iterator<Item, Callable> map([[maybe_unused]] Callable &&callable)
  {
    // TODO: should not compile
    assert(false);
    return {};
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
  [[nodiscard]] Item product() const;


  /**
   * @brief Iterates over the entire iterator, summing all the elements.
  */
  [[nodiscard]] Item sum() const;

  /**
   * @brief Reverses an iterator's direction.
   * @tparam Iterator 
  */
  template<typename Iterator>
  [[nodiscard]] Iterator rev() const;

  /**
   * @brief Creates an iterator that yields its first n elements.
  */
  [[nodiscard]] take_iterator<Item> take(size_type n) const;

  /**
   * @brief Advances the iterator and returns the next value.
  */
  [[nodiscard]] virtual std::optional<value_type> next() = 0;

  /**
   * @brief Returns currently pointed-to value.
  */

  [[nodiscard]] virtual value_type operator*() = 0;
};

template<typename Item>
class const_iterator_interface
{
public:
  using size_type = std::size_t;
  using value_type = std::remove_cv_t<Item>;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;

  virtual ~const_iterator_interface() = default;

  //const_iterator_interface(const const_iterator_interface &) = delete;

  //const_iterator_interface &operator=(const const_iterator_interface &) = delete;

  //const_iterator_interface(const_iterator_interface &&) = default;

  //const_iterator_interface &operator=(const_iterator_interface &&) = default;

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
  [[nodiscard]] Collection collect() const;

  /**
   * @brief Counts number of iterations.
  */
  [[nodiscard]] size_type count() const;

  /**
   * @brief Creates an iterator which gives the current iteration count as well as the next value
  */
  [[nodiscard]] enumerate_iterator<Item> enumerate();

  /**
   * @brief Creates an iterator which uses a predicate to determine if an element should be yielded.
   * @tparam Predicate 
   * @param predicate 
  */
  template<typename Predicate>
  [[nodiscard]] filter_iterator<Item> filter(Predicate &&predicate) const;

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
  [[nodiscard]] flatten_iterator<Item> flatten() const;

  /**
   * @brief Applies a function, producing a single, final value.
   * @tparam Operator 
   * @param initial 
   * @param op 
  */
  template<typename Operator>
  [[nodiscard]] Item fold(Item initial, Operator &&op);

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
  [[nodiscard]] inspect_iterator<Item> inspect(Callable &&callable) const;

  /**
   * @brief Takes a callable and creates an iterator which calls that callable on each element.
   * @tparam Callable 
   * @param callable 
  */
  template<typename Callable>
  [[nodiscard]] map_iterator<Item, Callable> map(Callable &&callable) const;

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
  [[nodiscard]] Item product() const;


  /**
   * @brief Iterates over the entire iterator, summing all the elements.
  */
  [[nodiscard]] Item sum() const;

  /**
   * @brief Reverses an iterator's direction.
   * @tparam Iterator 
  */
  template<typename Iterator>
  [[nodiscard]] Iterator rev() const;

  /**
   * @brief Creates an iterator that yields its first n elements.
  */
  [[nodiscard]] take_iterator<Item> take(size_type n) const;

  /**
   * @brief Advances the iterator and returns the next value.
  */
  [[nodiscard]] virtual std::optional<value_type> next() const = 0;
};

template<typename Iter, typename Callable>
class map_iterator : public iterator_interface<typename Iter::value_type>
{
public:
  using value_type = std::remove_cv_t<typename Iter::value_type>;

  map_iterator(Iter iterator, Callable callable)
    : iterator_{ std::move(iterator) },
      callable_{ std::move(callable) }
  {}

  [[nodiscard]] virtual std::optional<value_type> next() override
  {
    return iterator_.next();
  }

  template<typename Collection>
  [[nodiscard]] Collection collect()
  {
    return from_iterator_trait<map_iterator<Iter, Callable>, Collection>::from_iter(*this);
  }

  [[nodiscard]] constexpr map_iterator<Iter, Callable> begin() noexcept { return { iterator_.begin(), callable_ }; }

  [[nodiscard]] constexpr map_iterator<Iter, Callable> cbegin() const noexcept { return { iterator_.begin(), callable_ }; }

  [[nodiscard]] constexpr map_iterator<Iter, Callable> end() noexcept { return { iterator_.end(), callable_ }; }

  [[nodiscard]] constexpr map_iterator<Iter, Callable> cend() const noexcept { return { iterator_.end(), callable_ }; }

  [[nodiscard]] constexpr typename Iter::value_type operator*() override { return callable_(*iterator_); }

  [[nodiscard]] constexpr typename Iter::size_type count() const override { return iterator_.count(); }

  constexpr void operator++()
  {
    ++iterator_;
  }

  [[nodiscard]] friend constexpr bool operator!=(const map_iterator<Iter, Callable> &lhs, const map_iterator<Iter, Callable> &rhs)
  {
    return lhs.iterator_ != rhs.iterator_;
  }

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
