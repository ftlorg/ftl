#pragma once

#include <type_traits>
#include <ftl/iterator_interface.hpp>
#include <ftl/iterator_member_provider.hpp>

namespace ftl {

template<typename Iter, typename Callable>
class map_iterator
  : public const_iterator_interface<map_iterator<Iter, Callable>, typename Iter::value_type, typename Iter::size_type>
  , public iterator_member_provider<map_iterator<Iter, Callable>, typename Iter::iterator_category> {

  friend const_iterator_interface<map_iterator<Iter, Callable>, typename Iter::value_type, typename Iter::size_type>;
  friend iterator_member_provider<map_iterator<Iter, Callable>, typename Iter::iterator_category>;

public:
  using difference_type = typename Iter::difference_type;
  using value_type = typename Iter::value_type;
  using pointer = typename Iter::pointer;
  using reference = typename Iter::reference;
  using const_pointer = typename Iter::const_pointer;
  using const_reference = typename Iter::const_reference;
  using inherited_iterator_category = typename Iter::iterator_category;
  using iterator_category = inherited_iterator_category;
  using size_type = typename Iter::size_type;

  map_iterator(Iter iterator, Callable callable) : iterator_{ std::move(iterator) }, callable_{ std::move(callable) } {
  }

  // private:
  template<typename Collection>
  [[nodiscard]] auto collect_impl() const -> Collection {
    return from_iterator_trait<map_iterator<Iter, Callable>, Collection>::from_iter(*this);
  }

  [[nodiscard]] constexpr auto count_impl() const -> size_type {
    return iterator_.count();
  }

  [[nodiscard]] auto enumerate_impl() const -> enumerate_iterator<map_iterator<Iter, Callable>> {
    return { *this };
  }

  template<typename NewCallable>
  [[nodiscard]] auto inspect_impl(NewCallable &&callable) const
    -> inspect_iterator<map_iterator<Iter, Callable>, NewCallable> {
    return { *this, std::forward<NewCallable>(callable) };
  }

  template<typename NewCallable>
  [[nodiscard]] auto map_impl(NewCallable &&callable) const -> map_iterator<map_iterator<Iter, Callable>, NewCallable> {
    return { *this, std::forward<NewCallable>(callable) };
  }

  template<typename NewCallable>
  [[nodiscard]] auto filter_impl(NewCallable &&callable) const
    -> filter_iterator<map_iterator<Iter, Callable>, NewCallable> {
    return { *this, std::forward<NewCallable>(callable) };
  }

  [[nodiscard]] constexpr auto deref_impl() ->
    typename std::invoke_result_t<Callable, decltype(std::declval<Iter>().operator*())> {
    return callable_(*iterator_);
  }

  [[nodiscard]] constexpr auto const_deref_impl() const ->
    typename std::invoke_result_t<Callable, decltype(std::declval<Iter>().operator*())> {
    return callable_(*iterator_);
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

  auto preincrement_impl() const -> const map_iterator<Iter, Callable> & {
    ++iterator_;

    return *this;
  }

  mutable Iter iterator_;
  Callable callable_;
};

}// namespace ftl

template<typename Iter, typename Callable>
struct std::iterator_traits<ftl::map_iterator<Iter, Callable>> {
  using difference_type = typename ftl::map_iterator<Iter, Callable>::difference_type;
  using value_type = typename ftl::map_iterator<Iter, Callable>::value_type;
  using pointer = typename ftl::map_iterator<Iter, Callable>::pointer;
  using reference = typename ftl::map_iterator<Iter, Callable>::reference;
  using iterator_category = typename ftl::map_iterator<Iter, Callable>::iterator_category;
};
