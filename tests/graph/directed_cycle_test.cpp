#include <gtest/gtest.h>
#include <cstdint>
#include <graph/digraph.hpp>
#include <graph/directed_cycle.hpp>
#include <sort/insertion.hpp>
#include <utility>
#include <vector>

void print_cycle(std::vector<uint64_t> const& cycle) {
  for (uint64_t v : cycle) {
    std::cout << v << ' ';
  }
  std::cout << '\n';
}

TEST(graph1, has_cycle) {
  uint64_t const V = 13;
  alg::Digraph G(V);
  std::vector<std::pair<uint64_t, uint64_t>> edges = {
      {0, 1},  {0, 5},  {2, 0},   {2, 3},  {3, 2},   {3, 5}, {4, 2}, {4, 3},
      {5, 4},  {6, 0},  {6, 4},   {6, 9},  {7, 6},   {7, 8}, {8, 7}, {8, 9},
      {9, 10}, {9, 11}, {10, 12}, {11, 4}, {11, 12}, {12, 9}};
  for (auto const& [v, w] : edges) {
    G.add_edge(v, w);
  }

  alg::DirectedCycle detector(G);
  EXPECT_EQ(detector.has_cycle(), true);
  auto cycle = detector.cycle();
  print_cycle(cycle);
}

TEST(graph2, no_cycle) {
  uint64_t const V = 13;
  alg::Digraph G(V);
  std::vector<std::pair<uint64_t, uint64_t>> edges = {
      {0, 1}, {0, 5}, {2, 0}, {2, 3}, {4, 3},  {5, 4},  {6, 0},  {6, 4},
      {6, 9}, {7, 6}, {8, 7}, {8, 9}, {9, 10}, {9, 11}, {11, 4}, {12, 9}};
  for (auto const& [v, w] : edges) {
    G.add_edge(v, w);
  }

  alg::DirectedCycle detector(G);
  EXPECT_EQ(detector.has_cycle(), false);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
