#ifndef __ALG_GRAPH_SCC_HPP__
#define __ALG_GRAPH_SCC_HPP__

#include <cstdint>
#include <exception>
#include <fstream>
#include <vector>

#include <graph/digraph.hpp>
#include <graph/directed_dfs.hpp>

namespace alg {
/*
 * compute strong connected components
 */
class SCC {
  std::vector<bool> marked_;
  std::vector<uint64_t> id_;    // id=id_[v] represents that v is in cc id
  std::vector<uint64_t> size_;  // size_[id] is the number of vertices in cc id
  uint64_t count_;              // num of ccs

 public:
  // constrcut with a Digraph
  SCC(Digraph const& G) : count_(0) {
    uint64_t const V = G.V();
    marked_.resize(V, false);
    id_.resize(V, 0);
    DepthFirstOrder const order(G.reverse());
    for (auto const& v : order.rev_post_order()) {
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
      throw std::runtime_error("error getting id of scc for invalid vertex");
    }
    return id_[v];
  }

  // number of connected components
  uint64_t count() const { return count_; }

  // size of the connected component containing v
  uint64_t size(uint64_t const v) const {
    if (!is_valid_vertex(v)) {
      throw std::runtime_error("error getting size of scc for invalid vertex");
    }
    return size_[id_[v]];
  }

  // whethter v and w are connected
  bool strongly_connected(uint64_t const v, uint64_t const w) const {
    if (!is_valid_vertex(v) || !is_valid_vertex(w)) {
      throw std::runtime_error(
          "error checking strong connectivity for invalid vertices");
    }
    return id_[v] == id_[w];
  }

  std::ostream& operator<<(std::ostream& os) const {
    std::vector<std::vector<uint64_t>> ccs;
    ccs.resize(count_, std::vector<uint64_t>());
    for (uint64_t i = 0; i < count_; i++) {
      ccs[i].reserve(size_[i]);
    }
    uint64_t const V = marked_.size();
    for (uint64_t v = 0; v < V; v++) {
      ccs[id_[v]].push_back(v);
    }
    os << "strongly connected components: " << count_ << '\n';
    for (uint64_t i = 0; i < count_; i++) {
      os << "class " << i << ":";
      for (auto const& v : ccs[i]) {
        os << ' ' << v;
      }
      os << '\n';
    }
    return os;
  }

 private:
  void dfs(Digraph const& G, uint64_t const v) {
    uint64_t const id = count_ - 1;
    marked_[v] = true;
    id_[v] = id;
    size_[id]++;
    for (uint64_t const& w : G.adj(v)) {
      if (!marked_[w]) {
        dfs(G, w);
      }
    }
  }

  bool is_valid_vertex(uint64_t const v) const { return v < marked_.size(); }
};

};      // namespace alg
#endif  // !__ALG_GRAPH_SCC_HPP__
