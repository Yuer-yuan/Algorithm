#include <gtest/gtest.h>
#include <iostream>
#include <search/llrb.hpp>
#include <string>
#include <time/timer.hpp>
#include <tuple>
#include <utility>
#include <vector>
#include "random/random.hpp"

TEST(put, check_with_size) {
  alg::LLRB<int, int> bst;
  std::vector<std::tuple<int, int>> examples = {
      {1, 9}, {2, 8}, {4, 6}, {5, 5}, {3, 7}};
  for (std::tuple<int, int> t : examples) {
    bst.put(std::get<0>(t), std::get<1>(t));
  }
  EXPECT_EQ(bst.size(), 5);
}

TEST(get, check_each_element) {
  alg::LLRB<int, int> bst;
  std::vector<std::tuple<int, int>> examples = {
      {1, 9}, {2, 8}, {4, 6}, {5, 5}, {3, 7}};
  for (std::tuple<int, int> t : examples) {
    bst.put(std::get<0>(t), std::get<1>(t));
  }
  EXPECT_EQ(*bst.get(1), 9);
  EXPECT_EQ(*bst.get(2), 8);
  EXPECT_EQ(*bst.get(3), 7);
  EXPECT_EQ(*bst.get(4), 6);
  EXPECT_EQ(*bst.get(5), 5);
}

TEST(del, check_with_size) {
  alg::LLRB<int, int> bst;
  std::vector<std::tuple<int, int>> examples = {
      {1, 9}, {2, 8}, {4, 6}, {5, 5}, {3, 7}

  };
  for (std::tuple<int, int> t : examples) {
    bst.put(std::get<0>(t), std::get<1>(t));
  }
  EXPECT_EQ(bst.size(), 5);
  EXPECT_TRUE(bst.contains(1));
  bst.del(1);
  EXPECT_FALSE(bst.contains(1));
  EXPECT_EQ(bst.size(), 4);
  EXPECT_TRUE(bst.contains(3));
  bst.del(3);
  EXPECT_FALSE(bst.contains(3));
  EXPECT_EQ(bst.size(), 3);
  EXPECT_FALSE(bst.contains(6));
  bst.del(6);
  EXPECT_EQ(bst.size(), 3);
}

TEST(del_min, check_with_contains) {
  alg::LLRB<int, int> bst;
  std::vector<std::tuple<int, int>> examples = {
      {3, 7}, {1, 9}, {2, 8}, {4, 6}, {5, 5}};
  for (std::tuple<int, int> t : examples) {
    bst.put(std::get<0>(t), std::get<1>(t));
  }

  std::cout << "deleting min 1\n";
  EXPECT_TRUE(bst.contains(1));
  bst.del_min();
  EXPECT_FALSE(bst.contains(1));

  std::cout << "deleting min 2\n";
  EXPECT_TRUE(bst.contains(2));
  bst.del_min();
  EXPECT_FALSE(bst.contains(2));

  std::cout << "deleting min 3\n";
  EXPECT_TRUE(bst.contains(3));
  bst.del_min();
  EXPECT_FALSE(bst.contains(3));

  std::cout << "deleting min 4\n";
  EXPECT_TRUE(bst.contains(4));
  bst.del_min();
  EXPECT_FALSE(bst.contains(4));

  std::cout << "deleting min 5\n";
  EXPECT_TRUE(bst.contains(5));
  bst.del_min();
  EXPECT_FALSE(bst.contains(5));
}

TEST(del_max, check_with_contains) {
  alg::LLRB<int, int> bst;
  std::vector<std::tuple<int, int>> examples = {
      {1, 9}, {2, 8}, {4, 6}, {5, 5}, {3, 7}};
  for (std::tuple<int, int> t : examples) {
    bst.put(std::get<0>(t), std::get<1>(t));
  }
  auto print_keys = [](std::vector<int> const& keys) {
    for (int i : keys) {
      std::cout << i << ' ';
    }
    std::cout << '\n';
  };

  EXPECT_TRUE(bst.contains(5));
  std::cout << "before delete max:\n";
  print_keys(bst.keys());
  bst.del_max();
  EXPECT_FALSE(bst.contains(5));
  std::cout << "after delete max:\n";
  print_keys(bst.keys());

  EXPECT_TRUE(bst.contains(4));
  std::cout << "before delete max:\n";
  print_keys(bst.keys());
  bst.del_max();
  EXPECT_FALSE(bst.contains(4));
  std::cout << "after delete max:\n";
  print_keys(bst.keys());

  EXPECT_TRUE(bst.contains(3));
  std::cout << "before delete max:\n";
  print_keys(bst.keys());
  bst.del_max();
  EXPECT_FALSE(bst.contains(3));
  std::cout << "after delete max:\n";
  print_keys(bst.keys());

  EXPECT_TRUE(bst.contains(2));
  std::cout << "before delete max:\n";
  print_keys(bst.keys());
  bst.del_max();
  EXPECT_FALSE(bst.contains(2));
  std::cout << "after delete max:\n";
  print_keys(bst.keys());

  EXPECT_TRUE(bst.contains(1));
  std::cout << "before delete max:\n";
  print_keys(bst.keys());
  bst.del_max();
  EXPECT_FALSE(bst.contains(1));
  std::cout << "after delete max:\n";
  print_keys(bst.keys());
}

