#pragma once

#include <ftl/iterator_interface.hpp>
#include <ftl/iterator_traits.hpp>
#include <ftl/iterator_member_provider.hpp>

namespace ftl {

template<typename Iter, typename Callable>
class filter_iterator final
  : public const_iterator_interface<filter_iterator<Iter, Callable>>
  , public iterator_member_provider<filter_iterator<Iter, Callable>,
      typename std::iterator_traits<ftl::filter_iterator<Iter, Callable>>::iterator_category> {

  friend iterator_member_provider<filter_iterator<Iter, Callable>, std::random_access_iterator_tag>;
  friend iterator_member_provider<filter_iterator<Iter, Callable>, std::bidirectional_iterator_tag>;
  friend iterator_member_provider<filter_iterator<Iter, Callable>, std::forward_iterator_tag>;
  friend iterator_member_provider<filter_iterator<Iter, Callable>, std::input_iterator_tag>;
  friend iterator_member_provider<filter_iterator<Iter, Callable>>;
  friend const_iterator_interface<filter_iterator<Iter, Callable>>;

public:
  using difference_type = typename std::iterator_traits<ftl::filter_iterator<Iter, Callable>>::difference_type;
  using value_type = typename std::iterator_traits<ftl::filter_iterator<Iter, Callable>>::value_type;
  using pointer = typename std::iterator_traits<ftl::filter_iterator<Iter, Callable>>::pointer;
  using reference = typename std::iterator_traits<ftl::filter_iterator<Iter, Callable>>::reference;
  using const_pointer = typename std::iterator_traits<ftl::filter_iterator<Iter, Callable>>::const_pointer;
  using const_reference = typename std::iterator_traits<ftl::filter_iterator<Iter, Callable>>::const_reference;
  using iterator_category = typename std::iterator_traits<ftl::filter_iterator<Iter, Callable>>::iterator_category;
  using inherited_iterator_category = typename std::iterator_traits<ftl::filter_iterator<Iter, Callable>>::iterator_category;
  using size_type = typename std::iterator_traits<ftl::filter_iterator<Iter, Callable>>::size_type;

  filter_iterator(Iter iterator, Callable callable) : iterator_{ std::move(iterator) }, callable_{ std::move(callable) } {
    while (iterator_ != iterator_.cend() && !callable_(*iterator_)) { ++iterator_; }
  }

private:
  template<typename Collection>
  [[nodiscard]] auto collect_impl() const -> Collection {
    return from_iterator_trait<filter_iterator<Iter, Callable>, Collection>::from_iter(*this);
  }

  [[nodiscard]] auto enumerate_impl() const -> enumerate_iterator<filter_iterator<Iter, Callable>> {
    return { *this };
  }

  template<typename NewCallable>
  [[nodiscard]] auto filter_impl(NewCallable &&callable) const
    -> filter_iterator<filter_iterator<Iter, Callable>, NewCallable> {
    return { *this, std::forward<NewCallable>(callable) };
  }

  template<typename NewCallable>
  [[nodiscard]] auto map_impl(NewCallable &&callable) const -> map_iterator<filter_iterator<Iter, Callable>, NewCallable> {
    return { *this, std::forward<NewCallable>(callable) };
  }

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

  auto postincrement_impl() -> filter_iterator<Iter, Callable> & {
    auto result = *this;
    while (++iterator_ != iterator_.cend() && !callable_(*iterator_)) {}
    return result;
  }


  mutable Iter iterator_;
  Callable callable_;
};

}// namespace ftl