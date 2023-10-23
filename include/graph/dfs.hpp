#ifndef __ALG_GRAPH_DFS_HPP__
#define __ALG_GRAPH_DFS_HPP__

#include <graph/graph.hpp>
#include <iostream>
#include <sort/common.hpp>
#include <vector>

namespace alg {
/*
 * single-source connectivity
 * Mark all the vertices connected to the source
 */
class DFS {
  std::vector<bool> marked_;
  int count_;  // num of connected vertices (including source itself)

 public:
  DFS(Graph const& G, int const s) : count_(0) {
    marked_.resize(G.V(), false);
    if (!is_valid_vertex(s)) {
      std::cerr << "Depth-first-search error: invalid source\n";
      return;
    }
    dfs(G, s);
  }

  bool marked(int const v) const {
    if (!is_valid_vertex(v)) {
      std::cerr << "Depth-first-search error: invalid node\n";
      return false;
    }
    return marked_[v];
  };

  int count() const { return count_; }

 private:
  inline bool is_valid_vertex(int const v) const {
    return ((size_t)v) < marked_.size();
  }

  void dfs(Graph const& G, int const v) {
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
  std::vector<bool> marked_;
  std::vector<int> edge_to_;
  int s_;

 public:
  DepthFirstPaths(Graph const& G, int const s) : s_(s) {
    marked_.resize(G.V(), false);
    edge_to_.resize(G.V(), -1);
    if (!is_valid_vertex(s_)) {
      std::cerr << "Depth-first-paths error: invalid source\n";
      return;
    }
    dfs(G, s_);
  }

  bool has_path_to(int const v) const {
    if (!is_valid_vertex(v)) {
      std::cerr << "Depth-first-paths error: invalid node\n";
      return false;
    }
    return marked_[v];
  }

  std::vector<int> path_to(int const v) const {
    std::vector<int> path;
    if (!is_valid_vertex(v)) {
      std::cerr << "Depth-first-paths error: invalid node\n";
      return path;
    }
    path.push_back(v);
    for (int w = v; marked_[w] && edge_to_[w] >= 0; w = edge_to_[w]) {
      path.push_back(edge_to_[w]);
    }
    reverse(path, 0, path.size() - 1);
    return path;
  }

 private:
  inline bool is_valid_vertex(int const v) const {
    return ((size_t)v) < marked_.size();
  }

  void dfs(Graph const& G, int const v) {
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
