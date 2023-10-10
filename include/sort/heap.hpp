#ifndef __ALG_SORT_HEAP_HPP__
#define __ALG_SORT_HEAP_HPP__

#include <optional>
#include <sort/common.hpp>
#include <vector>

namespace alg {
template <typename T>
class Heap {
  using Vector = std::vector<T>;
  using Cmp = bool (*)(T const& t1, T const& t2);

 public:
  static void sort(Vector& a, Cmp cmp = Order<T>::less) {
    int n = a.size();
    // build max heap
    for (int k = n / 2; k >= 1; k--) {
      sink(a, k, n, cmp);
    }
    // remove the max val from `pq`
    // rebuild heap for the rest
    while (n > 1) {
      std::swap(a[0], a[n - 1]);
      n--;
      sink(a, 1, n, cmp);
    }
  }

 private:
  static void sink(Vector& a, int k, int const n, Cmp cmp = Order<T>::less) {
    while (k * 2 <= n) {
      int j = k * 2;
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

template <typename T>
class PriorityQueue {
  using Vector = std::vector<T>;
  using Cmp = bool (*)(T const& t1, T const& t2);
  using Optional = std::optional<T>;

 private:
  Vector pq_;
  Cmp cmp_;

 public:
  PriorityQueue(Vector const& keys, Cmp cmp = Order<T>::less) : cmp_{cmp} {
    int const n = keys.size();
    pq_.resize(n);
    for (int i = 0; i < n; i++) {
      pq_[i] = keys[i];
    }
    for (int k = n / 2; k >= 1; k--) {
      sink(k);
    }
  };
  PriorityQueue(Cmp cmp = Order<T>::less) : cmp_{cmp} {};

  int size() const { return pq_.size(); };

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
  void swim(int k) {
    // for each `child`, check with its `parent`
    // if `child` "<" `parent`
    // "swim" up
    while (k > 1 && cmp_(pq_[k - 1], pq_[k / 2 - 1])) {
      std::swap(pq_[k - 1], pq_[k / 2 - 1]);
      k /= 2;
    }
  }

  void sink(int k) {
    // for each `parent`, check with its child(s)
    // select "smaller" child,
    // if `parent` ">" `child`
    // "sink" down
    int n = pq_.size();
    while (k * 2 <= n) {
      int j = k * 2;
      // check if another child exists
      // if so, compare two childs, select smaller one
      if (j < n && cmp_(pq_[j], pq_[j - 1])) {
        j++;
      }
      // `parent` no greater than `child`,
      // no need to search more
      if (!cmp_(pq_[j - 1], pq_[k - 1])) {
        break;
      }
      std::swap(pq_[k - 1], pq_[j - 1]);
      k = j;
    }
  }
};
};  // namespace alg

#endif  // !__ALG_SORT_HEAP_HPP__
