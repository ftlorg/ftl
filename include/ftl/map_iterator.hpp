#pragma once

#include <type_traits>
#include <functional>
#include <ftl/iterator_interface.hpp>
#include <ftl/iterator_member_provider.hpp>
#include <ftl/iterator_traits.hpp>

namespace ftl {

template<typename Iter, typename Callable>
class map_iterator final
  : public iterator_interface<map_iterator<Iter, Callable>>
  , public iterator_member_provider<map_iterator<Iter, Callable>, typename Iter::iterator_category> {

  friend iterator_member_provider<map_iterator<Iter, Callable>, std::random_access_iterator_tag>;
  friend iterator_member_provider<map_iterator<Iter, Callable>, std::bidirectional_iterator_tag>;
  friend iterator_member_provider<map_iterator<Iter, Callable>, std::forward_iterator_tag>;
  friend iterator_member_provider<map_iterator<Iter, Callable>, std::input_iterator_tag>;
  friend iterator_member_provider<map_iterator<Iter, Callable>>;
  friend iterator_interface<map_iterator<Iter, Callable>>;

public:
  using difference_type = typename std::iterator_traits<map_iterator<Iter, Callable>>::difference_type;
  using value_type = typename std::iterator_traits<map_iterator<Iter, Callable>>::value_type;
  using pointer = typename std::iterator_traits<map_iterator<Iter, Callable>>::pointer;
  using reference = typename std::iterator_traits<map_iterator<Iter, Callable>>::reference;
  using const_pointer = typename std::iterator_traits<map_iterator<Iter, Callable>>::const_pointer;
  using const_reference = typename std::iterator_traits<map_iterator<Iter, Callable>>::const_reference;
  using inherited_iterator_category = typename std::iterator_traits<map_iterator<Iter, Callable>>::iterator_category;
  using iterator_category = typename std::iterator_traits<map_iterator<Iter, Callable>>::inherited_iterator_category;
  using size_type = typename std::iterator_traits<map_iterator<Iter, Callable>>::size_type;
  using callable_t = std::function<std::invoke_result_t<Callable, typename Iter::value_type>(typename Iter::value_type)>;

  map_iterator(Iter iterator, callable_t callable) : iterator_{ std::move(iterator) }, callable_{ std::move(callable) } {
  }

private:
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

  [[nodiscard]] constexpr auto const_deref_impl() const ->
    typename std::invoke_result_t<Callable, decltype(std::declval<Iter>().operator*())> {
    return callable_(*iterator_);
  }

  [[nodiscard]] constexpr auto preincrement_impl() -> map_iterator<Iter, Callable> & {
    iterator_++;
    return *this;
  }

  [[nodiscard]] constexpr auto const_preincrement_impl() const -> const map_iterator<Iter, Callable> & {
    iterator_++;
    return *this;
  }

  mutable Iter iterator_;
  callable_t callable_;
};

}// namespace ftl
