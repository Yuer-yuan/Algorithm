#ifndef __ALG_GRAPH_CC_HPP__
#define __ALG_GRAPH_CC_HPP__

#include <cstdint>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>

#include <graph/graph.hpp>

namespace alg {

class ConnectedComponents {
  std::vector<bool> marked_;
  std::vector<uint64_t> id_;    // id=id_[v] represents that v is in cc id
  std::vector<uint64_t> size_;  // size_[id] is the number of vertices in cc id
  uint64_t count_;              // num of ccs

 public:
  // constrcut with a Graph
  ConnectedComponents(Graph const& G) : count_(0) {
    uint64_t const V = G.V();
    marked_.resize(V, false);
    id_.resize(V, 0);
    for (uint64_t v = 0; v < V; v++) {
      if (!marked_[v]) {
        size_.push_back(0);
        count_++;
        dfs(G, v);
      }
    }
  }

  // which cc does v belong to
  uint64_t id(uint64_t const v) const {
    if (!is_valid_vertex(v)) {
      throw std::runtime_error("invalid vertex");
    }
    return id_[v];
  }

  // number of connected components
  uint64_t count() const { return count_; }

  // size of the connected component containing v
  uint64_t size(uint64_t const v) const {
    if (!is_valid_vertex(v)) {
      throw std::runtime_error("invalid vertex");
    }
    return size_[id_[v]];
  }

  // whethter v and w are connected
  bool connected(uint64_t const v, uint64_t const w) const {
    if (!is_valid_vertex(v) || !is_valid_vertex(w)) {
      throw std::runtime_error("invalid vertex");
    }
    return id_[v] == id_[w];
  }

 private:
  void dfs(Graph const& G, uint64_t const v) {
    marked_[v] = true;
    id_[v] = count_ - 1;
    size_[count_ - 1]++;
    for (uint64_t const& w : G.adj(v)) {
      if (!marked_[w]) {
        dfs(G, w);
      }
    }
  }

  bool is_valid_vertex(uint64_t const v) const { return v < marked_.size(); }
};
};      // namespace alg
#endif  // !__ALG_GRAPH_CC_HPP__
