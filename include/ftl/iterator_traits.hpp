#pragma once

namespace ftl {
template<typename Iterator>
struct iterator_traits
{
  using iterator_category = Iterator::iterator_category;
  using value_type = Iterator::value_type;
  using difference_type = Iterator::difference_type;
  using pointer = Iterator::pointer;
  using reference = Iterator::reference;
};
}// namespace ftl