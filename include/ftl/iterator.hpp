#pragma once
#include <optional>

#include <ftl/iterator_traits.hpp>

namespace ftl {

template<typename Item>
class iterator : public iterator_traits<iterator>
{
public:
  using iterator_category = Iterator::iterator_category;
  using value_type = Item;
  using difference_type = std::ptrdiff_t;
  using pointer = Item*;
  using reference = Item&;

  /**
   * @brief Advances the iterator and returns the next value.
  */
  [[nodiscard]] virtual std::optional<Item> next() = 0;

  /**
   * @brief Checks if all of the items matche a predicate.
  */
  template<typename Predicate>
  [[nodiscard]] bool all(Predicate &&predicate) const;

  /**
   * @brief Checks if any of the items matches a predicate.
  */
  template<typename Predicate>
  [[nodiscard]] bool any(Predicate &&predicate) const;

  /**
   * @brief Transforms an iterator into collection.
  */
  template<typename Collection>
  [[nodiscard]] Collection collect() const;

  /**
   * @brief Retruns number of the items in collection.
  */
  std::size_t count() const;

private:
  Item *m_item;
};

}// namespace ftl