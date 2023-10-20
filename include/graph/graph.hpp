#ifndef __ALG_GRAPH_GRAPH_HPP_
#define __ALG_GRAPH_GRAPH_HPP_

#include <list>
#include <sstream>
#include <vector>
namespace alg {
class Graph {
  int v_;
  int e_;
  std::vector<std::list<int>> adj_;

 public:
  Graph(int const v) : v_(v), e_(0) { adj_.resize(v_); }
  Graph(Graph const& G) : v_(G.v_), e_(G.e_), adj_(G.adj_) {}
  Graph& operator=(Graph const& G) {
    this->v_ = G.v_;
    this->e_ = G.e_;
    this->adj_ = G.adj_;
    return *this;
  }
  Graph(Graph&& G) : v_(G.v_), e_(G.e_), adj_(std::move(G.adj_)) {}
  Graph& operator=(Graph&& G) {
    this->v_ = G.v_;
    this->e_ = G.e_;
    this->adj_ = std::move(G.adj_);
    return *this;
  }

  int v() const { return v_; }

  int e() const { return e_; }

  void add_edge(int const v, int const w) {
    if (!is_vertex_valid(v) || !is_vertex_valid(w)) {
      return;
    }
    e_++;
    adj_[v].push_front(w);
    adj_[w].push_front(v);
  }

  std::vector<int> adj(int const v) const {
    std::vector<int> va;
    if (!is_vertex_valid(v)) {
      return va;
    }
    va.reserve(adj_[v].size());
    va.insert(va.end(), adj_[v].begin(), adj_[v].end());
    return va;
  }

  std::string str() const {
    std::stringstream ss;
    ss << "vertices: " << v_ << ", edges: " << e_ << '\n';
    for (int v = 0; v < v_; v++) {
      ss << v << ": ";
      for (int const w : adj_[v]) {
        ss << w << ' ';
      }
      ss << '\n';
    }
    return ss.str();
  }

 private:
  bool is_vertex_valid(int const v) const {
    if (v < 0 || v >= v_) {
      return false;
    }
    return true;
  }
};
}  // namespace alg
#endif  // !__ALG_GRAPH_GRAPH_HPP_
