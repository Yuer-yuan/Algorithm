#ifndef __ALG_GRAPH_TOPOLOGICAL_HPP__
#define __ALG_GRAPH_TOPOLOGICAL_HPP__

#include <cassert>
#include <cstdint>
#include <stdexcept>
#include <vector>

#include "graph/digraph.hpp"
#include "graph/directed_cycle.hpp"
#include "graph/directed_dfs.hpp"

namespace alg {

class Topological {
  std::vector<uint64_t> order_;
  std::vector<uint64_t> rank_;

 public:
  Topological(Digraph const& G) {
    DirectedCycle detector(G);
    if (detector.has_cycle()) {
      throw std::runtime_error(
          "error calculating Topological order for cyclic graph");
    }
    rank_.resize(G.V(), 0);
    DepthFirstOrder orders(G);
    order_ = orders.rev_post_order();
    uint64_t r = 0;
    for (auto const& v : order_) {
      rank_[v] = r;
      r += 1;
    }
  }

  // whether there is a topological order
  bool has_order() const { return !order_.empty(); }

  // topological order of vertices
  std::vector<uint64_t> order() const { return order_; }

  uint64_t rank(uint64_t const v) const {
    if (!is_valid_vertex(v)) {
      throw std::runtime_error("error getting rank of invalid vertex");
    }
    return rank_[v];
  }

 private:
  bool is_valid_vertex(uint64_t const v) const { return v < rank_.size(); }
};
};      // namespace alg
#endif  // !__ALG_GRAPH_TOPOLOGICAL_HPP__
