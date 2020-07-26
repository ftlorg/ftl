#pragma once

namespace ftl {

template<typename T, typename U>
struct from_iterator_trait {
  [[nodiscard]] constexpr static auto from_iter(const T &iter) -> U {
    U collection{};
    for (auto &&elem : iter) { collection.push_back(elem); }
    return collection;
  }
};

}// namespace ftl