TEST(contains, check_existance) {
  alg::LLRB<int, int> bst;
  std::vector<std::tuple<int, int>> examples = {
      {1, 9}, {2, 8}, {4, 6}, {5, 5}, {3, 7}

  };
  for (std::tuple<int, int> t : examples) {
    bst.put(std::get<0>(t), std::get<1>(t));
  }
  EXPECT_TRUE(bst.contains(1));
  EXPECT_TRUE(bst.contains(2));
  EXPECT_TRUE(bst.contains(3));
  EXPECT_TRUE(bst.contains(4));
  EXPECT_TRUE(bst.contains(5));
  EXPECT_FALSE(bst.contains(6));
}

TEST(keys, check_one_by_one) {
  alg::LLRB<int, int> bst;
  std::vector<std::tuple<int, int>> examples = {
      {1, 9}, {2, 8}, {4, 6}, {5, 5}, {3, 7}};
  for (std::tuple<int, int> t : examples) {
    bst.put(std::get<0>(t), std::get<1>(t));
  }

  auto print_keys = [](std::vector<int> const& keys) {
    for (int i : keys) {
      std::cout << i << ' ';
    }
    std::cout << '\n';
  };

  print_keys(bst.keys());

  bst.del_max();
  print_keys(bst.keys());

  bst.del_max();
  print_keys(bst.keys());

  bst.del_max();
  print_keys(bst.keys());

  bst.del_max();
  print_keys(bst.keys());

  bst.del_max();
  print_keys(bst.keys());
}

TEST(print, test_print) {
  alg::LLRB<int, int> bst;
  std::vector<std::tuple<int, int>> examples = {
      {1, 9}, {2, 8}, {4, 6}, {5, 5}, {3, 7}};
  for (std::tuple<int, int> t : examples) {
    bst.put(std::get<0>(t), std::get<1>(t));
  }

  bst.print(std::cout);
  bst.del_max();
  bst.print(std::cout);
  bst.del_max();
  bst.print(std::cout);
  bst.del_max();
  bst.print(std::cout);
  bst.del_max();
  bst.print(std::cout);
  bst.del_max();
  bst.print(std::cout);
  bst.del_max();
}

TEST(all, random_test_with_inner_check) {
  alg::LLRB<int, int> bst;
  int const lo = 1000;
  int const hi = 10000;

  auto generator = alg::RandIntGen<int>(lo, hi);
  int const capacity = generator.gen();
  std::cout << "capacity: " << capacity << '\n';

  // test put
  for (int i = 0; i < capacity; i++) {
    int const integer = generator.gen();
    bst.put(integer, 0);
  }

  // test del min
  for (int i = 0; i < capacity / 10; i++) {
    int const min_key = bst.min().value();
    bst.del_min();
    ASSERT_FALSE(bst.contains(min_key));
  }

  // test del max
  for (int i = 0; i < capacity / 10; i++) {
    int const max_key = bst.max().value();
    bst.del_max();
    ASSERT_FALSE(bst.contains(max_key));
  }

  // test del
  for (int i = 0; i < capacity / 10; i++) {
    int const integer = generator.gen();
    if (bst.contains(integer)) {
      bst.del(integer);
    }
    ASSERT_FALSE(bst.contains(integer));
  }
}

TEST(ALL, test_single_element) {
  int const lo = 1000;
  int const hi = 10000;
  auto generator = alg::RandIntGen<int>(lo, hi);

  // test single del_min
  {
    alg::LLRB<int, int> bst;
    int const input = generator.gen();
    bst.put(input, 0);
    ASSERT_TRUE(bst.contains(input));
    bst.del_min();
    ASSERT_FALSE(bst.contains(input));
    bst.del_min();  // nothing happen
  }

  // test single del_max
  {
    alg::LLRB<int, int> bst;
    int const input = generator.gen();
    bst.put(input, 0);
    ASSERT_TRUE(bst.contains(input));
    bst.del_max();
    ASSERT_FALSE(bst.contains(input));
    bst.del_max();  // nothing happen
  }

  // test single del
  {
    alg::LLRB<int, int> bst;
    int const input = generator.gen();
    bst.put(input, 0);
    ASSERT_TRUE(bst.contains(input));
    bst.del(input);
    ASSERT_FALSE(bst.contains(input));
    bst.del(input + 1);  // nothing happen
  }
}

class WrapClass {
 private:
  std::string str1;
  std::string str2;

 public:
  WrapClass(std::string& str1, std::string& str2) : str1(str1), str2(str2) {}

  WrapClass(char const* str1, char const* str2)
      : str1(std::string(str1)), str2(std::string(str2)) {}

  std::strong_ordering operator<=>(WrapClass const& rhs) const {
    if (auto cmp = (str1 <=> rhs.str1); cmp != 0)
      return cmp;
    return str2 <=> rhs.str2;
  }
};

TEST(init, test_wrap_class) {
  alg::LLRB<WrapClass, int> bst;
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
