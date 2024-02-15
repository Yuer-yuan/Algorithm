#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <random/random.hpp>
#include <sort/heap.hpp>
#include <sort/quick.hpp>
#include <time/timer.hpp>
#include "sort/common.hpp"

using namespace alg;

// test priority queue
TEST(pq, init) {
  // default constructor
  PriorityQueue<int> pq1;
  // construct with self defined cmparator
  auto cmp = [](int const& t1, int const& t2) { return t1 > t2; };
  PriorityQueue<int, cmp> pq2;
  // construct with vector data
  std::vector<int> keys = {1, 6, 3, 8, 5, 9, 0};
  PriorityQueue<int> pq3(keys);
  Quick<int>::sort(keys);
  int const n = keys.size();
  for (int i = 0; i < n; i++) {
    int const min_key = pq3.pop();
    ASSERT_EQ(min_key, keys[i]);
    ASSERT_EQ(pq3.size(), n - i - 1);
  }
  try {
    pq3.pop();
  } catch (std::runtime_error const& e) {
    ASSERT_TRUE(true);
  }
}

TEST(pq, size) {
  std::vector<int> keys = {1, 6, 3, 8, 5, 9, 0};
  int const expect = keys.size();
  PriorityQueue<int> pq(keys);
  int const output = pq.size();
  std::cout << "expect: " << expect << ", and ouput: " << output << '\n';
  ASSERT_EQ(expect, output);

  // test if keys are immutable
  keys.pop_back();
  int const expect2 = expect;
  int const output2 = pq.size();
  std::cout << "after pop back, expect: " << expect2
            << ", and ouput: " << output2 << '\n';
  ASSERT_EQ(expect, output2);

  // test empty queue
  PriorityQueue<int> pq2;
  int const expect3 = 0;
  int const output3 = pq2.size();
  ASSERT_EQ(expect3, output3);
}

TEST(pq, push_with_sorted) {
  // test pushing with sorted array
  std::vector<std::string> data = {"apple", "banana", "cat", "dog", "egg"};
  PriorityQueue<std::string> pq;
  int const n = data.size();
  for (int i = 0; i < n; i++) {
    pq.push(data[i]);
    ASSERT_EQ(i + 1, pq.size());
  }
  for (int i = 0; i < n; i++) {
    std::string const min_val = pq.pop();
    ASSERT_EQ(data[i], min_val);
    ASSERT_EQ(pq.size(), n - i - 1);
  }
  try {
    pq.pop();
  } catch (std::runtime_error const& e) {
    ASSERT_TRUE(true);
  }
}

TEST(pq, push_with_random) {
  // test pushing with sorted array
  std::vector<std::string> data = {"apple", "banana", "cat", "dog", "egg"};
  Random<std::string>::shuffle(data);
  PriorityQueue<std::string> pq;
  int const n = data.size();
  for (int i = 0; i < n; i++) {
    pq.push(data[i]);
    ASSERT_EQ(i + 1, pq.size());
  }
  Quick<std::string>::sort(data);
  for (int i = 0; i < n; i++) {
    std::string const min_val = pq.pop();
    ASSERT_EQ(data[i], min_val);
    ASSERT_EQ(pq.size(), n - i - 1);
  }
  try {
    pq.pop();
  } catch (std::runtime_error const& e) {
    ASSERT_TRUE(true);
  }
}

TEST(pq, push_with_random_and_greater_order) {
  // test pushing with sorted array
  std::vector<std::string> data = {"apple", "banana", "cat", "dog", "egg"};
  Random<std::string>::shuffle(data);
  PriorityQueue<std::string, Order<std::string>::greater> pq;
  int const n = data.size();
  for (int i = 0; i < n; i++) {
    pq.push(data[i]);
    ASSERT_EQ(i + 1, pq.size());
  }
  Quick<std::string, Order<std::string>::greater>::sort(data);
  for (int i = 0; i < n; i++) {
    std::string const max_val = pq.pop();
    ASSERT_EQ(data[i], max_val);
    ASSERT_EQ(pq.size(), n - i - 1);
  }
  try {
    pq.pop();
  } catch (std::runtime_error const& e) {
    ASSERT_TRUE(true);
  }
}

