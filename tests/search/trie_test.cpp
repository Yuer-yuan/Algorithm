#include "search/trie.hpp"

#include <gtest/gtest.h>

#include <compare>
#include <cstdint>
#include <iostream>
#include <optional>
#include <ostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

TEST(put_and_size, check_with_size) {
	alg::Trie<uint8_t> t;
	t.put("a", 0);
	t.put("ab", 1);
	t.put("b", 2);
	t.put("ba", 3);
	EXPECT_EQ(t.size(), 4);
}

TEST(put_and_get, check_with_size) {
	alg::Trie<uint8_t> t;
	t.put("a", 0);
	EXPECT_EQ(t.get("a"), 0);
	EXPECT_EQ(t.get("b"), std::nullopt);
	t.put("ab", 1);
	EXPECT_EQ(t.get("a"), 0);
	EXPECT_EQ(t.get("ab"), 1);
	EXPECT_EQ(t.get("b"), std::nullopt);
	t.put("b", 2);
	EXPECT_EQ(t.get("b"), 2);
	t.put("ba", 3);
	EXPECT_EQ(t.get("b"), 2);
	EXPECT_EQ(t.get("ba"), 3);
	t.put("abcde", 4);
	EXPECT_EQ(t.get("abc"), std::nullopt);
	EXPECT_EQ(t.get("abcd"), std::nullopt);
	EXPECT_EQ(t.get("abcde"), 4);
	t.put("abcd", 5);
	EXPECT_EQ(t.get("abcd"), 5);
	EXPECT_EQ(t.get("abcde"), 4);
	EXPECT_EQ(t.get("aab"), std::nullopt);
	t.put("bc", 6);
	EXPECT_EQ(t.get("bc"), 6);
}

TEST(longest_prefix, check_with_size) {
	alg::Trie<uint8_t> t;
	t.put("a", 0);
	t.put("ab", 1);
	t.put("b", 2);
	t.put("ba", 3);
	t.put("abcde", 4);
	t.put("abcd", 5);
	t.put("bc", 6);

	EXPECT_EQ(t.lp("a"), "a");
	EXPECT_EQ(t.lp("ab"), "ab");
	EXPECT_EQ(t.lp("abcd"), "abcd");
	EXPECT_EQ(t.lp("abcde"), "abcde");
	EXPECT_EQ(t.lp("b"), "b");
	EXPECT_EQ(t.lp("ba"), "ba");
	EXPECT_EQ(t.lp("bc"), "bc");

	EXPECT_EQ(t.lp("ac"), "a");
	EXPECT_EQ(t.lp("abc"), "ab");
	EXPECT_EQ(t.lp("abcdef"), "abcde");
	EXPECT_EQ(t.lp("bb"), "b");
	EXPECT_EQ(t.lp("bd"), "b");
	EXPECT_EQ(t.lp("bcd"), "bc");
	EXPECT_EQ(t.lp("c"), "");
}

int
main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
