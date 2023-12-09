#include <gtest/gtest.h>
#include <graph/dfs.hpp>
#include <graph/graph.hpp>
#include <sort/common.hpp>
#include <vector>

TEST(common, reverse) {
  auto reverse_and_print = [](std::vector<int>& v, int const s, int const e) {
    std::cout << "before reverse: ";
    for (int const& i : v) {
      std::cout << i << ' ';
    }
    std::cout << '\n';

    alg::reverse(v, s, e);
    std::cout << "after reverse: ";
    for (int const& i : v) {
      std::cout << i << ' ';
    }
    std::cout << '\n';
  };

  auto check_vector = [](std::vector<int> const& input,
                         std::vector<int> const& expect) {
    ASSERT_EQ(input.size(), expect.size());
    int const n = input.size();
    for (int i = 0; i < n; i++) {
      ASSERT_EQ(input[i], expect[i]);
    }
  };

  std::vector<int> v1;
  std::vector<int> const v1_e;
  reverse_and_print(v1, 0, v1.size() - 1);
  check_vector(v1, v1_e);

  std::vector<int> v2 = {1};
  std::vector<int> const v2_e = {1};
  reverse_and_print(v2, 0, v2.size() - 1);
  check_vector(v2, v2_e);

  std::vector<int> v3 = {1, 2};
  std::vector<int> const v3_e = {2, 1};
  reverse_and_print(v3, 0, v3.size() - 1);
  check_vector(v3, v3_e);

  std::vector<int> v4 = {1, 2, 3, 4, 5};
  std::vector<int> const v4_e = {5, 4, 3, 2, 1};
  reverse_and_print(v4, 0, v4.size() - 1);
  check_vector(v4, v4_e);

  std::vector<int> v5 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<int> const v5_e = {1, 7, 6, 5, 4, 3, 2, 8};
  reverse_and_print(v5, 1, v5.size() - 2);
}

TEST(dfs, mark) {
  int const V = 6;
  std::vector<std::tuple<int, int>> E = {{0, 5}, {2, 4}, {2, 3}, {1, 2},
                                         {0, 1}, {3, 4}, {3, 5}, {0, 2}};
  alg::Graph G(V);
  for (auto const& [v, w] : E) {
    G.add_edge(v, w);
  }

  alg::DFS dfs(G, 0);
  ASSERT_EQ(dfs.count(), G.adj(0).size() * 2);
  for (int v = 0; v < V; v++) {
    ASSERT_TRUE(dfs.marked(v));
  }
}

TEST(dfs_path, mark) {
  int const V = 6;
  std::vector<std::tuple<int, int>> E = {{0, 5}, {2, 4}, {2, 3}, {1, 2},
                                         {0, 1}, {3, 4}, {3, 5}, {0, 2}};
  alg::Graph G(V);
  for (auto const& [v, w] : E) {
    G.add_edge(v, w);
  }

  int const s = 0;
  alg::DepthFirstPaths dfs(G, s);
  std::cout << "source: " << s << '\n';
  for (int v = 0; v < V; v++) {
    ASSERT_TRUE(dfs.has_path_to(v));
    std::cout << "path to " << v << ": ";
    auto const path = dfs.path_to(v);
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
