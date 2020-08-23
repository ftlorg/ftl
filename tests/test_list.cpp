#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

#define TEST_TAG "[list]"

TEST_CASE(TEST_TAG "default ctor", TEST_TAG) {
  ftl::list<int> list;

  REQUIRE(list.size() == 0);
}

TEST_CASE(TEST_TAG "count value ctor", TEST_TAG) {
  std::size_t size = 5;
  ftl::list<int> list(size, 10);

  REQUIRE(list.size() == size);

  for (const auto x : list) { REQUIRE(x == 10); }
}

TEST_CASE(TEST_TAG "count alloc ctor", TEST_TAG) {
  std::size_t size = 5;
  ftl::list<int> list(size);

  REQUIRE(list.size() == size);

  for (const auto x : list) { REQUIRE(x == 0); }
}

TEST_CASE(TEST_TAG "input iterator ctor", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3, 4, 5 };
  ftl::list<int> list2 = { list1.begin(), list1.end() };

  REQUIRE(list1.size() == list2.size());

  auto iter1 = list1.begin();
  auto iter2 = list2.begin();
  for (; iter1 != list1.end() && iter2 != list2.end(); iter1++, iter2++) { REQUIRE(*iter1 == *iter2); }
}

TEST_CASE(TEST_TAG "copy ctor", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3, 4, 5 };
  ftl::list<int> list2 = list1;

  REQUIRE(list1.size() == list2.size());

  auto iter1 = list1.begin();
  auto iter2 = list2.begin();
  for (; iter1 != list1.end() && iter2 != list2.end(); iter1++, iter2++) { REQUIRE(*iter1 == *iter2); }
}

TEST_CASE(TEST_TAG "move ctor", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3, 4, 5 };
  ftl::list<int> list2 = std::move(list1);


  int x = 0;
  for (auto iter2 = list2.begin(); iter2 != list2.end(); iter2++) { REQUIRE(*iter2 == ++x); }
}

TEST_CASE(TEST_TAG "initializer_list ctor", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3, 4, 5 };

  int x = 0;
  for (auto iter1 = list1.begin(); iter1 != list1.end(); iter1++) { REQUIRE(*iter1 == ++x); }
}

TEST_CASE(TEST_TAG "operator=", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3, 4, 5 };
  ftl::list<int> list2 = { 5, 4, 3, 2, 1 };
  list1 = list2;

  int x = 5;
  for (auto iter1 = list1.begin(); iter1 != list1.end(); iter1++) { REQUIRE(*iter1 == x--); }
}

TEST_CASE(TEST_TAG "move operator=", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3, 4, 5 };
  list1 = ftl::list<int>{ 5, 4, 3, 2, 1 };

  int x = 5;
  for (auto iter1 = list1.begin(); iter1 != list1.end(); iter1++) { REQUIRE(*iter1 == x--); }
}

TEST_CASE(TEST_TAG "assign", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3, 4, 5 };
  list1.assign(5u, 10);

  int x = 10;
  for (auto iter1 = list1.begin(); iter1 != list1.end(); iter1++) { REQUIRE(*iter1 == x); }
}

TEST_CASE(TEST_TAG "input iterator assign", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3, 4, 5 };
  ftl::list<int> list2 = { 10, 10, 10, 10, 10 };

  list1.assign(list2.begin(), list2.end());

  int x = 10;
  for (auto iter1 = list1.begin(); iter1 != list1.end(); iter1++) { REQUIRE(*iter1 == x); }
}

TEST_CASE(TEST_TAG "initializer_list assign", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3, 4, 5 };

  list1.assign({ 10, 10, 10, 10, 10 });

  int x = 10;
  for (auto iter1 = list1.begin(); iter1 != list1.end(); iter1++) { REQUIRE(*iter1 == x); }
}

TEST_CASE(TEST_TAG "front", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(list1.front() == 1);
}

TEST_CASE(TEST_TAG "front const", TEST_TAG) {
  const ftl::list<int> list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(list1.front() == 1);
}

TEST_CASE(TEST_TAG "back", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(list1.back() == 5);
}

