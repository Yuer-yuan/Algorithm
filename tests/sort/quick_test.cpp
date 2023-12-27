#include <cstdint>
#include <iostream>
#include <vector>

#include <random/random.hpp>
#include <sort/common.hpp>
#include <sort/quick.hpp>
#include <time/timer.hpp>

#include <gtest/gtest.h>

// test quick
TEST(plain_order, input_with_int_vec) {
  std::vector<int> input = {6, 4, 10, 9, 7, 7, 8, 10, 8, 9, 10};
  std::vector<int> expect = {4, 6, 7, 7, 8, 8, 9, 9, 10, 10, 10};

  uint64_t n = input.size();
  std::cout << "before sort: \n";
  for (uint64_t i = 0; i < n; i++) {
    std::cout << input[i] << ' ';
  }
  std::cout << '\n';

  alg::Timer<SystemClock> timer;
  timer.start();

  alg::Quick<int>::sort(input);

  timer.stop();

  std::cout << "after sort: \n";
  for (uint64_t i = 0; i < n; i++) {
    std::cout << input[i] << ' ';
  }
  std::cout << '\n';

  std::cout << "elapsed time: " << timer.miliseconds() << "ms\n";

  for (uint64_t i = 0; i < n; ++i) {
    ASSERT_EQ(input[i], expect[i]);
  }
}

/* TEST(plain_order, input_with_double_vec) { */
/*   std::vector<double> input = {6.1, 4.0,  10.9, 9.8, 7.3, 7.4, */
/*                                8.4, 10.6, 8.6,  9.2, 10.7}; */
/*   std::vector<double> expect = {4.0, 6.1, 7.3,  7.4,  8.4, 8.6, */
/*                                 9.2, 9.8, 10.6, 10.7, 10.9}; */
/**/
/*   int n = input.size(); */
/*   std::cout << "before sort: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/**/
/*   alg::Timer<HightResolutionClock> timer; */
/*   timer.start(); */
/**/
/*   alg::Quick<double>::sort(input); */
/**/
/*   timer.stop(); */
/**/
/*   std::cout << "after sort: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/**/
/*   std::cout << "elapsed time: " << timer.seconds() << "s, or " */
/*             << timer.miliseconds() << "ms\n"; */
/**/
/*   for (int i = 0; i < n; ++i) { */
/*     ASSERT_DOUBLE_EQ(input[i], expect[i]); */
/*   } */
/* } */
/**/
/* TEST(plain_order, input_with_str_vec) { */
/*   std::vector<std::string> input = {"bug", "bed", "be", "cat", "alpha",
 * "zoo"}; */
/*   std::vector<std::string> expect = {"alpha", "be", "bed", "bug", "cat",
 * "zoo"}; */
