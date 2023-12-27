#ifndef __ALG_SORT_QUICK_HPP__
#define __ALG_SORT_QUICK_HPP__

#include <cstddef>
#include <cstdint>
#include <functional>
#include <random/random.hpp>
#include <stdexcept>
#include <vector>

#include <sort/common.hpp>
#include <sort/insertion.hpp>

namespace alg {
/*
 * quick sort
 */
template <typename T, bool (*cmp)(T const&, T const&) = Order<T>::less>
class Quick {
  using Vector = std::vector<T>;

 public:
  static void sort(Vector& a) {
    Random<T>::shuffle(a);
    if (a.size() > 0) {
      sort(a, 0, a.size() - 1);
    }
  }

 private:
  static void sort(Vector& a, size_t const lo, size_t const hi) {
    if (hi <= lo) {
      return;
    }
    size_t const j = partition(a, lo, hi);
    if (j > 0) {  // be really carefully when substracting from `size_t` num
      sort(a, lo, j - 1);
    }
    sort(a, j + 1, hi);
  }

  static size_t partition(Vector& a, size_t const lo, size_t const hi) {
    size_t i = lo, j = hi + 1;
    size_t const pivot = lo;
    for (;;) {
      // find item on left to swap that no less than `a[lo]`
      for (; cmp(a[++i], a[pivot]);) {
        if (i == hi) {
          break;
        }
      }
      // find item on right to swap that no greater than `a[lo]`
      for (; cmp(a[pivot], a[--j]);) {
        if (j == lo) {
          break;
        }
      }
      // until pointers cross, `j` is the final position of `a[lo]`
      if (i >= j) {
        break;
      }
      // from `lo` to `j - 1`, no greater than `a[j]`
      // from `j + 1` to `hi`, no less than `a[j]`
      std::swap(a[i], a[j]);
    }
    std::swap(a[lo], a[j]);
    return j;
  }
};

/*
 * quick sort with practical improvements added
 * 1. insertion cutoff
 * 2. median of three select
 */
template <typename T, bool (*cmp)(T const&, T const&) = Order<T>::less>
class QuickX {
  using Vector = std::vector<T>;

 public:
  static void sort(Vector& a) {
    Random<T>::shuffle(a);
    if (!a.empty()) {
      sort(a, 0, a.size() - 1);
    }
  }

 private:
  static constexpr size_t INSERTION_CUTOFF = 8;

  static void sort(Vector& a, size_t const lo, size_t const hi) {
    if (hi <= lo) {
      return;
    }
    // insertion sort for small subarrays
    size_t const n = 1 + hi - lo;
    if (n <= INSERTION_CUTOFF) {
      Insertion<T, cmp>::sort(a, lo, hi);
      return;
    }
    size_t const j = partition(a, lo, hi);
    if (j > 0) {
      sort(a, lo, j - 1);
    }
    sort(a, j + 1, hi);
  }

  static size_t partition(Vector& a, size_t const lo, size_t const hi) {
    size_t const n = hi - lo + 1;
    size_t const m = median3(a, lo, lo + n / 2, hi);
    std::swap(a[lo], a[m]);
    size_t i = lo, j = hi + 1;
    while (true) {
      while (cmp(a[++i], a[lo])) {
        if (i == hi) {
          break;
        }
      }
      while (cmp(a[lo], a[--j])) {
        if (j == lo) {
          break;
        }
      }
      if (i >= j) {
        break;
      }
      std::swap(a[i], a[j]);
    }
    std::swap(a[lo], a[j]);
    return j;
  }

  static size_t median3(Vector& a,
                        size_t const i,
                        size_t const j,
                        size_t const k) {
    return cmp(a[i], a[j]) ? (cmp(a[j], a[k]) ? j : (cmp(a[i], a[k]) ? k : i))
                           : (cmp(a[k], a[j]) ? j : (cmp(a[k], a[i]) ? k : i));
  }
};

/*
 * quick sort: three-way partition
 */
template <typename T,
          int (*cmp)(T const& t1, T const& t2) =
              Order<T>::default_three_way_comparator>
class Quick3Way {
  using Vector = std::vector<T>;

 public:
  static void sort(Vector& a) {
    Random<T>::shuffle(a);
    if (!a.empty()) {
      sort(a, 0, a.size() - 1);
    }
  }

 private:
  static void sort(Vector& a, size_t const lo, size_t const hi) {
    if (hi <= lo) {
      return;
    }
    size_t lt = lo, i = lo + 1, gt = hi;
    T const v = a[lo];
    while (i <= gt) {
      int const r = cmp(a[i], v);
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
    if (lt > 0) {
      sort(a, lo, lt - 1, cmp);
    }
    sort(a, gt + 1, hi, cmp);
  }
};

// three way partition
template <typename T, bool (*cmp)(T const& t1, T const& t2) = Order<T>::less>
class QuickSelect {
  using Vector = std::vector<T>;

 public:
  static T const& select(Vector& a, size_t k) {
    Random<T>::shuffle(a);
    if (k >= a.size()) {
      throw std::runtime_error(
          "QuickSelect selecting error: cannot select out-of-range element");
    }
    size_t lo = 0, hi = a.size() - 1;
    while (lo < hi) {
      size_t const j = partition(a, lo, hi);
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
  static size_t partition(Vector& a, size_t const lo, size_t const hi) {
    size_t i = lo, j = hi + 1;
    while (true) {
      while (cmp(a[++i], a[lo])) {
        if (i == hi) {
          break;
        }
      }
      while (cmp(a[lo], a[--j])) {
        if (j == lo) {
          break;
        }
      }
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
