#pragma once

#include <functional>
#include <ftl/iterator_interface.hpp>

namespace ftl {

template<typename Item, typename Callable>
class map_iterator : public iterator_interface<Item>
{
public:
  [[nodiscard]] map_iterator(Callable callable) : callable_{ std::move(callable) } {}

  /**
   * @brief Advances the iterator and returns the next value.
  */
  [[nodiscard]] virtual std::optional<value_type> next()
  {
    return iterator_interface<Item>::next();
  };

private:
  Callable callable_;
};

}// namespace ftl
