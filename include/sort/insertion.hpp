#ifndef __ALG_SORT_INSERTION_HPP__
#define __ALG_SORT_INSERTION_HPP__

#include <sort/common.hpp>
#include <vector>

namespace alg {
template <typename T, bool (*cmp)(T const&, T const&) = Order<T>::less>
class Insertion {
  using Vector = std::vector<T>;

 public:
  static void sort(Vector& a, size_t const lo, size_t const hi) {
    for (size_t i = lo + 1; i <= hi; i++) {
      for (size_t j = i; j > lo && cmp(a[j], a[j - 1]); j--) {
        std::swap(a[j], a[j - 1]);
      }
    }
  }

  static void sort(Vector& a) {
    if (!a.empty()) {
      sort(a, 0, a.size() - 1);
    }
  }
};
};  // namespace alg

#endif  // !__ALG_SORT_INSERTION_HPP__
