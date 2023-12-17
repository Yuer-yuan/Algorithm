#include <array>
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

#include <gtest/gtest.h>
#include <graph/digraph.hpp>
#include "graph/scc.hpp"

TEST(all, tiny_graph) {
  uint64_t const V = 13;
  alg::Digraph G(V);
  std::vector<std::pair<uint64_t, uint64_t>> edges{
      {0, 1}, {0, 5}, {2, 0},  {2, 3},  {3, 2},   {3, 5},   {4, 2},
      {4, 3}, {5, 4}, {6, 0},  {6, 4},  {6, 9},   {7, 6},   {7, 8},
      {8, 7}, {8, 9}, {9, 10}, {9, 11}, {10, 12}, {11, 12}, {12, 9}};
  for (auto const& [v, w] : edges) {
    G.add_edge(v, w);
  }

  alg::SCC const scc(G);
  scc << std::cout;
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
