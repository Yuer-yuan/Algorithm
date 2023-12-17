#ifndef __ALG_GRAPH_BFS_HPP__
#define __ALG_GRAPH_BFS_HPP__

#include <algorithm>
#include <cstdint>
#include <exception>
#include <iostream>
#include <limits>
#include <queue>
#include <stdexcept>
#include <vector>

#include <graph/graph.hpp>
#include <sort/common.hpp>

namespace alg {

class BreathFirstPaths {
  static constexpr uint64_t INF = std::numeric_limits<uint64_t>::max();
  std::vector<bool> marked_;
  std::vector<uint64_t> edge_to_;
  std::vector<uint64_t> dist_to_;

 public:
  BreathFirstPaths(Graph const& G, uint64_t const s) {
    int const V = G.V();
    marked_.resize(V, false);
    edge_to_.resize(V, INF);
    dist_to_.resize(V, INF);
    if (!is_valid_vertex(s)) {
      throw std::runtime_error("error constructing BFSPaths: invalid source");
    }
    bfs(G, s);
  }

  BreathFirstPaths(Graph const& G, std::vector<uint64_t> const& sources) {
    uint64_t const V = G.V();
    marked_.resize(V, false);
    edge_to_.resize(V, INF);
    dist_to_.resize(V, INF);
    if (!is_valid_vertices(sources)) {
      throw std::runtime_error("error constructing BFSPaths: invalid sources");
    }
    bfs(G, sources);
  }

  bool has_path_to(uint64_t const v) const {
    if (!is_valid_vertex(v)) {
      throw std::runtime_error("error checking path to invalid vertex");
    }
    return marked_[v];
  }

  uint64_t dist_to(uint64_t const v) const {
    if (!is_valid_vertex(v)) {
      throw std::runtime_error("error getting distance to invalid vertex");
    }
    return dist_to_[v];
  }

  std::vector<uint64_t> path_to(uint64_t const v) const {
    std::vector<uint64_t> path;
    if (!is_valid_vertex(v)) {
      throw std::runtime_error("error getting path to invalid vertex");
    }
    if (!has_path_to(v)) {
      return path;
    }
    path.push_back(v);
    for (uint64_t w = v; dist_to_[w] != 0; w = edge_to_[w]) {
      path.push_back(edge_to_[w]);
    }
    std::reverse(path.begin(), path.end());
    return path;
  }

 private:
  void bfs(Graph const& G, uint64_t const s) {
    std::queue<uint64_t> q;
    marked_[s] = true;
    dist_to_[s] = 0;
    q.push(s);
    while (!q.empty()) {
      uint64_t const v = q.front();
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

  void bfs(Graph const& G, std::vector<uint64_t> const& sources) {
    std::queue<int> q;
    for (auto const& s : sources) {
      marked_[s] = true;
      dist_to_[s] = 0;
      q.push(s);
    }
    while (!q.empty()) {
      uint64_t const v = q.front();
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

  bool is_valid_vertex(uint64_t const v) const { return v < marked_.size(); }

  bool is_valid_vertices(std::vector<uint64_t> const& vertices) const {
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
