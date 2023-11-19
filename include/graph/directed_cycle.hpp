#ifndef __ALG_GRAPH_DIRECTED_CYCLE__
#define __ALG_GRAPH_DIRECTED_CYCLE__

#include <cassert>
#include <cstdint>
#include <vector>
#include "graph/digraph.hpp"
#include "sort/common.hpp"
namespace alg {
/*
 * cycle detection of digraph
 */
class DirectedCycle {
  std::vector<bool> marked_;       // marked_[v] -- has v been marked?
  std::vector<uint64_t> edge_to_;  // if w = edge_to_[v] -- w -> v
  std::vector<bool> on_stack_;     // on_stack_[v] -- is v on stack?
  std::vector<uint64_t> cycle_;    // detected cycle

 public:
  DirectedCycle(Digraph const& G) {
    uint64_t const V = G.V();
    marked_.resize(V, false);
    edge_to_.resize(V);
    on_stack_.resize(V, false);
    for (uint64_t v = 0; v < V; v++) {
      if (!marked_[v] && !has_cycle()) {
        dfs(G, v);
      }
    }
  }

  bool has_cycle() const { return cycle_.size() != 0; }

  std::vector<uint64_t> cycle() const { return cycle_; }

 private:
  void dfs(Digraph const& G, uint64_t const v) {
    marked_[v] = true;
    on_stack_[v] = true;
    for (uint64_t w : G.adj(v)) {
      if (has_cycle()) {
        return;
      }
      if (!marked_[w]) {
        marked_[w] = true;
        edge_to_[w] = v;
        dfs(G, w);
      } else if (on_stack_[w]) {
        // find a cycle -- a path v -> w -> v
        for (uint64_t x = v; x != w; x = edge_to_[x]) {
          cycle_.push_back(x);
        }
        cycle_.push_back(w);
        cycle_.push_back(v);
        reverse(cycle_, 0, cycle_.size() - 1);
      }
    }
    on_stack_[v] = false;
  }
};
};      // namespace alg
#endif  // !__ALG_GRAPH_DIRECTED_CYCLE__
