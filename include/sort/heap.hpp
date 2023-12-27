#ifndef __ALG_SORT_HEAP_HPP__
#define __ALG_SORT_HEAP_HPP__

#include <cstdint>
#include <optional>
#include <vector>

#include <sort/common.hpp>

namespace alg {
template <typename T, bool (*cmp)(T const& t1, T const& t2) = Order<T>::less>
class Heap {
  using Vector = std::vector<T>;

 public:
  static void sort(Vector& a) {
    size_t n = a.size();
    // build max heap
    for (size_t k = n / 2; k >= 1; k--) {
      sink(a, k, n);
    }
    // remove the max val from `pq`
    // rebuild heap for the rest
    while (n > 1) {
      std::swap(a[0], a[n - 1]);
      n--;
      sink(a, 1, n);
    }
  }

 private:
  static void sink(Vector& a, size_t const k_, size_t const n) {
    size_t k = k_;
    while (k * 2 <= n) {
      size_t j = k * 2;
      // choosing the bigger one
      if (j < n && cmp(a[j - 1], a[j])) {
        j++;
      }
      // until parent no less than child
      if (!cmp(a[k - 1], a[j - 1])) {
        break;
      }
      std::swap(a[k - 1], a[j - 1]);
      k = j;
    }
  }
};

template <typename T, bool (*cmp)(T const& t1, T const& t2) = Order<T>::less>
class PriorityQueue {
  using Vector = std::vector<T>;
  using Optional = std::optional<T>;

 private:
  Vector pq_;

 public:
  PriorityQueue(){};

  PriorityQueue(Vector const& keys) {
    size_t const n = keys.size();
    pq_.resize(n);
    for (size_t i = 0; i < n; i++) {
      pq_[i] = keys[i];
    }
    for (size_t k = n / 2; k >= 1; k--) {
      sink(k);
    }
  };

  size_t size() const { return pq_.size(); };

  void push(T const& x) {
    pq_.push_back(x);
    swim(pq_.size());
  }

  Optional pop() {
    // empty
    if (pq_.empty()) {
      return std::nullopt;
    }
    T const r = pq_[0];
    std::swap(pq_[0], pq_[pq_.size() - 1]);
    pq_.pop_back();
    sink(1);
    return r;
  }

 private:
  void swim(size_t const k_) {
    // for each `child`, check with its `parent`
    // if `child` "<" `parent`
    // "swim" up
    size_t k = k_;
    while (k > 1 && cmp(pq_[k - 1], pq_[k / 2 - 1])) {
      std::swap(pq_[k - 1], pq_[k / 2 - 1]);
      k /= 2;
    }
  }

  void sink(size_t const k_) {
    // for each `parent`, check with its child(s)
    // select "smaller" child,
    // if `parent` ">" `child`
    // "sink" down
    size_t k = k_;
    size_t n = pq_.size();
    while (k * 2 <= n) {
      size_t j = k * 2;
      // check if another child exists
      // if so, compare two childs, select smaller one
      if (j < n && cmp(pq_[j], pq_[j - 1])) {
        j++;
      }
      // `parent` no greater than `child`,
      // no need to search more
      if (!cmp(pq_[j - 1], pq_[k - 1])) {
        break;
      }
      std::swap(pq_[k - 1], pq_[j - 1]);
      k = j;
    }
  }
};
};  // namespace alg

#endif  // !__ALG_SORT_HEAP_HPP__
