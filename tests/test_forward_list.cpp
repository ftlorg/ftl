#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

#define TEST_TAG "[forward_list]"

TEST_CASE(TEST_TAG "default ctor", TEST_TAG) {
  ftl::forward_list<int> forward_list;

  REQUIRE(forward_list.empty() == true);
}

TEST_CASE(TEST_TAG "count value ctor", TEST_TAG) {
  std::size_t size = 5;
  ftl::forward_list<int> forward_list(size, 10);

  for (const auto x : forward_list) { REQUIRE(x == 10); }
}

TEST_CASE(TEST_TAG "count alloc ctor", TEST_TAG) {
  std::size_t size = 5;
  ftl::forward_list<int> forward_list(size);

  for (const auto x : forward_list) { REQUIRE(x == 0); }
}

TEST_CASE(TEST_TAG "input iterator ctor", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };
  ftl::forward_list<int> forward_list2 = { forward_list1.begin(), forward_list1.end() };

  auto iter1 = forward_list1.begin();
  auto iter2 = forward_list2.begin();
  for (; iter1 != forward_list1.end() && iter2 != forward_list2.end(); iter1++, iter2++) { REQUIRE(*iter1 == *iter2); }
}

TEST_CASE(TEST_TAG "copy ctor", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };
  ftl::forward_list<int> forward_list2 = forward_list1;

  auto iter1 = forward_list1.begin();
  auto iter2 = forward_list2.begin();
  for (; iter1 != forward_list1.end() && iter2 != forward_list2.end(); iter1++, iter2++) { REQUIRE(*iter1 == *iter2); }
}

TEST_CASE(TEST_TAG "move ctor", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };
  ftl::forward_list<int> forward_list2 = std::move(forward_list1);

  int x = 0;
  for (auto iter2 = forward_list2.begin(); iter2 != forward_list2.end(); iter2++) { REQUIRE(*iter2 == ++x); }
}

TEST_CASE(TEST_TAG "initializer_forward_list ctor", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };

  int x = 0;
  for (auto iter1 = forward_list1.begin(); iter1 != forward_list1.end(); iter1++) { REQUIRE(*iter1 == ++x); }
}

TEST_CASE(TEST_TAG "operator=", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };
  ftl::forward_list<int> forward_list2 = { 5, 4, 3, 2, 1 };
  forward_list1 = forward_list2;

  int x = 5;
  for (auto iter1 = forward_list1.begin(); iter1 != forward_list1.end(); iter1++) { REQUIRE(*iter1 == x--); }
}

TEST_CASE(TEST_TAG "move operator=", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };
  forward_list1 = ftl::forward_list<int>{ 5, 4, 3, 2, 1 };

  int x = 5;
  for (auto iter1 = forward_list1.begin(); iter1 != forward_list1.end(); iter1++) { REQUIRE(*iter1 == x--); }
}

TEST_CASE(TEST_TAG "assign", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };
  forward_list1.assign(5u, 10);

  int x = 10;
  for (auto iter1 = forward_list1.begin(); iter1 != forward_list1.end(); iter1++) { REQUIRE(*iter1 == x); }
}

TEST_CASE(TEST_TAG "input iterator assign", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };
  ftl::forward_list<int> forward_list2 = { 10, 10, 10, 10, 10 };

  forward_list1.assign(forward_list2.begin(), forward_list2.end());

  int x = 10;
  for (auto iter1 = forward_list1.begin(); iter1 != forward_list1.end(); iter1++) { REQUIRE(*iter1 == x); }
}

TEST_CASE(TEST_TAG "initializer_forward_list assign", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };

  forward_list1.assign({ 10, 10, 10, 10, 10 });

  int x = 10;
  for (auto iter1 = forward_list1.begin(); iter1 != forward_list1.end(); iter1++) { REQUIRE(*iter1 == x); }
}

TEST_CASE(TEST_TAG "front", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(forward_list1.front() == 1);
}

TEST_CASE(TEST_TAG "front const", TEST_TAG) {
  const ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(forward_list1.front() == 1);
}

TEST_CASE(TEST_TAG "before_begin", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(*(++forward_list1.before_begin()) == 1);
}

TEST_CASE(TEST_TAG "before_begin const", TEST_TAG) {
  const ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(*(++forward_list1.before_begin()) == 1);
}

TEST_CASE(TEST_TAG "cbefore_begin", TEST_TAG) {
  const ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(*(++forward_list1.cbefore_begin()) == 1);
}

TEST_CASE(TEST_TAG "begin", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(*forward_list1.begin() == 1);
}

TEST_CASE(TEST_TAG "begin const", TEST_TAG) {
  const ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(*forward_list1.begin() == 1);
}

TEST_CASE(TEST_TAG "cbegin const", TEST_TAG) {
  const ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(*forward_list1.cbegin() == 1);
}

TEST_CASE(TEST_TAG "empty", TEST_TAG) {
  ftl::forward_list<int> forward_list1;
  ftl::forward_list<int> forward_list2 = { 1, 2, 3, 4, 5 };

  REQUIRE(forward_list1.empty() == true);
  REQUIRE(forward_list2.empty() == false);
}

