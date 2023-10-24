#include <gtest/gtest.h>
#include <graph/bfs.hpp>
#include <graph/graph.hpp>
#include <sort/common.hpp>
#include <vector>

TEST(bfs_path, single_source) {
  int const V = 6;
  std::vector<std::tuple<int, int>> E = {{0, 5}, {2, 4}, {2, 3}, {1, 2},
                                         {0, 1}, {3, 4}, {3, 5}, {0, 2}};
  alg::Graph G(V);
  for (auto const& [v, w] : E) {
    G.add_edge(v, w);
  }

  int const s = 0;
  alg::BreathFirstPaths bfs(G, s);
  std::cout << "source: " << s << '\n';
  for (int v = 0; v < V; v++) {
    ASSERT_TRUE(bfs.has_path_to(v));
    std::cout << "path to " << v << " has distance of " << bfs.dist_to(v)
              << ": ";
    auto const path = bfs.path_to(v);
    int const n = path.size();
    for (int i = 0; i < n; i++) {
      if (i != 0) {
        std::cout << "->";
      }
      std::cout << path[i];
    }
    std::cout << '\n';
  }
}

TEST(bfs_path, multi_sources) {
  int const V = 6;
  std::vector<std::tuple<int, int>> E = {{0, 5}, {2, 4}, {2, 3}, {1, 2},
                                         {0, 1}, {3, 4}, {3, 5}, {0, 2}};
  alg::Graph G(V);
  for (auto const& [v, w] : E) {
    G.add_edge(v, w);
  }

  std::vector<int> sources = {0, 1};
  alg::BreathFirstPaths bfs(G, sources);
  std::cout << "sources: ";
  for (auto const& s : sources) {
    std::cout << s << ' ';
  }
  std::cout << '\n';
  for (int v = 0; v < V; v++) {
    ASSERT_TRUE(bfs.has_path_to(v));
    std::cout << "path to " << v << " has distance of " << bfs.dist_to(v)
              << ": ";
    auto const path = bfs.path_to(v);
    int const n = path.size();
    for (int i = 0; i < n; i++) {
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