/**/
/*   int n = input.size(); */
/*   std::cout << "before sort: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/**/
/*   alg::Timer<SystemClock> timer; */
/*   timer.start(); */
/**/
/*   alg::Quick<std::string>::sort(input); */
/**/
/*   timer.stop(); */
/**/
/*   std::cout << "after sort: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/**/
/*   for (int i = 0; i < n; ++i) { */
/*     ASSERT_EQ(input[i], expect[i]); */
/*   } */
/* } */
/**/
/* TEST(user_defined_order, input_with_random_vec) { */
/*   std::vector<int> expect = {10, 10, 10, 9, 9, 8, 8, 7, 7, 6, 4}; */
/*   std::vector<int> input = expect; */
/**/
/*   int n = input.size(); */
/*   std::cout << "before shuffle: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/**/
/*   alg::Timer<HightResolutionClock> timer; */
/*   timer.start(); */
/*   alg::Random<int>::shuffle(input); */
/*   timer.stop(); */
/**/
/*   std::cout << "after shuffle: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/*   std::cout << "shuffle elapsed time: " << timer.miliseconds() << "ms\n"; */
/**/
/*   timer.reset(); */
/*   alg::Quick<int>::sort(input, alg::Order<int>::greater); */
/*   timer.stop(); */
/**/
/*   std::cout << "after sort: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/*   std::cout << "sort elapsed time: " << timer.miliseconds() << "ms\n"; */
/**/
/*   for (int i = 0; i < n; ++i) { */
/*     ASSERT_EQ(input[i], expect[i]); */
/*   } */
/* } */
/**/
/* TEST(user_defined_order, input_with_int_vec) { */
/*   std::vector<int> input = {6, 4, 10, 9, 7, 7, 8, 10, 8, 9, 10}; */
/*   std::vector<int> expect = {10, 10, 10, 9, 9, 8, 8, 7, 7, 6, 4}; */
/**/
/*   int n = input.size(); */
/*   std::cout << "before sort: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/**/
/*   alg::Timer<SystemClock> timer; */
/*   timer.start(); */
/**/
/*   alg::Quick<int>::sort(input, alg::Order<int>::greater); */
/**/
/*   timer.stop(); */
/**/
/*   std::cout << "after sort: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/**/
/*   std::cout << "elapsed time: " << timer.seconds() << "s\n"; */
/**/
/*   for (int i = 0; i < n; ++i) { */
/*     ASSERT_EQ(input[i], expect[i]); */
/*   } */
/* } */
/**/
/* // test three-way quick */
/* TEST(plain_order_for_three_way, input_with_int_vec) { */
/*   std::vector<int> input = {6, 4, 10, 9, 7, 7, 8, 10, 8, 9, 10}; */
/*   std::vector<int> expect = {4, 6, 7, 7, 8, 8, 9, 9, 10, 10, 10}; */
/**/
/*   int n = input.size(); */
/*   std::cout << "before sort: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/**/
/*   alg::Timer<SystemClock> timer; */
/*   timer.start(); */
/**/
/*   alg::Quick3Way<int>::sort(input); */
/**/
/*   timer.stop(); */
/**/
/*   std::cout << "after sort: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/**/
/*   std::cout << "elapsed time: " << timer.miliseconds() << "ms\n"; */
/**/
/*   for (int i = 0; i < n; ++i) { */
/*     ASSERT_EQ(input[i], expect[i]); */
/*   } */
/* } */
/**/
/* TEST(plain_order_for_three_way, input_with_double_vec) { */
/*   std::vector<double> input = {6.1, 4.0,  10.9, 9.8, 7.3, 7.4, */
/*                                8.4, 10.6, 8.6,  9.2, 10.7}; */
/*   std::vector<double> expect = {4.0, 6.1, 7.3,  7.4,  8.4, 8.6, */
/*                                 9.2, 9.8, 10.6, 10.7, 10.9}; */
/**/
/*   int n = input.size(); */
/*   std::cout << "before sort: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/**/
/*   alg::Timer<HightResolutionClock> timer; */
/*   timer.start(); */
/**/
/*   alg::Quick3Way<double>::sort(input); */
/**/
/*   timer.stop(); */
/**/
/*   std::cout << "after sort: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/**/
/*   std::cout << "elapsed time: " << timer.seconds() << "s, or " */
/*             << timer.miliseconds() << "ms\n"; */
/**/
/*   for (int i = 0; i < n; ++i) { */
/*     ASSERT_DOUBLE_EQ(input[i], expect[i]); */
/*   } */
/* } */
/**/
/* TEST(plain_order_for_three_way, input_with_str_vec) { */
/*   std::vector<std::string> input = {"bug", "bed", "be", "cat", "alpha",
 * "zoo"}; */
/*   std::vector<std::string> expect = {"alpha", "be", "bed", "bug", "cat",
 * "zoo"}; */
