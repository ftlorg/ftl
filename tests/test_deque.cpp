#include <catch2/catch.hpp>
#include <ftl/ftl.hpp>

#define TEST_TAG "[deque]"

TEST_CASE(TEST_TAG "default ctor", TEST_TAG) {
  ftl::deque<int> deq;

  REQUIRE(deq.size() == 0);
}

TEST_CASE(TEST_TAG "count value ctor", TEST_TAG) {
  std::size_t size = 5;
  ftl::deque<int> deq(size, 10);

  REQUIRE(deq.size() == size);

  for (const auto x : deq) { REQUIRE(x == 10); }
}

TEST_CASE(TEST_TAG "count alloc ctor", TEST_TAG) {
  std::size_t size = 5;
  ftl::deque<int> deq(size);

  REQUIRE(deq.size() == size);

  for (const auto x : deq) { REQUIRE(x == 0); }
}

TEST_CASE(TEST_TAG "input iterator ctor", TEST_TAG) {
  ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };
  ftl::deque<int> deq2 = { deq1.begin(), deq1.end() };

  REQUIRE(deq1.size() == deq2.size());

  auto iter1 = deq1.begin();
  auto iter2 = deq2.begin();
  for (; iter1 != deq1.end() && iter2 != deq2.end(); iter1++, iter2++) { REQUIRE(*iter1 == *iter2); }
}

TEST_CASE(TEST_TAG "copy ctor", TEST_TAG) {
  ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };
  ftl::deque<int> deq2 = deq1;

  REQUIRE(deq1.size() == deq2.size());

  auto iter1 = deq1.begin();
  auto iter2 = deq2.begin();
  for (; iter1 != deq1.end() && iter2 != deq2.end(); iter1++, iter2++) { REQUIRE(*iter1 == *iter2); }
}

TEST_CASE(TEST_TAG "move ctor", TEST_TAG) {
  ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };
  ftl::deque<int> deq2 = std::move(deq1);


  int x = 0;
  for (auto iter2 = deq2.begin(); iter2 != deq2.end(); iter2++) { REQUIRE(*iter2 == ++x); }
}

TEST_CASE(TEST_TAG "initializer_deq ctor", TEST_TAG) {
  ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };

  int x = 0;
  for (auto iter1 = deq1.begin(); iter1 != deq1.end(); iter1++) { REQUIRE(*iter1 == ++x); }
}

TEST_CASE(TEST_TAG "operator=", TEST_TAG) {
  ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };
  ftl::deque<int> deq2 = { 5, 4, 3, 2, 1 };
  deq1 = deq2;

  int x = 5;
  for (auto iter1 = deq1.begin(); iter1 != deq1.end(); iter1++) { REQUIRE(*iter1 == x--); }
}

TEST_CASE(TEST_TAG "move operator=", TEST_TAG) {
  ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };
  deq1 = ftl::deque<int>{ 5, 4, 3, 2, 1 };

  int x = 5;
  for (auto iter1 = deq1.begin(); iter1 != deq1.end(); iter1++) { REQUIRE(*iter1 == x--); }
}

TEST_CASE(TEST_TAG "assign", TEST_TAG) {
  ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };
  deq1.assign(5u, 10);

  int x = 10;
  for (auto iter1 = deq1.begin(); iter1 != deq1.end(); iter1++) { REQUIRE(*iter1 == x); }
}

TEST_CASE(TEST_TAG "input iterator assign", TEST_TAG) {
  ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };
  ftl::deque<int> deq2 = { 10, 10, 10, 10, 10 };

  deq1.assign(deq2.begin(), deq2.end());

  int x = 10;
  for (auto iter1 = deq1.begin(); iter1 != deq1.end(); iter1++) { REQUIRE(*iter1 == x); }
}

TEST_CASE(TEST_TAG "initializer_deq assign", TEST_TAG) {
  ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };

  deq1.assign({ 10, 10, 10, 10, 10 });

  int x = 10;
  for (auto iter1 = deq1.begin(); iter1 != deq1.end(); iter1++) { REQUIRE(*iter1 == x); }
}

TEST_CASE(TEST_TAG "front", TEST_TAG) {
  ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };

  REQUIRE(deq1.front() == 1);
}

TEST_CASE(TEST_TAG "front const", TEST_TAG) {
  const ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };

  REQUIRE(deq1.front() == 1);
}

TEST_CASE(TEST_TAG "back", TEST_TAG) {
  ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };

  REQUIRE(deq1.back() == 5);
}

TEST_CASE(TEST_TAG "back const", TEST_TAG) {
  const ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };

  REQUIRE(deq1.back() == 5);
}

TEST_CASE(TEST_TAG "begin", TEST_TAG) {
  ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };

  REQUIRE(*deq1.begin() == 1);
}

TEST_CASE(TEST_TAG "begin const", TEST_TAG) {
  const ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };

  REQUIRE(*deq1.begin() == 1);
}

TEST_CASE(TEST_TAG "cbegin const", TEST_TAG) {
  const ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };

  REQUIRE(*deq1.cbegin() == 1);
}

TEST_CASE(TEST_TAG "rbegin", TEST_TAG) {
  ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };

  REQUIRE(*deq1.rbegin() == 5);
}

TEST_CASE(TEST_TAG "rbegin const", TEST_TAG) {
  const ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };

  REQUIRE(*deq1.rbegin() == 5);
}

TEST_CASE(TEST_TAG "crbegin const", TEST_TAG) {
  const ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };

  REQUIRE(*deq1.crbegin() == 5);
}

TEST_CASE(TEST_TAG "empty", TEST_TAG) {
  ftl::deque<int> deq1;
  ftl::deque<int> deq2 = { 1, 2, 3, 4, 5 };

  REQUIRE(deq1.empty() == true);
  REQUIRE(deq2.empty() == false);
}

