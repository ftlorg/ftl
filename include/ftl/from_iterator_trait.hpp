#pragma once

namespace ftl {

template<typename T, typename U> struct from_iterator_trait {
  [[nodiscard]] constexpr static auto from_iter(T &) -> U {
    return {};
  }
};

}// namespace ftl
