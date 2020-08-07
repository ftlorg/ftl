#pragma once
#include <iterator>

namespace ftl {

template <typename Item, typename Allocator = std::allocator<Item>>
class vector_iterator final : public iterator_interface<vector_iterator<Item, Allocator>, Item, std::size_t> {

    friend iterator_interface<vector_iterator<Item, Allocator>, Item, std::size_t>;

public:
    using difference_type = std::ptrdiff_t;
    using value_type = typename std::remove_cv_t<Item>;
    using pointer = value_type *;
    using reference = value_type &;
    using const_pointer = const value_type *;
    using const_reference = const value_type &;
    using iterator_category = std::random_access_iterator_tag;
    using size_type = std::size_t;

    constexpr vector_iterator() {}

private:
    typename std::vector<value_type, Allocator>::iterator iterator_;
};

}

