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
class flatten_iterator : public iterator_interface<flatten_iterator<Iter>, typename Iter::value_type, std::size_t> {};

template<typename Iter>
class enumerate_iterator;

template<typename Iter, typename Callable>
class inspect_iterator;

template<typename Iter>
class take_iterator : public iterator_interface<take_iterator<Iter>, typename Iter::value_type, std::size_t> {};

template<typename Iter>
class rev_iterator : public iterator_interface<rev_iterator<Iter>, typename Iter::value_type, std::size_t> {};

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

  template<typename Predicate>
  [[nodiscard]] auto all(Predicate &&predicate) const -> bool;

  template<typename Predicate>
  [[nodiscard]] auto any(Predicate &&predicate) const -> bool;

  template<typename Collection>
  [[nodiscard]] auto collect() const -> Collection {
    return from_iterator_trait<Derived, Collection>::from_iter(static_cast<const Derived &>(*this));
  }

  [[nodiscard]] auto count() const -> size_type {
    return static_cast<const Derived &>(*this).count_impl();
  }

  [[nodiscard]] auto enumerate() const -> enumerate_iterator<Derived> {
    return { static_cast<const Derived &>(*this) };
  }

  template<typename Predicate>
  [[nodiscard]] auto filter(Predicate &&predicate) const -> filter_iterator<Derived, Predicate> {
    return { static_cast<const Derived &>(*this), std::forward<Callable>(callable) };
  }

  template<typename Predicate>
  [[nodiscard]] auto find(Predicate &&predicate) const -> std::optional<value_type>;

  [[nodiscard]] auto flatten() const -> flatten_iterator<Derived>;

  template<typename Operator>
  [[nodiscard]] auto fold(value_type initial, Operator &&op) const -> value_type;

  template<typename Callable>
  auto for_each(Callable &&callable) const -> void;

  template<typename Callable>
  [[nodiscard]] auto inspect(Callable &&callable) const -> inspect_iterator<Derived, Callable> {
    return { static_cast<const Derived &>(*this), std::forward<Callable>(callable) };
  }

  template<typename Callable>
  [[nodiscard]] auto map(Callable &&callable) const -> map_iterator<Derived, Callable> {
    return { static_cast<const Derived &>(*this), std::forward<Callable>(callable) };
  }

  [[nodiscard]] auto max() const -> std::optional<value_type>;

  [[nodiscard]] auto min() const -> std::optional<value_type>;

  template<typename Collection, typename Predicate>
  [[nodiscard]] auto partition(Predicate &&predicate) const -> std::tuple<Collection, Collection>;

  [[nodiscard]] auto product() const -> value_type;

  [[nodiscard]] auto sum() const -> value_type;

  [[nodiscard]] auto rev() const -> rev_iterator<Derived>;

  [[nodiscard]] auto take(size_type n) const -> take_iterator<Derived>;

  [[nodiscard]] constexpr auto begin() const noexcept -> Derived {
    return static_cast<const Derived &>(*this).begin_impl();
  }

  [[nodiscard]] constexpr auto cbegin() const noexcept -> Derived {
    return static_cast<const Derived &>(*this).cbegin_impl();
  }

  [[nodiscard]] constexpr auto end() const noexcept -> Derived {
    return static_cast<const Derived &>(*this).end_impl();
  }

  [[nodiscard]] constexpr auto cend() const noexcept -> Derived {
    return static_cast<const Derived &>(*this).cend_impl();
  }

  [[nodiscard]] auto operator*() const -> decltype(auto) {
    return static_cast<const Derived &>(*this).const_deref_impl();
  }

  auto operator++() const -> decltype(auto) {
    return static_cast<const Derived &>(*this).const_preincrement_impl();
  }

  auto operator++(int) const -> decltype(auto) {
    auto tmp = static_cast<const Derived &>(*this);

    ++static_cast<const Derived &>(*this);

    return tmp;
  }
};

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

  template<typename Predicate>
  [[nodiscard]] auto all(Predicate &&predicate) const -> bool;

  template<typename Predicate>
  [[nodiscard]] auto any(Predicate &&predicate) const -> bool;

  template<typename Collection>
  [[nodiscard]] auto collect() const -> Collection {
    return from_iterator_trait<Derived, Collection>::from_iter(static_cast<const Derived &>(*this));
  }

  [[nodiscard]] auto count() const -> size_type {
    return static_cast<const Derived &>(*this).count_impl();
  }

  [[nodiscard]] auto enumerate() const -> enumerate_iterator<Derived> {
    return { static_cast<const Derived &>(*this) };
  }

  template<typename Predicate>
  [[nodiscard]] auto filter(Predicate &&predicate) const -> filter_iterator<Derived, Predicate> {
    return { static_cast<const Derived &>(*this), std::forward<Callable>(callable) };
  }

  template<typename Predicate>
  [[nodiscard]] auto find(Predicate &&predicate) const -> std::optional<value_type>;

  [[nodiscard]] auto flatten() const -> flatten_iterator<Derived>;

  template<typename Operator>
  [[nodiscard]] auto fold(value_type initial, Operator &&op) const -> value_type;

  template<typename Callable>
  auto for_each(Callable &&callable) const -> void;

  template<typename Callable>
  [[nodiscard]] auto inspect(Callable &&callable) const -> inspect_iterator<Derived, Callable> {
    return { static_cast<const Derived &>(*this), std::forward<NewCallable>(callable) };
  }

  template<typename Callable>
  [[nodiscard]] auto map(Callable &&callable) const -> map_iterator<Derived, Callable> {
    return { static_cast<const Derived &>(*this), std::forward<Callable>(callable) };
  }

  [[nodiscard]] auto max() const -> std::optional<value_type>;

  [[nodiscard]] auto min() const -> std::optional<value_type>;

  template<typename Collection, typename Predicate>
  [[nodiscard]] auto partition(Predicate &&predicate) const -> std::tuple<Collection, Collection>;

  [[nodiscard]] auto product() const -> value_type;

  [[nodiscard]] auto sum() const -> value_type;

  [[nodiscard]] auto rev() const -> rev_iterator<Derived>;

  [[nodiscard]] auto take(size_type n) const -> take_iterator<Derived>;

  [[nodiscard]] constexpr auto begin() noexcept -> Derived {
    return static_cast<Derived &>(*this).begin_impl();
  }

  [[nodiscard]] constexpr auto begin() const noexcept -> Derived {
    return static_cast<const Derived &>(*this).begin_impl();
  }

  [[nodiscard]] constexpr auto cbegin() const noexcept -> Derived {
    return static_cast<const Derived &>(*this).cbegin_impl();
  }

  [[nodiscard]] constexpr auto end() noexcept -> Derived {
    return static_cast<Derived &>(*this).end_impl();
  }

  [[nodiscard]] constexpr auto end() const noexcept -> Derived {
    return static_cast<const Derived &>(*this).end_impl();
  }

  [[nodiscard]] constexpr auto cend() const noexcept -> Derived {
    return static_cast<const Derived &>(*this).cend_impl();
  }

  [[nodiscard]] auto operator*() -> decltype(auto) {
    return static_cast<Derived &>(*this).deref_impl();
  }


  [[nodiscard]] auto operator*() const -> decltype(auto) {
    return static_cast<const Derived &>(*this).const_deref_impl();
  }

  auto operator++() -> decltype(auto) {
    return static_cast<Derived &>(*this).preincrement_impl();
  }

  auto operator++() const -> decltype(auto) {
    return static_cast<const Derived &>(*this).const_preincrement_impl();
  }

  auto operator++(int) -> decltype(auto) {
    auto tmp = static_cast<Derived &>(*this);

    ++static_cast<Derived &>(*this);

    return tmp;
  }

  auto operator++(int) const -> decltype(auto) {
    auto tmp = static_cast<const Derived &>(*this);

    ++static_cast<const Derived &>(*this);

    return tmp;
  }
};

}// namespace ftl
