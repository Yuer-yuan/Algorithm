#ifndef __ALG_GRAPH_GRAPH_HPP_
#define __ALG_GRAPH_GRAPH_HPP_

#include <cstdint>
#include <exception>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace alg {

class Graph {
  uint64_t V_;
  uint64_t E_;
  std::vector<std::vector<uint64_t>> adj_;

 public:
  Graph(uint64_t const V) : V_(V), E_(0) { adj_.resize(V_); }
  Graph(Graph const& G) : V_(G.V_), E_(G.E_), adj_(G.adj_) {}
  Graph& operator=(Graph const& G) {
    this->V_ = G.V_;
    this->E_ = G.E_;
    this->adj_ = G.adj_;
    return *this;
  }
  Graph(Graph&& G) : V_(G.V_), E_(G.E_), adj_(std::move(G.adj_)) {}
  Graph& operator=(Graph&& G) {
    this->V_ = G.V_;
    this->E_ = G.E_;
    this->adj_ = std::move(G.adj_);
    return *this;
  }

  // number of vertices
  uint64_t V() const { return V_; }

  // number of edges
  uint64_t E() const { return E_; }

  // add edge v->w to graph
  void add_edge(uint64_t const v, uint64_t const w) {
    if (!is_valid_vertex(v) || !is_valid_vertex(w)) {
      throw std::runtime_error("error adding edge: invalid vertex");
    }
    E_++;
    adj_[v].push_back(w);
    adj_[w].push_back(v);
  }

  std::vector<uint64_t> adj(uint64_t const v) const {
    if (!is_valid_vertex(v)) {
      throw std::runtime_error("error getting adjecency list: invalid vertex");
    }
    return adj_[v];
  }

  std::ostream& operator<<(std::ostream& os) {
    os << "V: " << V_ << ", E: " << E_ << '\n';
    for (uint64_t v = 0; v < V_; v++) {
      os << v << ":";
      for (auto const w : adj_[v]) {
        os << ' ' << w;
      }
      os << '\n';
    }
    return os;
  }

 private:
  bool is_valid_vertex(uint64_t const v) const { return v < V_; }
};

}  // namespace alg
#endif  // !__ALG_GRAPH_GRAPH_HPP_