TEST(heap_sort, input_with_int_vec) {
  std::vector<int> input = {6, 4, 10, 9, 7, 7, 8, 10, 8, 9, 10};
  std::vector<int> expect = {4, 6, 7, 7, 8, 8, 9, 9, 10, 10, 10};

  int n = input.size();
  std::cout << "before sort: \n";
  for (int i = 0; i < n; i++) {
    std::cout << input[i] << ' ';
  }
  std::cout << '\n';

  alg::Timer<SystemClock> timer;
  timer.start();

  alg::Heap<int>::sort(input);

  timer.stop();

  std::cout << "after sort: \n";
  for (int i = 0; i < n; i++) {
    std::cout << input[i] << ' ';
  }
  std::cout << '\n';

  std::cout << "elapsed time: " << timer.miliseconds() << "ms\n";

  for (int i = 0; i < n; ++i) {
    ASSERT_EQ(input[i], expect[i]);
  }
}

TEST(heap_sort, input_with_double_vec) {
  std::vector<double> input = {6.1, 4.0,  10.9, 9.8, 7.3, 7.4,
                               8.4, 10.6, 8.6,  9.2, 10.7};
  std::vector<double> expect = {4.0, 6.1, 7.3,  7.4,  8.4, 8.6,
                                9.2, 9.8, 10.6, 10.7, 10.9};

  int n = input.size();
  std::cout << "before sort: \n";
  for (int i = 0; i < n; i++) {
    std::cout << input[i] << ' ';
  }
  std::cout << '\n';

  alg::Timer<HightResolutionClock> timer;
  timer.start();

  alg::Heap<double>::sort(input);

  timer.stop();

  std::cout << "after sort: \n";
  for (int i = 0; i < n; i++) {
    std::cout << input[i] << ' ';
  }
  std::cout << '\n';

  std::cout << "elapsed time: " << timer.seconds() << "s, or "
            << timer.miliseconds() << "ms\n";

  for (int i = 0; i < n; ++i) {
    ASSERT_DOUBLE_EQ(input[i], expect[i]);
  }
}

TEST(heap_sort, input_with_str_vec) {
  std::vector<std::string> input = {"bug", "bed", "be", "cat", "alpha", "zoo"};
  std::vector<std::string> expect = {"alpha", "be", "bed", "bug", "cat", "zoo"};

  int n = input.size();
  std::cout << "before sort: \n";
  for (int i = 0; i < n; i++) {
    std::cout << input[i] << ' ';
  }
  std::cout << '\n';

  alg::Timer<SystemClock> timer;
  timer.start();

  alg::Heap<std::string>::sort(input);

  timer.stop();

  std::cout << "after sort: \n";
  for (int i = 0; i < n; i++) {
    std::cout << input[i] << ' ';
  }
  std::cout << '\n';

  for (int i = 0; i < n; ++i) {
    ASSERT_EQ(input[i], expect[i]);
  }
}

TEST(heap_sort_user_defined_order, input_with_int_vec) {
  std::vector<int> input = {6, 4, 10, 9, 7, 7, 8, 10, 8, 9, 10};
  std::vector<int> expect = {10, 10, 10, 9, 9, 8, 8, 7, 7, 6, 4};

  int n = input.size();
  std::cout << "before sort: \n";
  for (int i = 0; i < n; i++) {
    std::cout << input[i] << ' ';
  }
  std::cout << '\n';

  alg::Timer<SystemClock> timer;
  timer.start();

  alg::Heap<int, alg::Order<int>::greater>::sort(input);

  timer.stop();

  std::cout << "after sort: \n";
  for (int i = 0; i < n; i++) {
    std::cout << input[i] << ' ';
  }
  std::cout << '\n';

  std::cout << "elapsed time: " << timer.seconds() << "s\n";

  for (int i = 0; i < n; ++i) {
    ASSERT_EQ(input[i], expect[i]);
  }
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
