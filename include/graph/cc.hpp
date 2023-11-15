#ifndef __ALG_GRAPH_CC_HPP__
#define __ALG_GRAPH_CC_HPP__
#include <graph/graph.hpp>
#include <iostream>
#include <vector>
namespace alg {
class ConnectedComponents {
  std::vector<bool> marked_;
  std::vector<int> id_;
  std::vector<int> size_;
  int count_;  // num of cc

 public:
  ConnectedComponents(Graph const& G) : count_(0) {
    int const V = G.V();
    marked_.resize(V, false);
    id_.resize(V, -1);
    for (int v = 0; v < V; v++) {
      if (!marked_[v]) {
        size_.push_back(0);
        count_++;
        dfs(G, v);
      }
    }
  }

  int id(int const v) const {
    if (!is_valid_vertex(v)) {
      std::cerr << "ConnectedComponents error: invalid vertex\n";
      return -1;
    }
    return id_[v];
  }

  int count() const { return count_; }

  int size(int const v) const {
    if (!is_valid_vertex(v)) {
      std::cerr << "ConnectedComponents error: invalid vertex\n";
      return -1;
    }
    return size_[id_[v]];
  }

  bool connected(int const v, int const w) const {
    if (!is_valid_vertex(v) || !is_valid_vertex(w)) {
      std::cerr << "ConnectedComponents error: invalid vertex\n";
      return false;
    }
    return id_[v] == id_[w];
  }

 private:
  void dfs(Graph const& G, int const v) {
    marked_[v] = true;
    id_[v] = count_ - 1;
    size_[count_ - 1]++;
    for (int const& w : G.adj(v)) {
      if (!marked_[w]) {
        dfs(G, w);
      }
    }
  }

  inline bool is_valid_vertex(int const v) const {
    return v >= 0 && (size_t)v < marked_.size();
  }
};
};      // namespace alg
#endif  // !__ALG_GRAPH_CC_HPP__
