#ifndef __ALG_GRAPH_DIRECTED_DFS_HPP__
#define __ALG_GRAPH_DIRECTED_DFS_HPP__

#include <cassert>
#include <cstdint>
#include <graph/digraph.hpp>
#include <iostream>
#include <vector>

namespace alg {
/*
 * single source or multi sources reachability
 */
class DirectedDFS {
  std::vector<bool> marked_;
  uint64_t cnt_;

 public:
  /*
   * single source reachability
   */
  DirectedDFS(Digraph const& G, uint64_t const s) : cnt_(0) {
    marked_.resize(G.V(), false);
    assert(is_valid_vertex(s));
    dfs(G, s);
  };

  /*
   * multi sources reachability
   */
  DirectedDFS(Digraph const& G, std::vector<uint64_t> const& vs) : cnt_(0) {
    marked_.resize(G.V(), false);
    assert(is_valid_vertices(vs));
    for (uint64_t s : vs) {
      if (!marked_[s]) {
        dfs(G, s);
      }
    }
  };

  /*
   * is v reachable
   */
  bool marked(uint64_t const v) const {
    assert(is_valid_vertex(v));
    return marked_[v];
  };

  /*
   * reachable vertices amount
   */
  uint64_t count() const { return cnt_; };

 private:
  void dfs(Digraph const& G, uint64_t const v) {
    cnt_++;
    marked_[v] = true;
    for (uint64_t w : G.adj(v)) {
      if (!marked_[w]) {
        dfs(G, w);
      }
    }
  }

  bool is_valid_vertex(uint64_t const v) const { return v < marked_.size(); }

  bool is_valid_vertices(std::vector<uint64_t> const& vs) {
    for (uint64_t v : vs) {
      if (!is_valid_vertex(v)) {
        return false;
      }
    }
    return true;
  }
};
};  // namespace alg

#endif  // !__ALG_GRAPH_DIRECTED_DFS_HPP__
