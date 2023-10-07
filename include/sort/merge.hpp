#ifndef __ALG_SORT_MERGE_HPP__
#define __ALG_SORT_MERGE_HPP__

#include <sort/common.hpp>
#include <vector>

namespace alg {
template <typename T>
class Merge {
  using Vector = std::vector<T>;
  using Cmp = bool (*)(T const& t1, T const& t2);

 public:
  static void sort(Vector& a, Cmp cmp = Order<T>::less) {
    Vector aux(a);
    sort(a, aux, 0, a.size() - 1, cmp);
  }

 private:
  static void sort(Vector& a,
                   Vector& aux,
                   int const lo,
                   int const hi,
                   Cmp cmp = Order<T>::less) {
    if (hi <= lo) {
      return;
    }
    int const mid = lo + (hi - lo) / 2;
    // switch the role of `a` and `aux` to avoid extra copy at each pass
    sort(aux, a, lo, mid, cmp);
    sort(aux, a, mid + 1, hi, cmp);
    merge(a, aux, lo, mid, hi, cmp);
  }

  static void merge(Vector& a,
                    Vector& aux,
                    int const lo,
                    int const mid,
                    int const hi,
                    Cmp cmp = Order<T>::less) {
    int i = lo, j = mid + 1;
    for (int k = lo; k <= hi; k++) {
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

// merge bottom up
// but slower than recursive version
template <typename T>
class MergeBU {
  using Vector = std::vector<T>;
  using Cmp = bool (*)(T const& t1, T const& t2);

 public:
  static void sort(Vector& a, Cmp cmp = Order<T>::less) {
    Vector aux(a);
    int const n = a.size();
    for (int sz = 1; sz < n; sz *= 2) {
      for (int lo = 0; lo < n - sz; lo += 2 * sz) {
        merge(a, aux, lo, lo + sz - 1, std::min(lo + 2 * sz - 1, n - 1), cmp);
      }
    }
  }

 private:
  static void merge(Vector& a,
                    Vector& aux,
                    int const lo,
                    int const mid,
                    int const hi,
                    Cmp cmp = Order<T>::less) {
    for (int k = lo; k <= hi; k++) {
      aux[k] = a[k];
    }
    int i = lo, j = mid + 1;
    for (int k = lo; k <= hi; k++) {
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
