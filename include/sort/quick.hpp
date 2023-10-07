#ifndef __ALG_SORT_QUICK_HPP__
#define __ALG_SORT_QUICK_HPP__

#include <random/random.hpp>
#include <sort/common.hpp>
#include <vector>

namespace alg {
template <typename T>
class Quick {
  using Vector = std::vector<T>;
  using Cmp = bool (*)(T const& t1, T const& t2);

 public:
  static void sort(Vector& a, Cmp cmp = Order<T>::less) {
    Random<T>::shuffle(a);
    sort(a, 0, a.size() - 1, cmp);
  }

 private:
  static void sort(Vector& a,
                   int const lo,
                   int const hi,
                   Cmp cmp = Order<T>::less) {
    if (hi <= lo) {
      return;
    }
    int j = partition(a, lo, hi, cmp);
    sort(a, lo, j - 1, cmp);
    sort(a, j + 1, hi, cmp);
  }

  static int partition(Vector& a,
                       int const lo,
                       int const hi,
                       Cmp cmp = Order<T>::less) {
    int i = lo, j = hi + 1;
    while (true) {
      // find item on left to swap
      while (cmp(a[++i], a[lo])) {
        if (i == hi) {
          break;
        }
      }
      // find item on right to swap
      while (cmp(a[lo], a[--j])) {
        if (j == lo) {
          break;
        }
      }
      // until pointers cross
      if (i >= j) {
        break;
      }
      std::swap(a[i], a[j]);
    }
    std::swap(a[lo], a[j]);
    return j;
  }
};
};  // namespace alg

#endif  // !__ALG_SORT_QUICK_HPP__
