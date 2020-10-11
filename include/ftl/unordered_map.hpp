#pragma once

#include <unordered_map>

#include <ftl/unordered_map_container_iterator.hpp>
#include <ftl/unordered_map_container_const_iterator.hpp>
#include <ftl/into_iterator_trait.hpp>

namespace ftl {

template<typename Key,
  typename T,
  typename Hash = std::hash<Key>,
  typename KeyEqual = std::equal_to<Key>,
  typename Allocator = std::allocator<std::pair<const Key, T>>>
class unordered_map : public std::unordered_map<Key, T, Hash, KeyEqual, Allocator> {
public:
  using value_type = typename std::unordered_map<Key, T, Hash, KeyEqual, Allocator>::value_type;
  using allocator_type = typename std::unordered_map<Key, T, Hash, KeyEqual, Allocator>::allocator_type;
  using size_type = typename std::unordered_map<Key, T, Hash, KeyEqual, Allocator>::size_type;
  using difference_type = typename std::unordered_map<Key, T, Hash, KeyEqual, Allocator>::difference_type;
  using pointer = typename std::unordered_map<Key, T, Hash, KeyEqual, Allocator>::pointer;
  using reference = typename std::unordered_map<Key, T, Hash, KeyEqual, Allocator>::reference;
  using const_pointer = typename std::unordered_map<Key, T, Hash, KeyEqual, Allocator>::const_pointer;
  using const_reference = typename std::unordered_map<Key, T, Hash, KeyEqual, Allocator>::const_reference;
  using ftl_iterator = unordered_map_container_iterator<Key, T>;
  using ftl_const_iterator = unordered_map_container_const_iterator<Key, T>;
  using iterator = typename std::unordered_map<Key, T, Hash, KeyEqual, Allocator>::iterator;
  using const_iterator = typename std::unordered_map<Key, T, Hash, KeyEqual, Allocator>::const_iterator;

  using std::unordered_map<Key, T, Hash, KeyEqual, Allocator>::unordered_map;

  [[nodiscard]] auto iter() noexcept -> ftl_iterator {
    return into_iterator_trait<unordered_map<Key, T, Hash, KeyEqual, Allocator>, ftl_iterator>::into_iter(*this);
  }

  [[nodiscard]] auto iter() const noexcept -> ftl_const_iterator {
    return into_iterator_trait<unordered_map<Key, T, Hash, KeyEqual, Allocator>, ftl_const_iterator>::into_iter(*this);
  }
};

template<typename Key,
  typename T,
  typename Hash = std::hash<Key>,
  typename KeyEqual = std::equal_to<Key>,
  typename Allocator = std::allocator<std::pair<const Key, T>>>
[[nodiscard]] constexpr auto to_unordered_map(const std::unordered_map<Key, T, Hash, KeyEqual, Allocator> &unordered_map)
  -> ftl::unordered_map<Key, T, Hash, KeyEqual, Allocator> {
  return { std::begin(unordered_map), std::end(unordered_map) };
}

}// namespace ftl

template<typename Iter, typename Key, typename T>
struct ftl::from_iterator_trait<ftl::enumerate_iterator<Iter>, ftl::unordered_map<Key, T>> {
  [[nodiscard]] constexpr static auto from_iter(const ftl::enumerate_iterator<Iter> &iter) -> ftl::unordered_map<Key, T> {
    ftl::unordered_map<Key, T> result{};

    for (auto &&item : iter) { result.emplace(std::get<0>(item), std::get<1>(item)); }

    return result;
  }
};

template<typename Key, typename T, typename Hash, typename KeyEqual, typename Allocator>
struct ftl::into_iterator_trait<ftl::unordered_map<Key, T, Hash, KeyEqual, Allocator>,
  typename ftl::unordered_map<Key, T, Hash, KeyEqual, Allocator>::ftl_iterator> {
  using iterator = typename ftl::unordered_map<Key, T, Hash, KeyEqual, Allocator>::ftl_iterator;

  [[nodiscard]] static auto into_iter(ftl::unordered_map<Key, T, Hash, KeyEqual, Allocator> &unordered_map) -> iterator {
    return { unordered_map.begin(), unordered_map.end() };
  }
};

template<typename Key, typename T, typename Hash, typename KeyEqual, typename Allocator>
struct ftl::into_iterator_trait<ftl::unordered_map<Key, T, Hash, KeyEqual, Allocator>,
  typename ftl::unordered_map<Key, T, Hash, KeyEqual, Allocator>::ftl_const_iterator> {
  using const_iterator = typename ftl::unordered_map<Key, T, Hash, KeyEqual, Allocator>::ftl_const_iterator;

  [[nodiscard]] static auto into_iter(const ftl::unordered_map<Key, T, Hash, KeyEqual, Allocator> &unordered_map)
    -> const_iterator {
    return { unordered_map.begin(), unordered_map.end() };
  }
};

template<typename Iter, typename Key, typename T, typename Hash, typename KeyEqual, typename Allocator>
struct ftl::from_iterator_trait<Iter, std::unordered_map<Key, T, Hash, KeyEqual, Allocator>> {
  [[nodiscard]] constexpr static auto from_iter(const Iter &iter) -> std::unordered_map<Key, T, Hash, KeyEqual, Allocator> {
    return std::unordered_map<Key, T, Hash, KeyEqual, Allocator>{ iter.begin(), iter.end() };
  }

  constexpr static auto from_iter_into_collection(const Iter &iter,
    std::unordered_map<Key, T, Hash, KeyEqual, Allocator> &collection) -> void {
    collection.insert(iter.begin(), iter.end());
  }
};

template<typename Iter, typename Key, typename T, typename Hash, typename KeyEqual, typename Allocator>
struct ftl::from_iterator_trait<Iter, ftl::unordered_map<Key, T, Hash, KeyEqual, Allocator>> {
  [[nodiscard]] constexpr static auto from_iter(const Iter &iter) -> ftl::unordered_map<Key, T, Hash, KeyEqual, Allocator> {
    return ftl::unordered_map<Key, T, Hash, KeyEqual, Allocator>{ iter.begin(), iter.end() };
  }

  constexpr static auto from_iter_into_collection(const Iter &iter,
    ftl::unordered_map<Key, T, Hash, KeyEqual, Allocator> &collection) -> void {
    collection.insert(iter.begin(), iter.end());
  }
};
