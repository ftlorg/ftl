#pragma once

#include <optional>
#include <tuple>

namespace ftl {

  template<typename Item>
class filter_iterator {};

template<typename Item>
class flatten_iterator{};

template<typename Item>
class enumerate_iterator{};

template<typename Item>
class inspect_iterator{};

template<typename Item>
class map_iterator{};

template<typename Item>
class take_iterator{};

template<typename Item>
class iterator_interface
{
public:
  using size_type = std::size_t;

  /**
   * @brief Advances the iterator and returns the next value.
  */
  [[nodiscard]] virtual std::optional<Item> next() = 0;

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
  [[nodiscard]] std::optional<Item> find(Predicate &&predicate) const;

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
  [[nodiscard]] map_iterator<Item> map(Callable &&callable) const;

  /**
   * @brief Returns the maximum element of an iterator.
  */
  [[nodiscard]] std::optional<Item> max() const;

  /**
   * @brief Returns the minimum element of an iterator.
  */
  [[nodiscard]] std::optional<Item> min() const;

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
};

template<typename Item>
class array_iterator : public iterator_interface<Item>
{
public:
  using iterator_category = /* */ void;
  using value_type = std::remove_cv_t<Item>;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type*;
  using reference = value_type&;
  using size_type = std::size_t;

  array_iterator(const Item * const begin, const Item * const end) : begin_{begin}, end_{end} {}

  [[nodiscard]] std::optional<Item> next() override {
    ++position_;

    if(begin_ + postion_ != end_)
      return { begin_[position_] };

    return std::nullopt;
  }

private:
  mutable size_type position_;
  Item * const begin_;
  Item * const end_;
};

template<typename Item>
class reverse_array_iterator : public iterator_interface<Item>
{
public:
  using iterator_category = /* */ void;
  using value_type = std::remove_cv_t<Item>;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type*;
  using reference = value_type&;
  using size_type = std::size_t;

  reverse_array_iterator(const Item * const rbegin, const Item * const rend) : rbegin_{rbegin}, rend_{rend}, position_{std::distance(rbegin, rend)} {}

  [[nodiscard]] virtual std::optional<Item> next() override {
    --position_;

    if(rbegin_ + postion_ != rend_)
      return { rbegin_[position_] };

    return std::nullopt;
  }

private:
  mutable size_type position_;
  Item * const rbegin_;
  Item * const rend_;
};

}// namespace ftl
