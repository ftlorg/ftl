
// Copyright Grzegorz Litarowicz and Lukasz Gut 2020 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <ftl/from_iterator_trait.hpp>
#include <ftl/iterator_traits.hpp>
#include <ftl/is_container.hpp>
#include <algorithm>
#include <memory>
#include <cassert>
#include <tuple>
#include <optional>
#include <numeric>

namespace ftl {

template<typename Derived>
class iterator_interface;

template<typename Iter, typename Callable>
class map_iterator;

template<typename Iter, typename Callable>
class filter_iterator;

template<typename Iter, bool is_container>
class flatten_iterator;

template<typename Iter>
class enumerate_iterator;

template<typename Iter, typename Callable>
class inspect_iterator;

template<typename Iter>
class take_iterator;

template<typename Derived>
class iterator_interface {
public:
  using size_type = typename std::iterator_traits<Derived>::size_type;
  using value_type = typename std::iterator_traits<Derived>::value_type;
  using pointer = value_type *;
  using reference = value_type &;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;

  virtual ~iterator_interface() = default;


  template<typename Predicate>
  [[nodiscard]] auto any(Predicate &&predicate) const -> bool {
    for (auto &&x : static_cast<const Derived &>(*this)) {
      if (predicate(x)) { return true; }
    }

    return false;
  }

  template<typename Collection>
  [[nodiscard]] auto collect() const -> Collection {
    return from_iterator_trait<Derived, Collection>::from_iter(static_cast<const Derived &>(*this));
  }

  template<typename Collection>
  [[nodiscard]] auto collect_sorted() const -> Collection {
    return from_iterator_trait<Derived, Collection>::from_iter_sorted(static_cast<const Derived &>(*this));
  }

  template<typename Collection>
  auto collect_into(Collection &collection) const -> void {
    return from_iterator_trait<Derived, Collection>::from_iter_into_collection(
      static_cast<const Derived &>(*this), collection);
  }

  [[nodiscard]] constexpr auto count() const -> typename std::iterator_traits<Derived>::size_type {
    return static_cast<typename std::iterator_traits<Derived>::size_type>(
      std::distance(static_cast<const Derived &>(*this).begin(), static_cast<const Derived &>(*this).end()));
  }

  [[nodiscard]] auto enumerate() const -> enumerate_iterator<Derived> {
    return { static_cast<const Derived &>(*this) };
  }

  template<typename Predicate>
  [[nodiscard]] auto filter(Predicate &&predicate) const -> filter_iterator<Derived, Predicate> {
    return { static_cast<const Derived &>(*this), std::forward<Predicate>(predicate) };
  }

  template<typename Predicate>
  [[nodiscard]] auto find(Predicate &&predicate) const -> std::optional<value_type> {
    for (const auto &elem : static_cast<const Derived &>(*this)) {
      if (predicate(elem)) { return std::optional<value_type>(elem); }
    }
    return std::nullopt;
  }

  [[nodiscard]] auto flatten() const -> flatten_iterator<Derived> {
    return flatten_iterator<Derived>{ static_cast<const Derived &>(*this) };
  }

  template<typename Initial, typename Operator>
  [[nodiscard]] auto fold(const Initial &initial, Operator &&op) const -> Initial {
    auto init = initial;

    for (auto &&x : static_cast<const Derived &>(*this)) { init = op(std::cref(init), x); }

    return init;
  }

  template<typename Predicate>
  [[nodiscard]] auto all(Predicate &&predicate) const -> bool {
    for (const auto &element : static_cast<const Derived &>(*this)) {
      if (!predicate(element)) { return false; }
    }
    return true;
  }

  template<typename Callable>
  auto for_each(Callable &&callable) const -> void {
    for (auto &&element : static_cast<const Derived &>(*this)) { callable(element); }
  }

  template<typename Callable>
  [[nodiscard]] auto inspect(Callable &&callable) const -> inspect_iterator<Derived, Callable> {
    return { static_cast<const Derived &>(*this), std::forward<Callable>(callable) };
  }

  template<typename Callable>
  [[nodiscard]] auto map(Callable &&callable) const -> map_iterator<Derived, Callable> {
    return { static_cast<const Derived &>(*this), std::forward<Callable>(callable) };
  }

  [[nodiscard]] auto max() const -> std::optional<value_type> {
    const auto begin = std::begin(static_cast<const Derived &>(*this));
    const auto end = std::end(static_cast<const Derived &>(*this));

    if (begin != end) {
      auto max = *begin;

      for (auto it = ++begin; it != end; it++) {
        const auto &val = *it;
        if (val > max) { max = val; }
      }

      return { max };
    }

    return std::nullopt;
  }

  [[nodiscard]] auto min() const -> std::optional<value_type> {
    const auto begin = std::begin(static_cast<const Derived &>(*this));
    const auto end = std::end(static_cast<const Derived &>(*this));

    if (begin != end) {
      auto min = *begin;

      for (auto it = ++begin; it != end; it++) {
        const auto &val = *it;
        if (val < min) { min = val; }
      }

      return { min };
    }

    return std::nullopt;
  }

  template<typename Collection, typename Predicate>
  [[nodiscard]] auto partition(Predicate &&predicate) const -> std::tuple<Collection, Collection> {
    Collection coll1{};
    Collection coll2{};

    for (const auto &x : static_cast<const Derived &>(*this)) {
      if (predicate(x)) {
        coll1.insert(std::end(coll1), x);
      } else {
        coll2.insert(std::end(coll2), x);
      }
    }

    return { coll1, coll2 };
  }

  [[nodiscard]] auto product() const -> value_type {
    auto result = static_cast<value_type>(1);
    for (const auto &element : static_cast<const Derived &>(*this)) { result *= element; }
    return result;
  }

  [[nodiscard]] auto sum() const -> value_type {
    return std::accumulate(
      static_cast<const Derived &>(*this).begin(), static_cast<const Derived &>(*this).end(), value_type{});
  }

  [[nodiscard]] auto take(size_type n) const -> take_iterator<Derived> {
    return { static_cast<const Derived &>(*this), n };
  }

private:
  iterator_interface() = default;
  friend Derived;
};

}// namespace ftl
