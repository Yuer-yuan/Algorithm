#ifndef __ALG_GRAPH_DIGRAPH_HPP_
#define __ALG_GRAPH_DIGRAPH_HPP_

#include <cstdint>
#include <exception>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace alg {
class Digraph {
  uint64_t V_;
  uint64_t E_;
  std::vector<std::vector<uint64_t>> adj_;
  std::vector<uint64_t> indegree_;

 public:
  Digraph(uint64_t const V) : V_(V), E_(0) {
    adj_.resize(V_);
    indegree_.resize(V_);
  }
  Digraph(Digraph const& G)
      : V_(G.V_), E_(G.E_), adj_(G.adj_), indegree_(G.indegree_) {}
  Digraph& operator=(Digraph const& G) {
    this->V_ = G.V_;
    this->E_ = G.E_;
    this->adj_ = G.adj_;
    this->indegree_ = G.indegree_;
    return *this;
  }
  Digraph(Digraph&& G)
      : V_(G.V_),
        E_(G.E_),
        adj_(std::move(G.adj_)),
        indegree_(std::move(G.indegree_)) {}
  Digraph& operator=(Digraph&& G) {
    this->V_ = G.V_;
    this->E_ = G.E_;
    this->adj_ = std::move(G.adj_);
    this->indegree_ = std::move(G.indegree_);
    return *this;
  }

  uint64_t V() const { return V_; }

  uint64_t E() const { return E_; }

  void add_edge(uint64_t const v, uint64_t const w) {
    if (!is_valid_vertex(v) || !is_valid_vertex(w)) {
      throw std::runtime_error("error adding invalid edge to di-graph");
    }
    E_++;
    adj_[v].push_back(w);
    indegree_[w]++;
  }

  std::vector<uint64_t> adj(uint64_t const v) const {
    if (!is_valid_vertex(v)) {
      throw std::runtime_error(
          "error getting adjecency list of invalid vertex");
    }
    return adj_[v];
  }

  uint64_t outdegree(uint64_t const v) const {
    if (!is_valid_vertex(v)) {
      throw std::runtime_error("error getting outdegree of invalid vertex");
    }
    return adj_[v].size();
  }

  uint64_t indegree(uint64_t const v) const {
    if (!is_valid_vertex(v)) {
      throw std::runtime_error("error getting indegree of invalid vertex");
    }
    return indegree_[v];
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

  Digraph reverse() const {
    Digraph r = Digraph(V_);
    for (uint64_t v = 0; v < V_; v++) {
      for (uint64_t w : adj(v)) {
        r.add_edge(w, v);
      }
    }
    return r;
  }

 private:
  bool is_valid_vertex(uint64_t const v) const { return v < V_; }
};
}  // namespace alg
#endif  // !__ALG_GRAPH_DIGRAPH_HPP_
