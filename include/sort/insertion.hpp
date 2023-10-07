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
  static void sort(Vector& a, Cmp cmp = Order<T>::less) {
    int n = a.size();
    for (int i = 1; i < n; i++) {
      for (int j = i; j > 0 && cmp(a[j], a[j - 1]); j--) {
        std::swap(a[j], a[j - 1]);
      }
    }
  }
};
};  // namespace alg

#endif  // !__ALG_SORT_INSERTION_HPP__
