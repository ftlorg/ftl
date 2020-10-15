
// Copyright Grzegorz Litarowicz and £ukasz Gut 2020 - 2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <ftl/iterator_interface.hpp>
#include <ftl/iterator_traits.hpp>
#include <ftl/iterator_member_provider.hpp>

namespace ftl {

template<typename Iter, typename Callable>
class filter_iterator final
  : public iterator_interface<filter_iterator<Iter, Callable>>
  , public iterator_member_provider<filter_iterator<Iter, Callable>,
      typename std::iterator_traits<filter_iterator<Iter, Callable>>::iterator_category> {

  friend iterator_member_provider<filter_iterator<Iter, Callable>, std::random_access_iterator_tag>;
  friend iterator_member_provider<filter_iterator<Iter, Callable>, std::bidirectional_iterator_tag>;
  friend iterator_member_provider<filter_iterator<Iter, Callable>, std::forward_iterator_tag>;
  friend iterator_member_provider<filter_iterator<Iter, Callable>, std::input_iterator_tag>;
  friend iterator_member_provider<filter_iterator<Iter, Callable>>;
  friend iterator_interface<filter_iterator<Iter, Callable>>;

public:
  using difference_type = typename std::iterator_traits<filter_iterator<Iter, Callable>>::difference_type;
  using value_type = typename std::iterator_traits<filter_iterator<Iter, Callable>>::value_type;
  using pointer = typename std::iterator_traits<filter_iterator<Iter, Callable>>::pointer;
  using reference = typename std::iterator_traits<filter_iterator<Iter, Callable>>::reference;
  using const_pointer = typename std::iterator_traits<filter_iterator<Iter, Callable>>::const_pointer;
  using const_reference = typename std::iterator_traits<filter_iterator<Iter, Callable>>::const_reference;
  using iterator_category = typename std::iterator_traits<filter_iterator<Iter, Callable>>::iterator_category;
  using inherited_iterator_category = typename std::iterator_traits<filter_iterator<Iter, Callable>>::iterator_category;
  using size_type = typename std::iterator_traits<filter_iterator<Iter, Callable>>::size_type;
  using callable_t = typename std::iterator_traits<filter_iterator<Iter, Callable>>::callable_t;

  filter_iterator(Iter iterator, callable_t callable) : iterator_{ std::move(iterator) }, callable_{ std::move(callable) } {
    while (iterator_ != iterator_.cend() && !callable_(*iterator_)) { ++iterator_; }
  }

private:

  [[nodiscard]] constexpr auto begin_impl() const noexcept -> filter_iterator<Iter, Callable> {
    return { iterator_.cbegin(), callable_ };
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> filter_iterator<Iter, Callable> {
    return { iterator_.cbegin(), callable_ };
  }

  [[nodiscard]] constexpr auto end_impl() const noexcept -> filter_iterator<Iter, Callable> {
    return { iterator_.cend(), callable_ };
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> filter_iterator<Iter, Callable> {
    return { iterator_.cend(), callable_ };
  }

  [[nodiscard]] constexpr auto const_deref_impl() const -> decltype(std::declval<const Iter&>().operator*()) {
    return *iterator_;
  }

  auto preincrement_impl() -> filter_iterator<Iter, Callable> & {
    while (++iterator_ != iterator_.end() && !callable_(*iterator_)) {}
    return *this;
  }

  auto const_preincrement_impl() const -> const filter_iterator<Iter, Callable> & {
    while (++iterator_ != iterator_.cend() && !callable_(*iterator_)) {}
    return *this;
  }

  mutable Iter iterator_;
  callable_t callable_;
};

}// namespace ftl