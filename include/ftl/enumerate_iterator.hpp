#pragma once

#include <ftl/iterator_interface.hpp>
#include <ftl/inspect_iterator.hpp>
#include <ftl/map_iterator.hpp>
#include <ftl/iterator_traits.hpp>
#include <tuple>
#include <utility>

namespace ftl {

template<typename Iter>
class enumerate_iterator final
  : public iterator_interface<enumerate_iterator<Iter>>
  , public iterator_member_provider<enumerate_iterator<Iter>,
      typename std::iterator_traits<ftl::enumerate_iterator<Iter>>::iterator_category> {

  friend iterator_member_provider<enumerate_iterator<Iter>, std::random_access_iterator_tag>;
  friend iterator_member_provider<enumerate_iterator<Iter>, std::bidirectional_iterator_tag>;
  friend iterator_member_provider<enumerate_iterator<Iter>, std::forward_iterator_tag>;
  friend iterator_member_provider<enumerate_iterator<Iter>, std::input_iterator_tag>;
  friend iterator_member_provider<enumerate_iterator<Iter>>;
  friend const_iterator_interface<enumerate_iterator<Iter>>;

public:
  using difference_type = typename std::iterator_traits<ftl::enumerate_iterator<Iter>>::difference_type;
  using pointer = typename std::iterator_traits<ftl::enumerate_iterator<Iter>>::pointer;
  using reference = typename std::iterator_traits<ftl::enumerate_iterator<Iter>>::reference;
  using const_pointer = typename std::iterator_traits<ftl::enumerate_iterator<Iter>>::const_pointer;
  using const_reference = typename std::iterator_traits<ftl::enumerate_iterator<Iter>>::const_reference;
  using inherited_iterator_category = typename std::iterator_traits<ftl::enumerate_iterator<Iter>>::iterator_category;
  using iterator_category = typename std::iterator_traits<ftl::enumerate_iterator<Iter>>::inherited_iterator_category;
  using size_type = typename std::iterator_traits<ftl::enumerate_iterator<Iter>>::size_type;
  using value_type = typename std::iterator_traits<ftl::enumerate_iterator<Iter>>::value_type;

  enumerate_iterator(Iter iterator) : iterator_{ std::move(iterator) }, index_{ 0 } {
  }

private:
  [[nodiscard]] constexpr auto count_impl() const -> size_type {
    return iterator_.count();
  }

  [[nodiscard]] constexpr auto begin_impl() const noexcept -> enumerate_iterator<Iter> {
    return { iterator_.cbegin() };
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> enumerate_iterator<Iter> {
    return { iterator_.cbegin() };
  }

  [[nodiscard]] constexpr auto end_impl() const noexcept -> enumerate_iterator<Iter> {
    return { iterator_.cend() };
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> enumerate_iterator<Iter> {
    return { iterator_.cend() };
  }

  // TODO: Think about return type
  [[nodiscard]] constexpr auto deref_impl() -> std::tuple<size_type, decltype(std::declval<Iter>().operator*())> {
    return { index_, *iterator_ };
  }

  [[nodiscard]] constexpr auto const_deref_impl() const
    -> std::tuple<size_type, decltype(std::declval<const Iter&>().operator*())> {
    return { index_, *iterator_ };
  }

  auto preincrement_impl() -> enumerate_iterator<Iter> & {
    ++iterator_;
    ++index_;

    return *this;
  }

  mutable Iter iterator_;
  mutable size_type index_;
};

}// namespace ftl
