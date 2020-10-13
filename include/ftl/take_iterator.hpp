#pragma once

#include <ftl/iterator_interface.hpp>
#include <type_traits>

namespace ftl {

template<typename Iter>
class take_iterator
  : public iterator_interface<take_iterator<Iter>>
  , public iterator_member_provider<take_iterator<Iter>, typename Iter::iterator_category> {

  friend iterator_interface<take_iterator<Iter>>;
  friend iterator_member_provider<take_iterator<Iter>, std::random_access_iterator_tag>;
  friend iterator_member_provider<take_iterator<Iter>, std::bidirectional_iterator_tag>;
  friend iterator_member_provider<take_iterator<Iter>, std::forward_iterator_tag>;
  friend iterator_member_provider<take_iterator<Iter>, std::input_iterator_tag>;
  friend iterator_member_provider<take_iterator<Iter>>;

public:
  using difference_type = typename Iter::difference_type;
  using value_type = typename Iter::value_type;
  using pointer = typename Iter::pointer;
  using reference = typename Iter::reference;
  using const_pointer = typename Iter::const_pointer;
  using const_reference = typename Iter::const_reference;
  using inherited_iterator_category = typename Iter::iterator_category;
  using iterator_category = std::forward_iterator_tag;
  using size_type = typename Iter::size_type;

  take_iterator(Iter iterator, size_type n) : iterator_{ std::move(iterator) }, n_{ std::min(n, iterator_.count()) } {
  }

  [[nodiscard]] constexpr auto begin_impl() const noexcept -> take_iterator<Iter> {
    return { iterator_.cbegin(), n_ };
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> take_iterator<Iter> {
    return { iterator_.cbegin(), n_ };
  }

  [[nodiscard]] constexpr auto end_impl() const noexcept -> take_iterator<Iter> {
    // TODO: This is suboptimal
    return { std::next(iterator_.cbegin(), static_cast<difference_type>(n_)), n_ };
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> take_iterator<Iter> {
    // TODO: This is suboptimal
    return { std::next(iterator_.cbegin(), static_cast<difference_type>(n_)), n_ };
  }

  [[nodiscard]] constexpr auto const_deref_impl() const -> decltype(std::declval<const Iter &>().operator*()) {
    return *iterator_;
  }

  auto preincrement_impl() -> const take_iterator<Iter> & {
    ++iterator_;
    return *this;
  }

  auto const_preincrement_impl() const -> const take_iterator<Iter> & {
    ++iterator_;
    return *this;
  }

private:
  mutable Iter iterator_;
  size_type n_ = 0;
};

}// namespace ftl