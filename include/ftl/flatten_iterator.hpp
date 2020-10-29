#include <ftl/iterator_interface.hpp>
#include <ftl/inspect_iterator.hpp>
#include <ftl/map_iterator.hpp>
#include <ftl/iterator_traits.hpp>
#include <tuple>
#include <utility>
#include <ftl/is_container.hpp>

namespace ftl {

template<typename Iter>
class flatten_iterator<Iter, true> final
  : public iterator_interface<flatten_iterator<Iter>>
  , public iterator_member_provider<flatten_iterator<Iter>,
      typename std::iterator_traits<flatten_iterator<Iter>>::iterator_category> {

  friend iterator_member_provider<flatten_iterator<Iter>, std::random_access_iterator_tag>;
  friend iterator_member_provider<flatten_iterator<Iter>, std::bidirectional_iterator_tag>;
  friend iterator_member_provider<flatten_iterator<Iter>, std::forward_iterator_tag>;
  friend iterator_member_provider<flatten_iterator<Iter>, std::input_iterator_tag>;
  friend iterator_member_provider<flatten_iterator<Iter>>;
  friend iterator_interface<flatten_iterator<Iter>>;

public:
  using difference_type = typename std::iterator_traits<flatten_iterator<Iter>>::difference_type;
  using pointer = typename std::iterator_traits<flatten_iterator<Iter>>::pointer;
  using reference = typename std::iterator_traits<flatten_iterator<Iter>>::reference;
  using const_pointer = typename std::iterator_traits<flatten_iterator<Iter>>::const_pointer;
  using const_reference = typename std::iterator_traits<flatten_iterator<Iter>>::const_reference;
  using inherited_iterator_category = typename std::iterator_traits<flatten_iterator<Iter>>::iterator_category;
  using iterator_category = typename std::iterator_traits<flatten_iterator<Iter>>::inherited_iterator_category;
  using size_type = typename std::iterator_traits<flatten_iterator<Iter>>::size_type;
  using value_type = typename std::iterator_traits<flatten_iterator<Iter>>::value_type;
  using container_type = typename std::iterator_traits<Iter>::value_type;
  using container_iterator_type = typename container_type::ftl_const_iterator;

  flatten_iterator(Iter iterator) : iterator_{ std::move(iterator) } {
    if (iterator_ != iterator_.end()) {
      if constexpr (Iter::is_container_iterator){
        inner_iterator_ = static_cast<container_iterator_type>((*iterator_).iter());
      } else {
        container_ = *iterator_;
        inner_iterator_ = static_cast<container_iterator_type>(container_.iter());
      }
    }
  }

  flatten_iterator() = default;

private:
  [[nodiscard]] constexpr auto begin_impl() const noexcept -> flatten_iterator<Iter> {
    return { iterator_.cbegin() };
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> flatten_iterator<Iter> {
    return { iterator_.cbegin() };
  }

  [[nodiscard]] constexpr auto end_impl() const noexcept -> flatten_iterator<Iter> {
    return { iterator_.cend() };
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> flatten_iterator<Iter> {
    return { iterator_.cend() };
  }

  // TODO: Think about return type
  [[nodiscard]] constexpr auto deref_impl() -> value_type {
    return *iterator_;
  }

  [[nodiscard]] constexpr auto const_deref_impl() const -> value_type {
    return *inner_iterator_;
  }

  auto preincrement_impl() -> flatten_iterator<Iter> & {
    if (++inner_iterator_ == inner_iterator_.end()) {
      if (++iterator_ != iterator_.end()) {
        if constexpr (Iter::is_container_iterator){
          inner_iterator_ = static_cast<container_iterator_type>((*iterator_).iter());
        } else {
          container_ = *iterator_;
          inner_iterator_ = static_cast<container_iterator_type>(container_.iter());
        }
      }
    }
    return *this;
  }

  auto const_preincrement_impl() const -> const flatten_iterator<Iter> & {
    if (++inner_iterator_ == inner_iterator_.end()) {
      if (++iterator_ != iterator_.end()) {
        if constexpr (Iter::is_container_iterator){
          inner_iterator_ = static_cast<container_iterator_type>((*iterator_).iter());
        } else {
          container_ = *iterator_;
          inner_iterator_ = static_cast<container_iterator_type>(container_.iter());
        }
      }
    }
    return *this;
  }

  Iter iterator_;
  ftl::flatten_iterator<container_iterator_type> inner_iterator_;
  container_type container_;
};

template<typename Iter>
class flatten_iterator<Iter, false> final
  : public iterator_interface<flatten_iterator<Iter>>
  , public iterator_member_provider<flatten_iterator<Iter>,
      typename std::iterator_traits<flatten_iterator<Iter>>::iterator_category> {

  friend iterator_member_provider<flatten_iterator<Iter>, std::random_access_iterator_tag>;
  friend iterator_member_provider<flatten_iterator<Iter>, std::bidirectional_iterator_tag>;
  friend iterator_member_provider<flatten_iterator<Iter>, std::forward_iterator_tag>;
  friend iterator_member_provider<flatten_iterator<Iter>, std::input_iterator_tag>;
  friend iterator_member_provider<flatten_iterator<Iter>>;
  friend iterator_interface<flatten_iterator<Iter>>;

public:
  using difference_type = typename std::iterator_traits<flatten_iterator<Iter>>::difference_type;
  using pointer = typename std::iterator_traits<flatten_iterator<Iter>>::pointer;
  using reference = typename std::iterator_traits<flatten_iterator<Iter>>::reference;
  using const_pointer = typename std::iterator_traits<flatten_iterator<Iter>>::const_pointer;
  using const_reference = typename std::iterator_traits<flatten_iterator<Iter>>::const_reference;
  using inherited_iterator_category = typename std::iterator_traits<flatten_iterator<Iter>>::iterator_category;
  using iterator_category = typename std::iterator_traits<flatten_iterator<Iter>>::inherited_iterator_category;
  using size_type = typename std::iterator_traits<flatten_iterator<Iter>>::size_type;
  using value_type = typename std::iterator_traits<flatten_iterator<Iter>>::value_type;
  using container_type = typename std::iterator_traits<Iter>::value_type;
  using container_iterator_type = typename container_type::ftl_const_iterator;

  flatten_iterator(Iter iterator) : iterator_{ std::move(iterator) } {
    if constexpr (Iter::is_container_iterator){
      inner_iterator_ = static_cast<container_iterator_type>((*iterator_).iter());
    } else {
      container_ = *iterator_;
      inner_iterator_ = static_cast<container_iterator_type>(container_.iter());
    }
  }

  flatten_iterator() = default;

private:
  [[nodiscard]] constexpr auto begin_impl() const noexcept -> flatten_iterator<Iter> {
    return { iterator_.cbegin() };
  }

  [[nodiscard]] constexpr auto cbegin_impl() const noexcept -> flatten_iterator<Iter> {
    return { iterator_.cbegin() };
  }

  [[nodiscard]] constexpr auto end_impl() const noexcept -> flatten_iterator<Iter> {
    return { iterator_.cend() };
  }

  [[nodiscard]] constexpr auto cend_impl() const noexcept -> flatten_iterator<Iter> {
    return { iterator_.cend() };
  }

  [[nodiscard]] constexpr auto deref_impl() -> value_type {
    return *inner_iterator_;
  }

  [[nodiscard]] constexpr auto const_deref_impl() const -> value_type {
    return *inner_iterator_;
  }

  auto preincrement_impl() -> flatten_iterator<Iter> & {
    if (++inner_iterator_ == inner_iterator_.end()) {
      if (++iterator_ != iterator_.end()) {
        if constexpr (Iter::is_container_iterator){
          inner_iterator_ = static_cast<container_iterator_type>((*iterator_).iter());
        } else {
          container_ = *iterator_;
          inner_iterator_ = static_cast<container_iterator_type>(container_.iter());
        }
      }
    }
    return *this;
  }

  auto const_preincrement_impl() const -> const flatten_iterator<Iter> & {
    if (++inner_iterator_ == inner_iterator_.end()) {
      if (++iterator_ != iterator_.end()) {
        if constexpr (Iter::is_container_iterator){
          inner_iterator_ = static_cast<container_iterator_type>((*iterator_).iter());
        } else {
          container_ = *iterator_;
          inner_iterator_ = static_cast<container_iterator_type>(container_.iter());
        }
      }
    }
    return *this;
  }

  Iter iterator_;
  container_iterator_type inner_iterator_;
  container_type container_;
};

}// namespace ftl
