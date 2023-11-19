#ifndef __ALG_GRAPH_DIRECTED_DFS_HPP__
#define __ALG_GRAPH_DIRECTED_DFS_HPP__

#include <cassert>
#include <cstdint>
#include <graph/digraph.hpp>
#include <iostream>
#include <vector>
#include "sort/common.hpp"

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

/*
 * depth first search ordering
 */
class DepthFirstOrder {
  std::vector<uint64_t> marked_;
  std::vector<uint64_t> pre_;   // pre_[v] = preorder number of v
  std::vector<uint64_t> post_;  // post_[v] = postorder number of v
  std::vector<uint64_t> pre_order_, post_order_;
  uint64_t pre_cnt_, post_cnt_;

 public:
  DepthFirstOrder(Digraph const& G) : pre_cnt_(0), post_cnt_(0) {
    uint64_t const V = G.V();
    marked_.resize(V, false);
    pre_.resize(V, 0);
    post_.resize(V, 0);
    pre_order_.reserve(V);
    post_order_.reserve(V);
    for (uint64_t v = 0; v < V; v++) {
      if (!marked_[v]) {
        dfs(G, v);
      }
    }
    assert(check());
  }

  uint64_t pre(uint64_t const v) const { return pre_[v]; }
  uint64_t post(uint64_t const v) const { return post_[v]; }
  std::vector<uint64_t> pre_order() const { return pre_order_; }
  std::vector<uint64_t> post_order() const { return post_order_; }
  std::vector<uint64_t> rev_post_order() const {
    std::vector<uint64_t> rev = post_order_;
    reverse(rev, 0, rev.size() - 1);
    return rev;
  }

 private:
  void dfs(Digraph const& G, uint64_t const v) {
    marked_[v] = true;
    pre_order_.push_back(v);
    pre_[v] = pre_cnt_++;
    for (uint64_t const w : G.adj(v)) {
      if (!marked_[w]) {
        dfs(G, w);
      }
    }
    post_order_.push_back(v);
    post_[v] = post_cnt_++;
  }
  bool is_valid_vertex(uint64_t const v) const { return v < marked_.size(); }
  bool check() const {
    uint64_t r = 0;
    for (uint64_t v : pre_order()) {
      if (pre(v) != r++) {
        return false;
      }
    }
    r = 0;
    for (uint64_t v : post_order()) {
      if (post(v) != r++) {
        return false;
      }
    }
    return true;
  }
};
};  // namespace alg

#endif  // !__ALG_GRAPH_DIRECTED_DFS_HPP__