/**/
/*   int n = input.size(); */
/*   std::cout << "before sort: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/**/
/*   alg::Timer<SystemClock> timer; */
/*   timer.start(); */
/**/
/*   alg::Quick3Way<std::string>::sort(input); */
/**/
/*   timer.stop(); */
/**/
/*   std::cout << "after sort: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/**/
/*   for (int i = 0; i < n; ++i) { */
/*     ASSERT_EQ(input[i], expect[i]); */
/*   } */
/* } */
/**/
/* TEST(user_defined_order_for_three_way, input_with_random_vec) { */
/*   std::vector<int> expect = {10, 10, 10, 9, 9, 8, 8, 7, 7, 6, 4}; */
/*   std::vector<int> input = expect; */
/**/
/*   int n = input.size(); */
/*   std::cout << "before shuffle: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/**/
/*   alg::Timer<HightResolutionClock> timer; */
/*   timer.start(); */
/*   alg::Random<int>::shuffle(input); */
/*   timer.stop(); */
/**/
/*   std::cout << "after shuffle: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/*   std::cout << "shuffle elapsed time: " << timer.miliseconds() << "ms\n"; */
/**/
/*   auto cmp = [](int const& t1, int const& t2) { */
/*     if (t1 > t2) { */
/*       return -1; */
/*     } */
/*     if (t1 < t2) { */
/*       return 1; */
/*     } */
/*     return 0; */
/*   }; */
/**/
/*   timer.reset(); */
/*   alg::Quick3Way<int>::sort(input, cmp); */
/*   timer.stop(); */
/**/
/*   std::cout << "after sort: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/*   std::cout << "sort elapsed time: " << timer.miliseconds() << "ms\n"; */
/**/
/*   for (int i = 0; i < n; ++i) { */
/*     ASSERT_EQ(input[i], expect[i]); */
/*   } */
/* } */
/**/
/* TEST(user_defined_order_for_three_way, input_with_int_vec) { */
/*   std::vector<int> input = {6, 4, 10, 9, 7, 7, 8, 10, 8, 9, 10}; */
/*   std::vector<int> expect = {10, 10, 10, 9, 9, 8, 8, 7, 7, 6, 4}; */
/**/
/*   int n = input.size(); */
/*   std::cout << "before sort: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/**/
/*   alg::Timer<SystemClock> timer; */
/**/
/*   auto cmp = [](int const& t1, int const& t2) { */
/*     if (t1 > t2) { */
/*       return -1; */
/*     } */
/*     if (t1 < t2) { */
/*       return 1; */
/*     } */
/*     return 0; */
/*   }; */
/*   timer.start(); */
/*   alg::Quick3Way<int>::sort(input, cmp); */
/*   timer.stop(); */
/**/
/*   std::cout << "after sort: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/**/
/*   std::cout << "elapsed time: " << timer.seconds() << "s\n"; */
/**/
/*   for (int i = 0; i < n; ++i) { */
/*     ASSERT_EQ(input[i], expect[i]); */
/*   } */
/* } */
/**/
/* // test quick select */
/* TEST(plain_order_for_quick_select, str_vec) { */
/*   std::vector<std::string> input = {"bug", "bed", "be", "cat", "alpha",
 * "zoo"}; */
/*   int const k = 3; */
/*   std::string expect = std::string{"bug"}; */
/**/
/*   int n = input.size(); */
/*   std::cout << "before select: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/**/
/*   alg::Timer<SystemClock> timer; */
/*   timer.start(); */
/*   std::string const& output = alg::QuickSelect<std::string>::select(input,
 * k); */
/*   timer.stop(); */
/**/
/*   std::cout << "after select the " << k << "th element: " << output */
/*             << "\nelapsed time: " << timer.seconds() << "s\n"; */
/*   ASSERT_EQ(output, expect); */
/* } */
/**/
/* TEST(user_defined_order_for_quick_select, int_vec) { */
/*   std::vector<int> input = {6, 4, 10, 9, 7, 7, 8, 10, 8, 9, 10}; */
/*   int const k = 5; */
/*   int const expect = 8; */
/**/
/*   int n = input.size(); */
/*   std::cout << "before select: \n"; */
/*   for (int i = 0; i < n; i++) { */
/*     std::cout << input[i] << ' '; */
/*   } */
/*   std::cout << '\n'; */
/**/
/*   alg::Timer<SystemClock> timer; */
/*   timer.start(); */
/*   int const& output = */
/*       alg::QuickSelect<int>::select(input, k, alg::Order<int>::greater); */
/*   timer.stop(); */
/**/
/*   std::cout << "after select the " << k << "th element: " << output */
/*             << "\nelapsed time: " << timer.seconds() << "s\n"; */
/*   ASSERT_EQ(output, expect); */
/* } */

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
