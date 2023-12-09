#include "graph/topological.hpp"
#include <gtest/gtest.h>
#include <cstdint>
#include <graph/digraph.hpp>
#include <graph/directed_cycle.hpp>
#include <sort/insertion.hpp>
#include <utility>
#include <vector>

TEST(graph1, no_cycle) {
  uint64_t const V = 13;
  alg::Digraph G(V);
  std::vector<std::pair<uint64_t, uint64_t>> edges = {
      {0, 1}, {0, 5}, {0, 6}, {2, 0}, {2, 3},  {3, 5},  {5, 4},
      {6, 4}, {6, 9}, {7, 6}, {8, 7}, {9, 10}, {9, 11}, {11, 12}};
  for (auto const& [v, w] : edges) {
    G.add_edge(v, w);
  }

  alg::DirectedCycle detector(G);
  ASSERT_EQ(detector.has_cycle(), false);

  alg::Topological topological(G);
  auto print_vec = [](std::vector<uint64_t> const& v) {
    for (uint64_t i = 0; i < v.size(); i++) {
      std::cout << v[i] << ' ';
    }
    std::cout << '\n';
  };
  auto input = topological.order();
  std::cout << "got:\n";
  print_vec(input);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
