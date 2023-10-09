#ifndef __ALG_SORT_QUICK_HPP__
#define __ALG_SORT_QUICK_HPP__

#include <random/random.hpp>
#include <sort/common.hpp>
#include <sort/insertion.hpp>
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
    int const j = partition(a, lo, hi, cmp);
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
      // that no less than `a[lo]`
      while (cmp(a[++i], a[lo])) {
        if (i == hi) {
          break;
        }
      }
      // find item on right to swap
      // that no greater than `a[lo]`
      while (cmp(a[lo], a[--j])) {
        // redundant
        if (j == lo) {
          break;
        }
      }
      // until pointers cross
      // `j` is the final position of `a[lo]`
      if (i >= j) {
        break;
      }
      // s.t.
      // from `lo` to `j - 1`, no greater than `a[j]`
      // from `j + 1` to `hi`, no less than `a[j]`
      std::swap(a[i], a[j]);
    }
    std::swap(a[lo], a[j]);
    return j;
  }
};

// practical improvements added:
// insertion cutoff and median of three select
template <typename T>
class QuickX {
  using Vector = std::vector<T>;
  using Cmp = bool (*)(T const& t1, T const& t2);
  static constexpr int INSERTION_CUTOFF = 8;

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
    // insertion sort for small subarrays
    int const n = hi - lo + 1;
    if (n <= INSERTION_CUTOFF) {
      Insertion<T>::sort(a, lo, hi);
      return;
    }
    int const j = partition(a, lo, hi, cmp);
    sort(a, lo, j - 1, cmp);
    sort(a, j + 1, hi, cmp);
  }

  static int partition(Vector& a,
                       int const lo,
                       int const hi,
                       Cmp cmp = Order<T>::less) {
    int const n = hi - lo + 1;
    int const m = median3(a, lo, lo + n / 2, hi, cmp);
    std::swap(a[lo], a[m]);
    int i = lo, j = hi + 1;
    while (true) {
      // find item on left to swap
      // that no less than `a[lo]`
      while (cmp(a[++i], a[lo])) {
        if (i == hi) {
          break;
        }
      }
      // find item on right to swap
      // that no greater than `a[lo]`
      while (cmp(a[lo], a[--j])) {
        // redundant
        if (j == lo) {
          break;
        }
      }
      // until pointers cross
      // `j` is the final position of `a[lo]`
      if (i >= j) {
        break;
      }
      // s.t.
      // from `lo` to `j - 1`, no greater than `a[j]`
      // from `j + 1` to `hi`, no less than `a[j]`
      std::swap(a[i], a[j]);
    }
    std::swap(a[lo], a[j]);
    return j;
  }

  static int median3(Vector& a,
                     int const i,
                     int const j,
                     int const k,
                     Cmp cmp = Order<T>::less) {
    return cmp(a[i], a[j]) ? (cmp(a[j], a[k]) ? j : (cmp(a[i], a[k]) ? k : i))
                           : (cmp(a[k], a[j]) ? j : (cmp(a[k], a[i]) ? k : i));
  }
};

// three way partition
template <typename T>
class Quick3Way {
  using Vector = std::vector<T>;
  using Cmp = int (*)(T const& t1, T const& t2);

 public:
  static void sort(Vector& a,
                   Cmp cmp = Order<T>::default_three_way_comparator) {
    Random<T>::shuffle(a);
    sort(a, 0, a.size() - 1, cmp);
  }

 private:
  static void sort(Vector& a,
                   int const lo,
                   int const hi,
                   Cmp cmp = Order<T>::default_three_way_comparator) {
    if (hi <= lo) {
      return;
    }
    int lt = lo, i = lo + 1, gt = hi;
    T const v = a[lo];
    while (i <= gt) {
      int r = cmp(a[i], v);
      if (r < 0) {
        std::swap(a[i], a[lt]);
        i++;
        lt++;
      } else if (r > 0) {
        std::swap(a[i], a[gt]);
        gt--;
      } else {
        i++;
      }
    }
    sort(a, lo, lt - 1, cmp);
    sort(a, gt + 1, hi, cmp);
  }
};

// three way partition
template <typename T>
class QuickSelect {
  using Vector = std::vector<T>;
  using Cmp = bool (*)(T const& t1, T const& t2);

 public:
  static T const& select(Vector& a, int k, Cmp cmp = Order<T>::less) {
    Random<T>::shuffle(a);
    int lo = 0, hi = a.size() - 1;
    while (lo < hi) {
      int j = partition(a, lo, hi, cmp);
      if (j > k) {
        hi = j - 1;
      } else if (j < k) {
        lo = j + 1;
      } else {
        return a[j];
      }
    }
    return a[lo];
  }

 private:
  static int partition(Vector& a,
                       int const lo,
                       int const hi,
                       Cmp cmp = Order<T>::less) {
    int i = lo, j = hi + 1;
    while (true) {
      // find item on left to swap
      // that no less than `a[lo]`
      while (cmp(a[++i], a[lo])) {
        if (i == hi) {
          break;
        }
      }
      // find item on right to swap
      // that no greater than `a[lo]`
      while (cmp(a[lo], a[--j])) {
        // redundant
        if (j == lo) {
          break;
        }
      }
      // until pointers cross
      // `j` is the final position of `a[lo]`
      if (i >= j) {
        break;
      }
      // s.t.
      // from `lo` to `j - 1`, no greater than `a[j]`
      // from `j + 1` to `hi`, no less than `a[j]`
      std::swap(a[i], a[j]);
    }
    std::swap(a[lo], a[j]);
    return j;
  }
};

};  // namespace alg

#endif  // !__ALG_SORT_QUICK_HPP__