TEST_CASE(TEST_TAG "empty const", TEST_TAG) {
  const ftl::forward_list<int> forward_list1;
  const ftl::forward_list<int> forward_list2 = { 1, 2, 3, 4, 5 };

  REQUIRE(forward_list1.empty() == true);
  REQUIRE(forward_list2.empty() == false);
}

TEST_CASE(TEST_TAG "max_size", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(forward_list1.max_size() > 0);
}

TEST_CASE(TEST_TAG "max_size const", TEST_TAG) {
  const ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(forward_list1.max_size() > 0);
}

TEST_CASE(TEST_TAG "clear", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };
  forward_list1.clear();

  REQUIRE(forward_list1.empty() == true);
}

TEST_CASE(TEST_TAG "insert_after", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };
  
  forward_list1.insert_after(forward_list1.before_begin(), 0);

  REQUIRE(forward_list1.front() == 0);
}

TEST_CASE(TEST_TAG "emplace_after", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };

  forward_list1.emplace_after(forward_list1.before_begin(), 0);

  REQUIRE(forward_list1.front() == 0);
}

TEST_CASE(TEST_TAG "erase_after", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4, 5 };

  forward_list1.erase_after(forward_list1.before_begin());

  REQUIRE(forward_list1.front() == 2);
}

TEST_CASE(TEST_TAG "push_front", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = {};

  forward_list1.push_front(1);
  REQUIRE(forward_list1 == ftl::forward_list<int>{ 1 });

  forward_list1.push_front(2);
  REQUIRE(forward_list1 == ftl::forward_list<int>{ 2, 1 });

  forward_list1.push_front(3);
  REQUIRE(forward_list1 == ftl::forward_list<int>{ 3, 2, 1 });
}

TEST_CASE(TEST_TAG "emplace_front", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = {};

  forward_list1.emplace_front(1);
  REQUIRE(forward_list1 == ftl::forward_list<int>{ 1 });

  forward_list1.emplace_front(2);
  REQUIRE(forward_list1 == ftl::forward_list<int>{ 2, 1 });

  forward_list1.emplace_front(3);
  REQUIRE(forward_list1 == ftl::forward_list<int>{ 3, 2, 1 });
}

TEST_CASE(TEST_TAG "pop_front", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3, 4 };

  forward_list1.pop_front();
  REQUIRE(forward_list1 == ftl::forward_list<int>{ 2, 3, 4 });

  forward_list1.pop_front();
  REQUIRE(forward_list1 == ftl::forward_list<int>{ 3, 4 });

  forward_list1.pop_front();
  REQUIRE(forward_list1 == ftl::forward_list<int>{ 4 });
}

TEST_CASE(TEST_TAG "resize", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = {};
  forward_list1.resize(5);

  REQUIRE(forward_list1 == ftl::forward_list<int>{ 0, 0, 0, 0, 0 });
}

TEST_CASE(TEST_TAG "swap", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3 };
  ftl::forward_list<int> forward_list2 = { 3, 2, 1 };
  forward_list1.swap(forward_list2);

  REQUIRE(forward_list1 == ftl::forward_list<int>{ 3, 2, 1 });
  REQUIRE(forward_list2 == ftl::forward_list<int>{ 1, 2, 3 });
}

TEST_CASE(TEST_TAG "merge", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3 };
  ftl::forward_list<int> forward_list2 = { 4, 5, 6 };
  forward_list1.merge(forward_list2);

  REQUIRE(forward_list1 == ftl::forward_list<int>{ 1, 2, 3, 4, 5, 6 });
  REQUIRE(forward_list2.empty() == true);
}

TEST_CASE(TEST_TAG "remove", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3 };
  forward_list1.remove(2);

  REQUIRE(forward_list1 == ftl::forward_list<int>{ 1, 3 });
}

TEST_CASE(TEST_TAG "remove_if", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3 };
  forward_list1.remove_if([](const auto &x) { return x % 2 == 0; });

  REQUIRE(forward_list1 == ftl::forward_list<int>{ 1, 3 });
}

TEST_CASE(TEST_TAG "reverse", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 3 };
  forward_list1.reverse();

  REQUIRE(forward_list1 == ftl::forward_list<int>{ 3, 2, 1 });
}

TEST_CASE(TEST_TAG "unique", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 2, 3, 3, 4 };
  forward_list1.unique();

  REQUIRE(forward_list1 == ftl::forward_list<int>{ 1, 2, 3, 4 });
}

TEST_CASE(TEST_TAG "unique predicate", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 1, 2, 2, 3, 3, 4 };
  forward_list1.unique([](const auto &a, const auto &b) { return a < b; });

  REQUIRE(forward_list1 == ftl::forward_list<int>{ 1 });
}

TEST_CASE(TEST_TAG "sort", TEST_TAG) {
  ftl::forward_list<int> forward_list1 = { 5, 1, 3, 2, 4 };
  forward_list1.sort();

  REQUIRE(forward_list1 == ftl::forward_list<int>{ 1, 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "to_forward_list", TEST_TAG) {
  std::forward_list<int> forward_list = { 1, 2, 3, 4, 5 };
  const auto ftl_forward_list = ftl::to_forward_list(forward_list);

  REQUIRE(ftl_forward_list == ftl::forward_list<int>{ 1, 2, 3, 4, 5 });
}
