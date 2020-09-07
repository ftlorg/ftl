#pragma once

#include <ftl/iterator_interface.hpp>

namespace ftl {

template<typename Key, typename T, typename Item = std::pair<Key, T>>
class map_container_const_iterator final
  : public const_iterator_interface<map_container_const_iterator<Key, T>, Item, std::size_t> {
public:
private:
};

}// namespace ftl