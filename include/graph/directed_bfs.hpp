#ifndef __ALG_GRAPH_DIRECTED_BFS_HPP__
#define __ALG_GRAPH_DIRECTED_BFS_HPP__

#include <cassert>
#include <cstdint>
#include <graph/digraph.hpp>
#include <limits>
#include <queue>
#include <sort/common.hpp>
#include <vector>

namespace alg {
/*
 * find shortest path from single source or multi sources
 */
class BreathFirstDirectedPaths {
  static constexpr uint64_t INF = std::numeric_limits<uint64_t>::max();
  std::vector<bool> marked_;
  std::vector<uint64_t> edge_to_;
  std::vector<uint64_t> dist_to_;

 public:
  /*
   * single-source shortest path
   */
  BreathFirstDirectedPaths(Digraph const& G, uint64_t const s) {
    uint64_t V = G.V();
    marked_.resize(V, false);
    edge_to_.resize(V, INF);
    dist_to_.resize(V, INF);
    assert(is_valid_vertex(s));
    bfs(G, s);
  }

  /*
   * multi-sources shortest path
   */
  BreathFirstDirectedPaths(Digraph const& G, std::vector<uint64_t> const& vs) {
    uint64_t V = G.V();
    marked_.resize(V, false);
    edge_to_.resize(V, INF);
    dist_to_.resize(V, INF);
    assert(is_valid_vertices(vs));
    bfs(G, vs);
  }

  /*
   * is there a path from source or sources to v
   */
  bool has_path_to(uint64_t const v) const {
    assert(is_valid_vertex(v));
    return marked_[v];
  };

  /*
   * number of edges from source or sources to v
   * INF if unreachable
   */
  uint64_t dist_to(uint64_t const v) const {
    assert(is_valid_vertex(v));
    return dist_to_[v];
  };

  /*
   * shortest path from source or sources to v
   */
  std::vector<uint64_t> path_to(uint64_t const v) const {
    assert(is_valid_vertex(v));
    std::vector<uint64_t> path;
    if (!has_path_to(v)) {
      return path;
    }
    path.push_back(v);
    for (uint64_t w = v; dist_to_[w] != 0; w = edge_to_[w]) {
      path.push_back(w);
    }
    reverse(path, 0, path.size());
    return path;
  };

 private:
  void bfs(Digraph const& G, uint64_t const s) {
    std::queue<uint64_t> q;
    dist_to_[s] = 0;
    marked_[s] = true;
    q.push(s);
    while (!q.empty()) {
      uint64_t const v = q.front();
      q.pop();
      for (uint64_t w : G.adj(v)) {
        if (!marked_[w]) {
          edge_to_[w] = v;
          dist_to_[w] = dist_to_[v] + 1;
          marked_[w] = true;
          q.push(w);
        }
      }
    }
  }
  void bfs(Digraph const& G, std::vector<uint64_t> const& vs) {
    std::queue<uint64_t> q;
    for (uint64_t const v : vs) {
      dist_to_[v] = 0;
      marked_[v] = true;
      q.push(v);
    }
    while (!q.empty()) {
      uint64_t const v = q.front();
      q.pop();
      for (uint64_t const w : G.adj(v)) {
        if (!marked_[w]) {
          edge_to_[w] = v;
          dist_to_[w] = dist_to_[v] + 1;
          marked_[w] = true;
          q.push(w);
        }
      }
    }
  }
  bool is_valid_vertex(uint64_t const v) const { return v < marked_.size(); }
  bool is_valid_vertices(std::vector<uint64_t> const& vs) const {
    for (uint64_t v : vs) {
      if (!is_valid_vertex(v)) {
        return false;
      }
    }
    return true;
  };
};
};      // namespace alg
#endif  // !__ALG_GRAPH_DIRECTED_BFS_HPP__
