#ifndef __ALG_SORT_SHELL_HPP__
#define __ALG_SORT_SHELL_HPP__

#include <sort/common.hpp>
#include <vector>

namespace alg {
template <typename T>
class Shell {
  using Vector = std::vector<T>;
  using Cmp = bool (*)(T const& t1, T const& t2);

 public:
  static void sort(Vector& a, Cmp cmp = Order<T>::less) {
    int n = a.size();
    int h = 1;
    while (3 * h + 1 < n) {
      h = 3 * h + 1;
    }
    while (h >= 1) {
      for (int i = h; i < n; i++) {
        for (int j = i; j >= h && cmp(a[j], a[j - h]); j -= h) {
          std::swap(a[j], a[j - h]);
        }
      }
      h /= 3;
    }
  }
};
};      // namespace alg
#endif  // !__ALG_SORT_SHELL_HPP__
