#include <gtest/gtest.h>
#include <graph/bfs.hpp>
#include <graph/graph.hpp>
#include <sort/common.hpp>
#include <vector>

TEST(bfs_path, single_source) {
  uint64_t const V = 6;
  std::vector<std::tuple<uint64_t, uint64_t>> E = {
      {0, 5}, {2, 4}, {2, 3}, {1, 2}, {0, 1}, {3, 4}, {3, 5}, {0, 2}};
  alg::Graph G(V);
  for (auto const& [v, w] : E) {
    G.add_edge(v, w);
  }

  uint64_t const s = 0;
  alg::BreathFirstPaths bfs(G, s);
  std::cout << "source: " << s << '\n';
  for (uint64_t v = 0; v < V; v++) {
    ASSERT_TRUE(bfs.has_path_to(v));
    std::cout << "path to " << v << " has distance of " << bfs.dist_to(v)
              << ": ";
    auto const path = bfs.path_to(v);
    uint64_t const n = path.size();
    for (uint64_t i = 0; i < n; i++) {
      if (i != 0) {
        std::cout << "->";
      }
      std::cout << path[i];
    }
    std::cout << '\n';
  }
}

TEST(bfs_path, multi_sources) {
  uint64_t const V = 6;
  std::vector<std::tuple<uint64_t, uint64_t>> E = {
      {0, 5}, {2, 4}, {2, 3}, {1, 2}, {0, 1}, {3, 4}, {3, 5}, {0, 2}};
  alg::Graph G(V);
  for (auto const& [v, w] : E) {
    G.add_edge(v, w);
  }

  std::vector<uint64_t> sources = {0, 1};
  alg::BreathFirstPaths bfs(G, sources);
  std::cout << "sources: ";
  for (auto const& s : sources) {
    std::cout << s << ' ';
  }
  std::cout << '\n';
  for (uint64_t v = 0; v < V; v++) {
    ASSERT_TRUE(bfs.has_path_to(v));
    std::cout << "path to " << v << " has distance of " << bfs.dist_to(v)
              << ": ";
    auto const path = bfs.path_to(v);
    uint64_t const n = path.size();
    for (uint64_t i = 0; i < n; i++) {
      if (i != 0) {
        std::cout << "->";
      }
      std::cout << path[i];
    }
    std::cout << '\n';
  }
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
