#ifndef __ALG_GRAPH_DFS_HPP__
#define __ALG_GRAPH_DFS_HPP__

#include <algorithm>
#include <cstdint>
#include <exception>
#include <iostream>
#include <limits>
#include <sort/common.hpp>
#include <stdexcept>
#include <vector>

#include <graph/graph.hpp>

namespace alg {

/*
 * single-source connectivity of undirected graph
 * Mark all the vertices connected to the source
 */
class DFS {
  std::vector<bool> marked_;
  uint64_t count_;  // num of connected vertices (including source itself)

 public:
  // construct with a graph and specify which vertex to start with
  DFS(Graph const& G, uint64_t const s) : count_(0) {
    marked_.resize(G.V(), false);
    if (!is_valid_vertex(s)) {
      throw std::runtime_error("error constructing DFS: invalid source vertex");
    }
    dfs(G, s);
  }

  // whether v is reachable from s
  bool marked(uint64_t const v) const {
    if (!is_valid_vertex(v)) {
      throw std::runtime_error("error checking reachablity: invalid vertex");
    }
    return marked_[v];
  };

  // number of connected components
  uint64_t count() const { return count_; }

 private:
  bool is_valid_vertex(uint64_t const v) const { return v < marked_.size(); }

  void dfs(Graph const& G, uint64_t const v) {
    marked_[v] = true;
    count_++;
    for (auto const& w : G.adj(v)) {
      if (!marked_[w]) {
        dfs(G, w);
      }
    }
  }
};

/* single-source paths */
class DepthFirstPaths {
  constexpr static uint64_t INF = std::numeric_limits<uint64_t>::max();
  std::vector<bool> marked_;
  std::vector<uint64_t> edge_to_;
  uint64_t s_;

 public:
  DepthFirstPaths(Graph const& G, uint64_t const s) : s_(s) {
    marked_.resize(G.V(), false);
    edge_to_.resize(G.V(), INF);
    if (!is_valid_vertex(s_)) {
      throw std::runtime_error("error constructing DFSPaths: invalid source");
    }
    dfs(G, s_);
  }

  bool has_path_to(uint64_t const v) const {
    if (!is_valid_vertex(v)) {
      throw std::runtime_error("error checking path to invalid vertex");
    }
    return marked_[v];
  }

  std::vector<uint64_t> path_to(uint64_t const v) const {
    std::vector<uint64_t> path;
    if (!is_valid_vertex(v)) {
      throw std::runtime_error("error getting path to invalid vertex");
    }
    path.push_back(v);
    for (uint64_t w = v; marked_[w] && edge_to_[w] != INF; w = edge_to_[w]) {
      path.push_back(edge_to_[w]);
    }
    std::reverse(path.begin(), path.end());
    return path;
  }

 private:
  bool is_valid_vertex(uint64_t const v) const { return v < marked_.size(); }

  void dfs(Graph const& G, uint64_t const v) {
    marked_[v] = true;
    for (auto const& w : G.adj(v)) {
      if (!marked_[w]) {
        edge_to_[w] = v;
        dfs(G, w);
      }
    }
  }
};
};  // namespace alg

#endif  // !__ALG_GRAPH_DFS_HPP__
