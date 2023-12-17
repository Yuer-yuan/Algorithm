#include <gtest/gtest.h>
#include <cstdint>
#include <graph/graph.hpp>
#include <sort/insertion.hpp>
#include <vector>

TEST(all, tiny_graph) {
  uint64_t const V = 13;
  std::vector<std::tuple<uint64_t, uint64_t>> E = {
      {0, 5},   {4, 3},  {0, 1}, {9, 12}, {6, 4},  {5, 4}, {0, 2},
      {11, 12}, {9, 10}, {0, 6}, {7, 8},  {9, 11}, {5, 3}};
  alg::Graph G(V);
  for (auto const& [v, w] : E) {
    G.add_edge(v, w);
  }
  ASSERT_EQ(V, G.V());
  ASSERT_EQ(E.size(), G.E());

  auto get_sorted_adj = [&](uint64_t const v) {
    auto adj_v = G.adj(v);
    alg::Insertion<uint64_t>::sort(adj_v);
    return adj_v;
  };

  auto check_adj = [](std::vector<uint64_t> const& input,
                      std::vector<uint64_t> const& expected) {
    ASSERT_EQ(input.size(), expected.size());
    std::cout << "check adjecent vertices\ninput: ";
    for (uint64_t const v : input) {
      std::cout << v << ' ';
    }
    std::cout << "\nexpect: ";
    for (uint64_t const v : expected) {
      std::cout << v << ' ';
    }
    std::cout << '\n';
    uint64_t n = expected.size();
    for (uint64_t i = 0; i < n; i++) {
      ASSERT_EQ(input[i], expected[i]);
    }
  };

  std::vector<std::vector<uint64_t>> expected_adj = {/*  0 */ {1, 2, 5, 6},
                                                     /*  1 */ {0},
                                                     /*  2 */ {0},
                                                     /*  3 */ {4, 5},
                                                     /*  4 */ {3, 5, 6},
                                                     /*  5 */ {0, 3, 4},
                                                     /*  6 */ {0, 4},
                                                     /*  7 */ {8},
                                                     /*  8 */ {7},
                                                     /*  9 */ {10, 11, 12},
                                                     /* 10 */ {9},
                                                     /* 11 */ {9, 12},
                                                     /* 12 */ {9, 11}};

  for (uint64_t v = 0; v < V; v++) {
    check_adj(get_sorted_adj(v), expected_adj[v]);
  }

  G << std::cout;
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
