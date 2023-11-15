#ifndef __ALG_GRAPH_GRAPH_HPP_
#define __ALG_GRAPH_GRAPH_HPP_

#include <list>
#include <sstream>
#include <vector>

namespace alg {
class Graph {
  int V_;
  int E_;
  std::vector<std::list<int>> adj_;

 public:
  Graph(int const V) : V_(V), E_(0) { adj_.resize(V_); }
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

  int V() const { return V_; }

  int E() const { return E_; }

  void add_edge(int const v, int const w) {
    if (!is_valid_vertex(v) || !is_valid_vertex(w)) {
      return;
    }
    E_++;
    adj_[v].push_front(w);
    adj_[w].push_front(v);
  }

  std::vector<int> adj(int const v) const {
    std::vector<int> va;
    if (!is_valid_vertex(v)) {
      return va;
    }
    va.reserve(adj_[v].size());
    va.insert(va.end(), adj_[v].begin(), adj_[v].end());
    return va;
  }

  std::string str() const {
    std::stringstream ss;
    ss << "vertices: " << V_ << ", edges: " << E_ << '\n';
    for (int v = 0; v < V_; v++) {
      ss << v << ": ";
      for (int const w : adj_[v]) {
        ss << w << ' ';
      }
      ss << '\n';
    }
    return ss.str();
  }

 private:
  bool is_valid_vertex(int const v) const {
    if (v < 0 || v >= V_) {
      return false;
    }
    return true;
  }
};
}  // namespace alg
#endif  // !__ALG_GRAPH_GRAPH_HPP_
