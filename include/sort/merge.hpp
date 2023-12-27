#ifndef __ALG_SORT_MERGE_HPP__
#define __ALG_SORT_MERGE_HPP__

#include <vector>

#include <sort/common.hpp>

namespace alg {
template <typename T, bool (*cmp)(T const& t1, T const& t2) = Order<T>::less>
/*
 * merge sort
 */
class Merge {
  using Vector = std::vector<T>;

 public:
  static void sort(Vector& a) {
    if (a.empty()) {
      return;
    }
    Vector aux(a);
    sort(a, aux, 0, a.size() - 1);
  }

 private:
  static void sort(Vector& a, Vector& aux, size_t const lo, size_t const hi) {
    if (hi <= lo) {
      return;
    }
    size_t const mid = lo + (hi - lo) / 2;
    // switch the role of `a` and `aux` to avoid extra copy at each pass
    sort(aux, a, lo, mid);
    sort(aux, a, mid + 1, hi);
    merge(a, aux, lo, mid, hi);
  }

  static void merge(Vector& a,
                    Vector& aux,
                    size_t const lo,
                    size_t const mid,
                    size_t const hi) {
    size_t i = lo, j = mid + 1;
    for (size_t k = lo; k <= hi; k++) {
      if (i > mid) {
        a[k] = aux[j++];
      } else if (j > hi) {
        a[k] = aux[i++];
      } else if (cmp(aux[j], aux[i])) {
        a[k] = aux[j++];
      } else {
        a[k] = aux[i++];
      }
    }
  }
};

/*
 * merge sort : bottom up (slower than recursive version)
 */
template <typename T, bool (*cmp)(T const& t1, T const& t2) = Order<T>::less>
class MergeBU {
  using Vector = std::vector<T>;

 public:
  static void sort(Vector& a) {
    Vector aux(a);
    size_t const n = a.size();
    for (size_t sz = 1; sz < n; sz *= 2) {
      for (size_t lo = 0; lo < n - sz; lo += 2 * sz) {
        merge(a, aux, lo, lo + sz - 1, std::min(lo + 2 * sz - 1, n - 1));
      }
    }
  }

 private:
  static void merge(Vector& a,
                    Vector& aux,
                    size_t const lo,
                    size_t const mid,
                    size_t const hi) {
    for (size_t k = lo; k <= hi; k++) {
      aux[k] = a[k];
    }
    size_t i = lo, j = mid + 1;
    for (size_t k = lo; k <= hi; k++) {
      if (i > mid) {
        a[k] = aux[j++];
      } else if (j > hi) {
        a[k] = aux[i++];
      } else if (cmp(aux[j], aux[i])) {
        a[k] = aux[j++];
      } else {
        a[k] = aux[i++];
      }
    }
  }
};

};      // namespace alg
#endif  // !__ALG_SORT_SORT_HPP__
