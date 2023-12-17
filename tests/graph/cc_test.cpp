#include <gtest/gtest.h>
#include <vector>

#include <graph/cc.hpp>
#include <graph/graph.hpp>
#include <sort/common.hpp>

TEST(cc, connected) {
  uint64_t const V = 6;
  std::vector<std::tuple<uint64_t, uint64_t>> E = {
      {0, 5}, {2, 4}, {2, 3}, {1, 2}, {0, 1}, {3, 4}, {3, 5}, {0, 2}};
  alg::Graph G(V);
  for (auto const& [v, w] : E) {
    G.add_edge(v, w);
  }

  alg::ConnectedComponents cc(G);
  ASSERT_EQ(cc.count(), 1);
  for (uint64_t v = 0; v < V; v++) {
    ASSERT_EQ(cc.id(v), 0);
    ASSERT_EQ(cc.size(v), V);
    for (uint64_t w = 0; w < V; w++) {
      ASSERT_TRUE(cc.connected(v, w));
    }
  }
}

TEST(cc, two_connected_components) {
  uint64_t const V = 6;
  std::vector<std::tuple<uint64_t, uint64_t>> E = {
      {1, 2}, {0, 1}, {3, 4}, {3, 5}, {0, 2}};
  alg::Graph G(V);
  for (auto const& [v, w] : E) {
    G.add_edge(v, w);
  }

  alg::ConnectedComponents cc(G);
  ASSERT_EQ(cc.count(), 2);
  for (uint64_t v = 0; v <= 2; v++) {
    ASSERT_EQ(cc.id(v), 0);
    ASSERT_EQ(cc.size(v), 3);
    for (uint64_t w = 0; w <= 2; w++) {
      ASSERT_TRUE(cc.connected(v, w));
    }
    for (uint64_t w = 3; w <= 5; w++) {
      ASSERT_FALSE(cc.connected(v, w));
    }
  }
  for (uint64_t v = 3; v <= 5; v++) {
    ASSERT_EQ(cc.id(v), 1);
    ASSERT_EQ(cc.size(v), 3);
    for (uint64_t w = 0; w <= 2; w++) {
      ASSERT_FALSE(cc.connected(v, w));
    }
    for (uint64_t w = 3; w <= 5; w++) {
      ASSERT_TRUE(cc.connected(v, w));
    }
  }
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
