#include <gtest/gtest.h>
#include <functional>
#include <random/random.hpp>
#include <search/common.hpp>
#include <search/seperate_chaining.hpp>
#include "sort/quick.hpp"

TEST(put_and_get, small_case) {
  auto hash = alg::Hash<int>::hash;
  alg::SeperateChaining<int, int> st(hash);
  std::vector<std::tuple<int, int>> input = {{1, 0}, {2, 0}, {3, 0}};
  int cnt = 0;

  // consistency of size, get and put
  for (auto const& [key, val] : input) {
    ASSERT_EQ(cnt, st.size());
    ASSERT_FALSE(st.contains(key));
    st.put(key, val);
    ASSERT_EQ(++cnt, st.size());
    ASSERT_TRUE(st.contains(key));
    auto got = st.get(key).value();
    ASSERT_EQ(val, got);
  }

  // test value update
  auto updated = std::vector<std::tuple<int, int>>(input);
  for (auto& [key, val] : updated) {
    val++;
  }
  int n = input.size();
  for (int i = 0; i < n; i++) {
    ASSERT_EQ(std::get<1>(updated[i]), std::get<1>(input[i]) + 1);
  }
  for (auto const& [key, val] : input) {
    st.put(key, val);
    ASSERT_EQ(cnt, st.size());
    auto got = st.get(key).value();
    ASSERT_EQ(val, got);
  }
}

TEST(del, small_case) {
  alg::SeperateChaining<int, int> st(alg::Hash<int>::hash);
  std::vector<std::tuple<int, int>> input = {{1, 0}, {2, 0}, {3, 0}};
  int cnt = 0;

  // consistency of size, get and put
  for (auto const& [key, val] : input) {
    ASSERT_EQ(cnt, st.size());
    ASSERT_FALSE(st.contains(key));
    st.put(key, val);
    ASSERT_EQ(++cnt, st.size());
    ASSERT_TRUE(st.contains(key));
    auto got = st.get(key).value();
    ASSERT_EQ(val, got);
  }

  // delete
  for (auto const& [key, _val] : input) {
    st.del(key);
    ASSERT_FALSE(st.contains(key));
    ASSERT_EQ(st.size(), --cnt);
  }
  st.del(0);  // stdout, error message
  st.del(1);  // stdout, error message
}

TEST(all, random) {
  auto st = alg::SeperateChaining<int, int>(alg::Hash<int>::hash);
  int const lo = 1000, hi = 10000;
  int const val_lo = 0, val_hi = std::numeric_limits<int>::max();
  auto generator = alg::RandIntGen<int>(lo, hi);
  int const n = generator.gen();
  std::cout << "n: " << n << '\n';
  auto ikeys = std::vector<int>();

  for (int i = 0; i < n; i++) {
    auto key_generator = alg::RandIntGen<>(val_lo, val_hi);
    int const key = key_generator.gen();
    int val = 0;

    if (st.contains(key)) {
      val = st.get(key).value() + 1;
    } else {
      st.put(key, val);
      ikeys.push_back(key);
    }
  }

  auto okeys = st.keys();
  ASSERT_EQ(okeys.size(), ikeys.size());
  alg::Quick<int>::sort(ikeys);
  alg::Quick<int>::sort(okeys);
  for (size_t i = 0; i < okeys.size(); i++) {
    ASSERT_EQ(ikeys[i], okeys[i]);
  }

  int const range = ikeys.size();
  auto rand_idx_generator = alg::RandIntGen<int>(0, range - 1);
  for (int i = 0; i < n / 10; i++) {
    int const idx = rand_idx_generator.gen();
    st.del(ikeys[idx]);
  }
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