TEST_CASE(TEST_TAG "empty const", TEST_TAG) {
  const ftl::deque<int> deq1;
  const ftl::deque<int> deq2 = { 1, 2, 3, 4, 5 };

  REQUIRE(deq1.empty() == true);
  REQUIRE(deq2.empty() == false);
}

TEST_CASE(TEST_TAG "size", TEST_TAG) {
  ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };

  REQUIRE(deq1.size() == 5);
}

TEST_CASE(TEST_TAG "size const", TEST_TAG) {
  const ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };

  REQUIRE(deq1.size() == 5);
}

TEST_CASE(TEST_TAG "max_size", TEST_TAG) {
  ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };

  REQUIRE(deq1.max_size() > 0);
}

TEST_CASE(TEST_TAG "max_size const", TEST_TAG) {
  const ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };

  REQUIRE(deq1.max_size() > 0);
}

TEST_CASE(TEST_TAG "clear", TEST_TAG) {
  ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };
  deq1.clear();

  REQUIRE(deq1.size() == 0);
}

TEST_CASE(TEST_TAG "insert", TEST_TAG) {
  ftl::deque<int> deq1;
  deq1.insert(deq1.begin(), 1);

  REQUIRE(deq1.front() == 1);
}

TEST_CASE(TEST_TAG "emplace", TEST_TAG) {
  ftl::deque<int> deq1;
  deq1.emplace(deq1.begin(), 1);

  REQUIRE(deq1.front() == 1);
}

TEST_CASE(TEST_TAG "erase", TEST_TAG) {
  ftl::deque<int> deq1 = { 1, 2, 3, 4, 5 };
  deq1.erase(deq1.begin());

  REQUIRE(deq1 == ftl::deque<int>{ 2, 3, 4, 5 });
}

TEST_CASE(TEST_TAG "push_back", TEST_TAG) {
  ftl::deque<int> deq1 = {};

  deq1.push_back(1);
  REQUIRE(deq1 == ftl::deque<int>{ 1 });

  deq1.push_back(2);
  REQUIRE(deq1 == ftl::deque<int>{ 1, 2 });

  deq1.push_back(3);
  REQUIRE(deq1 == ftl::deque<int>{ 1, 2, 3 });
}

TEST_CASE(TEST_TAG "emplace_back", TEST_TAG) {
  ftl::deque<int> deq1 = {};

  deq1.emplace_back(1);
  REQUIRE(deq1 == ftl::deque<int>{ 1 });

  deq1.emplace_back(2);
  REQUIRE(deq1 == ftl::deque<int>{ 1, 2 });

  deq1.emplace_back(3);
  REQUIRE(deq1 == ftl::deque<int>{ 1, 2, 3 });
}

TEST_CASE(TEST_TAG "pop_back", TEST_TAG) {
  ftl::deque<int> deq1 = { 1, 2, 3, 4 };

  deq1.pop_back();
  REQUIRE(deq1 == ftl::deque<int>{ 1, 2, 3 });

  deq1.pop_back();
  REQUIRE(deq1 == ftl::deque<int>{ 1, 2 });

  deq1.pop_back();
  REQUIRE(deq1 == ftl::deque<int>{ 1 });
}

TEST_CASE(TEST_TAG "push_front", TEST_TAG) {
  ftl::deque<int> deq1 = {};

  deq1.push_front(1);
  REQUIRE(deq1 == ftl::deque<int>{ 1 });

  deq1.push_front(2);
  REQUIRE(deq1 == ftl::deque<int>{ 2, 1 });

  deq1.push_front(3);
  REQUIRE(deq1 == ftl::deque<int>{ 3, 2, 1 });
}

TEST_CASE(TEST_TAG "emplace_front", TEST_TAG) {
  ftl::deque<int> deq1 = {};

  deq1.emplace_front(1);
  REQUIRE(deq1 == ftl::deque<int>{ 1 });

  deq1.emplace_front(2);
  REQUIRE(deq1 == ftl::deque<int>{ 2, 1 });

  deq1.emplace_front(3);
  REQUIRE(deq1 == ftl::deque<int>{ 3, 2, 1 });
}

TEST_CASE(TEST_TAG "pop_front", TEST_TAG) {
  ftl::deque<int> deq1 = { 1, 2, 3, 4 };

  deq1.pop_front();
  REQUIRE(deq1 == ftl::deque<int>{ 2, 3, 4 });

  deq1.pop_front();
  REQUIRE(deq1 == ftl::deque<int>{ 3, 4 });

  deq1.pop_front();
  REQUIRE(deq1 == ftl::deque<int>{ 4 });
}

TEST_CASE(TEST_TAG "resize", TEST_TAG) {
  ftl::deque<int> deq1 = {};
  deq1.resize(5);

  REQUIRE(deq1.size() == 5);
  REQUIRE(deq1 == ftl::deque<int>{ 0, 0, 0, 0, 0 });
}

TEST_CASE(TEST_TAG "swap", TEST_TAG) {
  ftl::deque<int> deq1 = { 1, 2, 3 };
  ftl::deque<int> deq2 = { 3, 2, 1 };
  deq1.swap(deq2);

  REQUIRE(deq1 == ftl::deque<int>{ 3, 2, 1 });
  REQUIRE(deq2 == ftl::deque<int>{ 1, 2, 3 });
}

TEST_CASE(TEST_TAG "to_deq", TEST_TAG) {
  std::deque<int> deq = { 1, 2, 3, 4, 5 };
  const auto ftl_deq = ftl::to_deque(deq);

  REQUIRE(ftl_deq == ftl::deque<int>{ 1, 2, 3, 4, 5 });
}
