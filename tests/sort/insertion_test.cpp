#include <gtest/gtest.h>
#include <iostream>
#include <sort/common.hpp>
#include <sort/insertion.hpp>
#include <time/timer.hpp>
#include <vector>

TEST(plain_order, input_with_int_vec) {
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

  alg::Insertion<int>::sort(input);

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

TEST(plain_order, input_with_double_vec) {
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

  alg::Insertion<double>::sort(input);

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

TEST(plain_order, input_with_str_vec) {
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

  alg::Insertion<std::string>::sort(input);

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

TEST(user_defined_order, input_with_int_vec) {
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

  alg::Insertion<int, alg::Order<int>::greater>::sort(input);

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
