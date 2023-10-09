#ifndef __ALG_SORT_INSERTION_HPP__
#define __ALG_SORT_INSERTION_HPP__

#include <sort/common.hpp>
#include <vector>

namespace alg {
template <typename T>
class Insertion {
  using Vector = std::vector<T>;
  using Cmp = bool (*)(T const& t1, T const& t2);

 public:
  static void sort(Vector& a,
                   int const lo,
                   int const hi,
                   Cmp cmp = Order<T>::less) {
    for (int i = lo + 1; i <= hi; i++) {
      for (int j = i; j > lo && cmp(a[j], a[j - 1]); j--) {
        std::swap(a[j], a[j - 1]);
      }
    }
  }

  static void sort(Vector& a, Cmp cmp = Order<T>::less) {
    sort(a, 0, a.size() - 1, cmp);
  }
};
};  // namespace alg

#endif  // !__ALG_SORT_INSERTION_HPP__
