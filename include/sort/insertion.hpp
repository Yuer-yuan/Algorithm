#ifndef __ALG_INSERTION_HPP__
#define __ALG_INSERTION_HPP__

#include <vector>

namespace alg {
template <typename T>
class Insertion {
 public:
  static void sort(
      std::vector<T>& a,
      bool (*cmp)(T const& t1, T const& t2) = [](T const& t1, T const& t2) {
        return t1 < t2;
      }) {
    int n = a.size();
    for (int i = 1; i < n; i++) {
      for (int j = i; j > 0 && cmp(a[j], a[j - 1]); j--) {
        std::swap(a[j], a[j - 1]);
      }
    }
  }
};
};  // namespace alg

#endif  // !__ALG_SELECTION_HPP__
