#include <gtest/gtest.h>

#include <compare>
#include <iostream>
#include <ostream>
#include <search/bst.hpp>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

TEST(put, check_with_size) {
  alg::BST<int, int> bst;
  std::vector<std::tuple<int, int>> examples = {
      {1, 9}, {2, 8}, {4, 6}, {5, 5}, {3, 7}};
  for (std::tuple<int, int> t : examples) {
    bst.put(std::get<0>(t), std::get<1>(t));
  }
  EXPECT_EQ(bst.size(), 5);
}

TEST(get, check_each_element) {
  alg::BST<int, int> bst;
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
  alg::BST<int, int> bst;
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
  alg::BST<int, int> bst;
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
  alg::BST<int, int> bst;
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
  alg::BST<int, int> bst;
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
  alg::BST<int, int> bst;
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
  alg::BST<int, int> bst;
  std::vector<std::tuple<int, int>> examples = {
      {1, 9}, {2, 8}, {4, 6}, {5, 5}, {3, 7}};
  for (std::tuple<int, int> t : examples) {
    bst.put(std::get<0>(t), std::get<1>(t));
  }

  bst << std::cout;
  bst.del_max();
  bst << std::cout;
  bst.del_max();
  bst << std::cout;
  bst.del_max();
  bst << std::cout;
  bst.del_max();
  bst << std::cout;
  bst.del_max();
  bst << std::cout;
  bst.del_max();
  bst << std::cout;
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
  alg::BST<WrapClass, int> bst;
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