TEST_CASE(TEST_TAG "back const", TEST_TAG) {
  const ftl::list<int> list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(list1.back() == 5);
}

TEST_CASE(TEST_TAG "begin", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(*list1.begin() == 1);
}

TEST_CASE(TEST_TAG "begin const", TEST_TAG) {
  const ftl::list<int> list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(*list1.begin() == 1);
}

TEST_CASE(TEST_TAG "cbegin const", TEST_TAG) {
  const ftl::list<int> list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(*list1.cbegin() == 1);
}

TEST_CASE(TEST_TAG "rbegin", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(*list1.rbegin() == 5);
}

TEST_CASE(TEST_TAG "rbegin const", TEST_TAG) {
  const ftl::list<int> list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(*list1.rbegin() == 5);
}

TEST_CASE(TEST_TAG "crbegin const", TEST_TAG) {
  const ftl::list<int> list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(*list1.crbegin() == 5);
}

TEST_CASE(TEST_TAG "empty", TEST_TAG) {
  ftl::list<int> list1;
  ftl::list<int> list2 = { 1, 2, 3, 4, 5 };

  REQUIRE(list1.empty() == true);
  REQUIRE(list2.empty() == false);
}

TEST_CASE(TEST_TAG "empty const", TEST_TAG) {
  const ftl::list<int> list1;
  const ftl::list<int> list2 = { 1, 2, 3, 4, 5 };

  REQUIRE(list1.empty() == true);
  REQUIRE(list2.empty() == false);
}

TEST_CASE(TEST_TAG "size", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(list1.size() == 5);
}

TEST_CASE(TEST_TAG "size const", TEST_TAG) {
  const ftl::list<int> list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(list1.size() == 5);
}

TEST_CASE(TEST_TAG "max_size", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(list1.max_size() > 0);
}

TEST_CASE(TEST_TAG "max_size const", TEST_TAG) {
  const ftl::list<int> list1 = { 1, 2, 3, 4, 5 };

  REQUIRE(list1.max_size() > 0);
}

TEST_CASE(TEST_TAG "clear", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3, 4, 5 };
  list1.clear();

  REQUIRE(list1.size() == 0);
}

TEST_CASE(TEST_TAG "insert", TEST_TAG) {
  ftl::list<int> list1;
  list1.insert(list1.begin(), 1);

  REQUIRE(list1.front() == 1);
}

TEST_CASE(TEST_TAG "emplace", TEST_TAG) {
  ftl::list<int> list1;
  list1.emplace(list1.begin(), 1);

  REQUIRE(list1.front() == 1);
}

TEST_CASE(TEST_TAG "erase", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3, 4, 5 };
  list1.erase(list1.begin());

  REQUIRE(list1 == ftl::list<int>{ 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "push_back", TEST_TAG) {
  ftl::list<int> list1 = {};

  list1.push_back(1);
  REQUIRE(list1 == ftl::list<int>{ 1 });

  list1.push_back(2);
  REQUIRE(list1 == ftl::list<int>{ 1, 2 });

  list1.push_back(3);
  REQUIRE(list1 == ftl::list<int>{ 1, 2, 3 });
}

TEST_CASE(TEST_TAG "emplace_back", TEST_TAG) {
  ftl::list<int> list1 = {};

  list1.emplace_back(1);
  REQUIRE(list1 == ftl::list<int>{ 1 });

  list1.emplace_back(2);
  REQUIRE(list1 == ftl::list<int>{ 1, 2 });

  list1.emplace_back(3);
  REQUIRE(list1 == ftl::list<int>{ 1, 2, 3 });
}

TEST_CASE(TEST_TAG "pop_back", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3, 4 };

  list1.pop_back();
  REQUIRE(list1 == ftl::list<int>{ 1, 2, 3 });

  list1.pop_back();
  REQUIRE(list1 == ftl::list<int>{ 1, 2 });

  list1.pop_back();
  REQUIRE(list1 == ftl::list<int>{ 1 });
}

