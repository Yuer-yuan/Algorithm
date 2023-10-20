#include <gtest/gtest.h>
#include <graph/graph.hpp>
#include <sort/insertion.hpp>
#include <vector>

TEST(all, tiny_graph) {
  int const V = 13;
  std::vector<std::tuple<int, int>> E = {
      {0, 5},   {4, 3},  {0, 1}, {9, 12}, {6, 4},  {5, 4}, {0, 2},
      {11, 12}, {9, 10}, {0, 6}, {7, 8},  {9, 11}, {5, 3}};
  alg::Graph G(V);
  for (auto const& [v, w] : E) {
    G.add_edge(v, w);
  }
  ASSERT_EQ(V, G.v());
  ASSERT_EQ(E.size(), G.e());

  auto get_sorted_adj = [&](int const v) {
    auto adj_v = G.adj(v);
    alg::Insertion<int>::sort(adj_v);
    return adj_v;
  };

  auto check_adj = [](std::vector<int> const& input,
                      std::vector<int> const& expected) {
    ASSERT_EQ(input.size(), expected.size());
    std::cout << "check adjecent vertices\ninput: ";
    for (int const v : input) {
      std::cout << v << ' ';
    }
    std::cout << "\nexpect: ";
    for (int const v : expected) {
      std::cout << v << ' ';
    }
    std::cout << '\n';
    int n = expected.size();
    for (int i = 0; i < n; i++) {
      ASSERT_EQ(input[i], expected[i]);
    }
  };

  std::vector<std::vector<int>> expected_adj = {/*  0 */ {1, 2, 5, 6},
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

  for (int v = 0; v < V; v++) {
    check_adj(get_sorted_adj(v), expected_adj[v]);
  }

  std::cout << G.str();
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
