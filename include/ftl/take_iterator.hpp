#pragma once

#include <ftl/iterator_interface.hpp>
#include <type_traits>

namespace ftl {

template<typename Iter>
class take_iterator : const_iterator_interface<take_iterator<Iter>, typename Iter::value_type, typename Iter::size_type> {

  friend const_iterator_interface<take_iterator<Iter>, typename Iter::value_type, typename Iter::size_type>;

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

  take_iterator(Iter iterator, size_type n) : iterator_{ std::move(iterator) }, n_{ n } {
  }

  [[nodiscard]] constexpr auto begin_impl() const noexcept -> take_iterator<Iter> {
    return { iterator_.cbegin(), callable_ };
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> take_iterator<Iter> {
    return { iterator_.cbegin(), callable_ };
  }

  [[nodiscard]] constexpr auto end_impl() const noexcept -> take_iterator<Iter> {
    return { iterator_.cend(), callable_ };
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> take_iterator<Iter> {
    return { iterator_.cend(), callable_ };
  }

  [[nodiscard]] constexpr auto const_deref_impl() const ->
    typename std::invoke_result_t<Callable, decltype(std::declval<Iter>().operator*())> {
    return callable_(*iterator_);
  }

  auto const_preincrement_impl() const -> const take_iterator<Iter> & {
    if (counter_ < n_) {
      ++iterator_;
      ++counter;
    } else {
      iterator_ = iterator_.end();
    }

    return *this;
  }

  Iter iterator_;
  size_type n_ = 0;
  size_type counter_ = 0;
};

}// namespace ftl