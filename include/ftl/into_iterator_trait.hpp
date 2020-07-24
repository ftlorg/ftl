#pragma once

namespace ftl {

template<typename T, typename U> struct into_iterator_trait {
  [[nodiscard]] constexpr static auto into_iter(T &) -> U {
    return {};
  }
};

}// namespace ftl
