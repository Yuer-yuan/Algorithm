#ifndef __ALG_GRAPH_BFS_HPP__
#define __ALG_GRAPH_BFS_HPP__

#include <graph/graph.hpp>
#include <iostream>
#include <limits>
#include <queue>
#include <sort/common.hpp>
#include <vector>

namespace alg {
class BreathFirstPaths {
  static constexpr int INF = -1;
  std::vector<bool> marked_;
  std::vector<int> edge_to_;
  std::vector<int> dist_to_;

 public:
  BreathFirstPaths(Graph const& G, int const s) {
    int const V = G.V();
    marked_.resize(V, false);
    edge_to_.resize(V, INF);
    dist_to_.resize(V, INF);
    if (!is_valid_vertex(s)) {
      std::cerr << "BreathFirstPaths error: invalid source\n";
      return;
    }
    bfs(G, s);
  }

  BreathFirstPaths(Graph const& G, std::vector<int> const& sources) {
    int const V = G.V();
    marked_.resize(V, false);
    edge_to_.resize(V, INF);
    dist_to_.resize(V, INF);
    if (!is_valid_vertices(sources)) {
      std::cerr << "BreathFirstPaths error: invalid sources\n";
      return;
    }
    bfs(G, sources);
  }

  bool has_path_to(int const v) const {
    if (!is_valid_vertex(v)) {
      std::cerr
          << "BreathFirstPaths check connectivity error: invalid vertex\n";
      return false;
    }
    return marked_[v];
  }

  int dist_to(int const v) const {
    if (!is_valid_vertex(v)) {
      std::cerr << "BreathFirstPaths get distance error: invalid vertex\n";
      return INF;
    }
    return dist_to_[v];
  }

  std::vector<int> path_to(int const v) const {
    std::vector<int> path;
    if (!is_valid_vertex(v)) {
      std::cerr << "BreathFirstPaths find path error: invalid vertex\n";
      return path;
    }
    if (!has_path_to(v)) {
      return path;
    }
    path.push_back(v);
    for (int w = v; dist_to_[w] != 0; w = edge_to_[w]) {
      path.push_back(edge_to_[w]);
    }
    reverse(path, 0, path.size() - 1);
    return path;
  }

 private:
  void bfs(Graph const& G, int const s) {
    std::queue<int> q;
    marked_[s] = true;
    dist_to_[s] = 0;
    q.push(s);
    while (!q.empty()) {
      int const v = q.front();
      q.pop();
      for (auto const& w : G.adj(v)) {
        if (!marked_[w]) {
          marked_[w] = true;
          edge_to_[w] = v;
          dist_to_[w] = dist_to_[v] + 1;
          q.push(w);
        }
      }
    }
  }

  void bfs(Graph const& G, std::vector<int> const& sources) {
    std::queue<int> q;
    for (auto const& s : sources) {
      marked_[s] = true;
      dist_to_[s] = 0;
      q.push(s);
    }
    while (!q.empty()) {
      int const v = q.front();
      q.pop();
      for (auto const& w : G.adj(v)) {
        if (!marked_[w]) {
          marked_[w] = true;
          edge_to_[w] = v;
          dist_to_[w] = dist_to_[v] + 1;
          q.push(w);
        }
      }
    }
  }

  bool is_valid_vertex(int const v) const {
    if (v < 0 || ((size_t)v) >= marked_.size()) {
      return false;
    }
    return true;
  }

  bool is_valid_vertices(std::vector<int> const& vertices) const {
    for (auto const& v : vertices) {
      if (!is_valid_vertex(v)) {
        return false;
      }
    }
    return true;
  }
};
};      // namespace alg
#endif  // !__ALG_GRAPH_BFS_HPP__