TEST_CASE(TEST_TAG "push_front", TEST_TAG) {
  ftl::list<int> list1 = {};

  list1.push_front(1);
  REQUIRE(list1 == ftl::list<int>{ 1 });

  list1.push_front(2);
  REQUIRE(list1 == ftl::list<int>{ 2, 1 });

  list1.push_front(3);
  REQUIRE(list1 == ftl::list<int>{ 3, 2, 1 });
}

TEST_CASE(TEST_TAG "emplace_front", TEST_TAG) {
  ftl::list<int> list1 = {};

  list1.emplace_front(1);
  REQUIRE(list1 == ftl::list<int>{ 1 });

  list1.emplace_front(2);
  REQUIRE(list1 == ftl::list<int>{ 2, 1 });

  list1.emplace_front(3);
  REQUIRE(list1 == ftl::list<int>{ 3, 2, 1 });
}

TEST_CASE(TEST_TAG "pop_front", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3, 4 };

  list1.pop_front();
  REQUIRE(list1 == ftl::list<int>{ 2, 3, 4 });

  list1.pop_front();
  REQUIRE(list1 == ftl::list<int>{ 3, 4 });

  list1.pop_front();
  REQUIRE(list1 == ftl::list<int>{ 4 });
}

TEST_CASE(TEST_TAG "resize", TEST_TAG) {
  ftl::list<int> list1 = {};
  list1.resize(5);

  REQUIRE(list1.size() == 5);
  REQUIRE(list1 == ftl::list<int>{ 0, 0, 0, 0, 0 });
}

TEST_CASE(TEST_TAG "swap", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3 };
  ftl::list<int> list2 = { 3, 2, 1 };
  list1.swap(list2);

  REQUIRE(list1 == ftl::list<int>{ 3, 2, 1 });
  REQUIRE(list2 == ftl::list<int>{ 1, 2, 3 });
}

TEST_CASE(TEST_TAG "merge", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3 };
  ftl::list<int> list2 = { 4, 5, 6 };
  list1.merge(list2);

  REQUIRE(list1 == ftl::list<int>{ 1, 2, 3, 4, 5, 6 });
  REQUIRE(list2.empty() == true);
}

TEST_CASE(TEST_TAG "splice whole", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3 };
  ftl::list<int> list2 = { 4, 5, 6 };
  list1.splice(list1.begin(), list2);

  REQUIRE(list1 == ftl::list<int>{ 4, 5, 6, 1, 2, 3 });
  REQUIRE(list2.empty() == true);
}

TEST_CASE(TEST_TAG "splice partial", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3 };
  ftl::list<int> list2 = { 4, 5, 6 };
  auto it = list2.begin();
  std::advance(it, 1);
  list1.splice(list1.begin(), list2, it, list2.end());

  REQUIRE(list1 == ftl::list<int>{ 5, 6, 1, 2, 3 });
  REQUIRE(list2 == ftl::list<int>{ 4 });
}

TEST_CASE(TEST_TAG "remove", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3 };
  list1.remove(2);

  REQUIRE(list1 == ftl::list<int>{ 1, 3 });
}

TEST_CASE(TEST_TAG "remove_if", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3 };
  list1.remove_if([](const auto &x) { return x % 2 == 0; });

  REQUIRE(list1 == ftl::list<int>{ 1, 3 });
}

TEST_CASE(TEST_TAG "reverse", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 3 };
  list1.reverse();

  REQUIRE(list1 == ftl::list<int>{ 3, 2, 1 });
}

TEST_CASE(TEST_TAG "unique", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 2, 3, 3, 4 };
  list1.unique();

  REQUIRE(list1 == ftl::list<int>{ 1, 2, 3, 4 });
}

TEST_CASE(TEST_TAG "unique predicate", TEST_TAG) {
  ftl::list<int> list1 = { 1, 2, 2, 3, 3, 4 };
  list1.unique([](const auto &a, const auto &b) { return a < b; });

  REQUIRE(list1 == ftl::list<int>{ 1 });
}

TEST_CASE(TEST_TAG "sort", TEST_TAG) {
  ftl::list<int> list1 = { 5, 1, 3, 2, 4 };
  list1.sort();

  REQUIRE(list1 == ftl::list<int>{ 1, 2, 3, 4, 5 });
}
