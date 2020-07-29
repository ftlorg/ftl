#pragma once

namespace ftl {

template<typename T, typename U>
struct from_iterator_trait {
  [[nodiscard]] constexpr static auto from_iter(const T &iter) -> U {
    return { iter.begin(), iter.end() };
  }
};

}// namespace ftl
